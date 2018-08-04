#include <libnotify/notification.h>
#include <libnotify/notify.h>

#include "indicator-clipboard.h"

Tray::Tray() {
    menu = new QMenu();
    iconName = "com.github.dawidd6.indicator-clipboard";
    icon = QIcon::fromTheme(iconName);
    clipboard = QApplication::clipboard();

    quit = menu->addAction("Quit");
    action = nullptr;
    separator = nullptr;

    notify_init("indicator-clipboard");

    connect(quit, &QAction::triggered, &QApplication::quit);
    connect(clipboard, &QClipboard::dataChanged, this, &Tray::onDataChanged);

    setContextMenu(menu);
    setIcon(icon);
    show();
}

Tray::~Tray() {
    delete menu;
    notify_uninit();
}

void Tray::onDataChanged() {
    QString text = clipboard->text();

    for(int i = 0; i < actions.size(); i++)
        if(text == strings[i])
            return;
    strings.append(text);

    checkSeparator();
    trim(text, text.indexOf('\n'));
    addNewEntry(text);
    deleteOldEntries();
}

void Tray::onEntryTriggered() {
    auto *action = (QAction *)sender();
    for(int i = 0; i < actions.size(); i++)
        if(action == actions[i]) {
            clipboard->setText(strings[i]);
            showNotification(actions[i]->text());
        }
}

void Tray::addNewEntry(const QString &text) {
    action = new QAction(text, menu);
    menu->insertAction(separator, action);
    actions.append(action);
    connect(action, &QAction::triggered, this, &Tray::onEntryTriggered);
}

void Tray::deleteOldEntries() {
    if(actions.size() > 5) {
        actions.first()->disconnect();
        menu->removeAction(actions.first());
        delete actions.first();
        actions.removeFirst();
        strings.removeFirst();
    }
}

void Tray::trim(QString &text, int index) {
    text = text.trimmed();
    index = index > -1 ? index : 30;
    if(text.length() > index) {
        text.truncate(index);
        text += "...";
    }
}

void Tray::showNotification(const QString &text) {
    notify_notification_show(
            notify_notification_new("Text copied to clipboard",
                                    qPrintable(text),
                                    qPrintable(iconName)),
            nullptr);
}

void Tray::checkSeparator() {
    if(separator == nullptr) {
        separator = new QAction(menu);
        separator->setSeparator(true);
        menu->insertAction(quit, separator);
    }
}
