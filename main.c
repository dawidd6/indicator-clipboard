#include <string.h>

#include <gdk/gdk.h>
#include <gtk/gtk.h>

#include <libnotify/notify.h>
#include <libnotify/notification.h>

#include <libappindicator/app-indicator.h>

AppIndicator *indicator;
GtkClipboard *clipboard;
GtkWidget *menu;
GtkWidget *item_quit;
GtkWidget *item_test;
GtkWidget *item_separator;
GtkWidget *item;
GPtrArray *strings;
GPtrArray *items;

void handle_copy(GtkMenuItem *menuitem, gpointer user_data)
{
    for(int i = 0; i < items->len; i++)
        if(menuitem == g_ptr_array_index(items, i))
            g_print("match: %d\n", i);
}

void handle_owner_change(GtkClipboard *clipboard, GdkEvent *event, gpointer data)
{
    char *text = gtk_clipboard_wait_for_text(clipboard);
    char *trun = text;
    int pos = 0;
    item = gtk_menu_item_new_with_label(text);

    g_strstrip(trun);
    if(strlen(trun) > 30)
    {
        g_strlcpy(trun, trun, 30);
        g_strlcat(trun, "...", 33);
    }

    g_ptr_array_add(strings, text);
    g_ptr_array_add(items, item);

    if(items->len > 5)
    {
        gtk_widget_destroy(g_ptr_array_index(items, 0));
        g_ptr_array_remove_index(items, 0);
        g_ptr_array_remove_index(strings, 0);
        const char *t = gtk_menu_item_get_label((GtkMenuItem *)g_ptr_array_index(items, 0));
        g_print("content: %s\n", t);
        //BUG TODO
        pos = 4;
    }

    g_signal_connect(item, "activate", G_CALLBACK(handle_copy), NULL);
    gtk_menu_shell_insert(GTK_MENU_SHELL(menu), item, pos);
    gtk_widget_show(item);
}

int main(int argc, char** argv)
{
    notify_init("indicator-clipboard");
    gtk_init(&argc, &argv);

    indicator = app_indicator_new("indicator-clipboard", "com.github.dawidd6.indicator-clipboard", APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    menu = gtk_menu_new();
    item_quit = gtk_menu_item_new_with_label("Quit");
    item_test= gtk_menu_item_new_with_label("test");
    item_separator = gtk_separator_menu_item_new();
    strings = g_ptr_array_new();
    items = g_ptr_array_new();

    app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
    app_indicator_set_menu(indicator, GTK_MENU(menu));
    app_indicator_set_title(indicator, "Clipboard Indicator");

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_separator);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item_quit);

    g_signal_connect(item_quit, "activate", gtk_main_quit, NULL);

    g_signal_connect(clipboard, "owner-change", G_CALLBACK(handle_owner_change), NULL);

    gtk_widget_show_all(menu);
    gtk_main();
    notify_uninit();
    return 0;
}
