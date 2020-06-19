#include "client.h"

static void mx_widget_set_class(GtkWidget *widget, char *class) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    gtk_style_context_add_class(context, class);
}

void mx_msgcreate_label_login(GtkWidget *box_main, t_gmsg *gmsg) {
    GtkWidget *label_login = gtk_label_new(gmsg->login);

    mx_widget_set_class(label_login, "sender_login");
    gtk_box_pack_start(GTK_BOX(box_main), label_login, FALSE, FALSE, 0);
    gtk_widget_set_halign(label_login, GTK_ALIGN_START);
}

void mx_msgcreate_label_text(GtkBuilder *builder, GtkWidget *box_info, t_gmsg *gmsg, gboolean is_own) {
    GtkWidget *label_text = gtk_label_new(NULL);

    gtk_box_pack_start(GTK_BOX(box_info), label_text, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(label_text), 0.00);
    gtk_widget_set_halign(label_text, GTK_ALIGN_START);
    gtk_label_set_line_wrap(GTK_LABEL(label_text), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(label_text), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_text(GTK_LABEL(label_text), gmsg->msg);
    gmsg->label_text = GTK_LABEL(label_text);
    g_object_ref(label_text);
    (void)builder;
    (void)is_own;
}

void mx_msgcreate_label_time(GtkWidget *box_info, t_gmsg *gmsg) {
    GtkWidget *label_time = gtk_label_new(NULL);

    gtk_box_pack_start(GTK_BOX(box_info), label_time, FALSE, TRUE, 0);
    gtk_widget_set_halign(label_time, GTK_ALIGN_START);
    gtk_widget_set_valign(label_time, GTK_ALIGN_END);
    gtk_label_set_text(GTK_LABEL(label_time), "13:07");
    gtk_widget_set_tooltip_text(label_time, "24.05.2020    13:37");
    (void)gmsg;
}

// MAIN CREATING
static GtkWidget *create_eventbox() {
    GtkWidget *eventbox = gtk_event_box_new();

    gtk_widget_set_can_focus(eventbox, FALSE);
    return eventbox;
}

static GtkWidget *create_box_main(GtkWidget *eventbox) {
    GtkWidget *box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    mx_widget_set_class(box_main, "main_msg_box");
    gtk_container_add(GTK_CONTAINER(eventbox), GTK_WIDGET(box_main));
    return box_main;
}

static void create_box_info(t_chat *chat,
                            GtkWidget *box_main, t_gmsg *gmsg) {
    GtkWidget *box_info = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gboolean is_own = !g_strcmp0(chat->login, gmsg->login);

    mx_widget_set_class(box_info, "box_msg_info");
    gtk_box_pack_end(GTK_BOX(box_main), box_info, FALSE, TRUE, 0);
    if (!is_own)
        mx_msgcreate_label_login(box_main, gmsg);
    mx_msgcreate_label_text(chat->builder, box_info, gmsg, is_own);
    mx_msgcreate_label_time(box_info, gmsg);
}

GtkWidget *mx_create_message_row(t_chat *chat, t_gmsg *msg) {
    GtkWidget  *eventbox = create_eventbox();
    GtkWidget *box_main = create_box_main(eventbox);
    create_box_info(chat, box_main, msg);

    return eventbox;
}
