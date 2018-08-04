#include <libnotify/notification.h>
#include <libnotify/notify.h>

#include <QApplication>
#include <QClipboard>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QVector>
#include <QIcon>
#include <QDebug>

class Tray : public QSystemTrayIcon {
    QVector <QAction*> actions;
    QVector <QString> strings;
    QString iconName;
    QIcon icon;
    QMenu *menu;
    QAction *quit;
    QAction *action;
    QAction *separator;
    QClipboard *clipboard;

    public:
        Tray() {
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

        ~Tray() override {
            delete menu;
            notify_uninit();
        }

        void onDataChanged() {
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

        void onEntryTriggered() {
            auto *action = (QAction *)sender();
            for(int i = 0; i < actions.size(); i++)
                if(action == actions[i]) {
                    clipboard->setText(strings[i]);
                    showNotification(actions[i]->text());
                }
        }

        void addNewEntry(const QString &text) {
            action = new QAction(text, menu);
            menu->insertAction(separator, action);
            actions.append(action);
            connect(action, &QAction::triggered, this, &Tray::onEntryTriggered);
        }

        void deleteOldEntries() {
            if(actions.size() > 5) {
                actions.first()->disconnect();
                menu->removeAction(actions.first());
                actions.removeFirst();
                strings.removeFirst();
            }
        }

        void trim(QString &text, int index) {
            text = text.trimmed();
            index = index > -1 ? index : 30;
            if(text.length() > index) {
                text.truncate(index);
                text += "...";
            }
        }

        void showNotification(const QString &text) {
            notify_notification_show(
                    notify_notification_new("Text copied to clipboard",
                            qPrintable(text),
                            qPrintable(iconName)),
                            nullptr);
        }

        void checkSeparator() {
            if(separator == nullptr) {
                separator = new QAction(menu);
                separator->setSeparator(true);
                menu->insertAction(quit, separator);
            }
        }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Tray tray;
    return QApplication::exec();
}
