#include "client.h"

void mx_logout_client(t_chat *chat) {
    GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(chat->builder,
                                                          "listbox_rooms"));
    GtkListBoxRow *row = gtk_list_box_get_row_at_index(box, 0);

    while (row) {
        mx_delete_row_room(GTK_WIDGET(row), chat->builder);
        row = gtk_list_box_get_row_at_index(box, 0);
    }
}