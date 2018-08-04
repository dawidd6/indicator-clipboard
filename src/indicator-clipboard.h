#pragma once

#include <QApplication>
#include <QClipboard>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QVector>
#include <QIcon>

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
        Tray();
        ~Tray() override;
        void onDataChanged();
        void onEntryTriggered();
        void addNewEntry(const QString &text);
        void deleteOldEntries();
        void trim(QString &text, int index);
        void showNotification(const QString &text);
        void checkSeparator();
};