#include "client.h"

static void req_test(GtkButton *btn, t_chat *chat) {
    t_file *file = mx_upload_file("/Users/okhomin/Desktop/ucode/ush/ush/ush");
    t_dtp *file_rq = mx_upload_file_request("ush", (int)file->st.st_size);

    printf("size = %lld\n", file->st.st_size);
    mx_send(chat->ssl, file_rq);
    mx_send_file(chat->ssl, file->bytes, file->st.st_size);
    mx_free_file(&file);
    mx_free_request(&file_rq);
    (void)chat;
    (void)btn;
}

void mx_connect_test_request(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_stickers"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_test), chat);
}
