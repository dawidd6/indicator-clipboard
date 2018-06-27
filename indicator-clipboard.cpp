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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QVector <QAction*> actions;
    QVector <QString> strings;
    QSystemTrayIcon tray;
    QMenu menu;
    QClipboard *clipboard = QApplication::clipboard();
    QString icon_name = "com.github.dawidd6.indicator-clipboard";
    QIcon icon = QIcon::fromTheme(icon_name);
    QAction *quit = menu.addAction("Quit");
    QAction *action = nullptr;
    QAction *separator = nullptr;

    notify_init("indicator-clipboard");

    QObject::connect(quit, &QAction::triggered, &a, &QApplication::quit);

    QObject::connect(clipboard, &QClipboard::dataChanged, [&]
    {
        QString text = clipboard->text();
        bool dupe = false;

        for(int i = 0; i < actions.size(); i++)
            if(text == strings[i])
                dupe = true;

        if(!dupe)
        {
            strings.append(text);
            text = text.trimmed();

            int i = text.indexOf('\n');
            i = i > -1 ? i : 30;
            if(text.length() > i)
            {
                text.truncate(i);
                text += "...";
            }

            if(separator == nullptr)
            {
                separator = new QAction(&menu);
                separator->setSeparator(true);
                menu.insertAction(quit, separator);
            }

            action = new QAction(text, &menu);
            actions.append(action);
            menu.insertAction(separator, action);
        }

        if(actions.size() > 5)
        {
            delete actions.first();
            menu.removeAction(actions.first());
            actions.erase(actions.begin());
            strings.erase(strings.begin());
        }

        for(int i = 0; i < actions.size(); i++)
        {
            actions[i]->disconnect();
            QObject::connect(actions[i], &QAction::triggered, [&, i]
            {
                clipboard->setText(strings[i]);
                notify_notification_show(
                notify_notification_new("Text copied to clipboard",
                                        qPrintable(actions[i]->text()),
                                        qPrintable(icon_name))
                                        , NULL);
            });
        }
    });

    tray.setContextMenu(&menu);
    tray.setIcon(icon);
    tray.show();

    a.exec();
    notify_uninit();
}
