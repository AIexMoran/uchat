#pragma once

#include "utils.h"
#include "sqlite3.h"
#include "protocol.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

#define MX_IMGS_PATH "../src/gui/resources/"
#define MX_STICKER_PATH MX_IMGS_PATH"stickers/"
#define MX_GUI_PATH "../src/gui/gui.glade"
#define MX_IMG_EYE MX_IMGS_PATH"eye.png"
#define MX_IMG_CLOSEDEYE MX_IMGS_PATH"closed-eye.png"

#define MX_ERRMSG_INVALID_LOGIN "Login can be minimum 3 symbol of a-z, 0-9, -"
#define MX_ERRMSG_NODATA "Please, enter login and password"
#define MX_ERRMSG_DIFPASS "Passwords must match"
#define MX_ERRMSG_INCCRDATA "The login or password inccorect"
#define MX_ERRMSG_USEREXIST "User already exist"

#define MX_ROOM_CTRL 0
#define MX_MSG_CTRL 1

#define MX_LOCAL_ROOMS "listbox_rooms"
#define MX_GLOBAL_ROOMS "listbox_global_rooms"

#define MX_DARK_THEME "../src/gui/resources/dark-theme.css"
#define MX_LIGHT_THEME "../src/gui/resources/light-theme.css"

//settings
#define MX_BUF_MSGS 30
#define MX_MAX_LENGTH_QUEUE 30
#define MX_RECONN_ATTEMPTS 6
#define MX_RECONN_DELAY_S 4

// flag time
#define MX_TIME_SHORT 0
#define MX_TIME_LONG 1

//formatting
#define MX_FT_SCRATCH "~~"
#define MX_FT_BOLD "**"
#define MX_FT_IMPORTANT "``"
#define MX_FT_ITALIC "##"
#define MX_FT_UNDER "__"

#define MX_OP_SCRATCH "<span strikethrough=\"true\">%s</span>"
#define MX_OP_BOLD "<span font_weight=\"bold\">%s</span>"
#define MX_OP_IMPORTANT "<span background=\"#FF698C7F\">%s</span>"
#define MX_OP_ITALIC "<span font_style=\"italic\">%s</span>"
#define MX_OP_UNDER "<span underline=\"single\">%s</span>"

#define MX_CLOSE_SPAN "</span>"

typedef struct s_groom t_groom;
typedef struct s_gmsg t_gmsg;
typedef struct s_chat t_chat;
typedef struct s_filter_data t_filter_data;
typedef struct s_signal_data t_signal_data;
typedef struct s_gsticker t_gsticker;

struct s_groom {
    GtkListBox *box_rooms;
    GtkScrolledWindow *page;
    GtkListBoxRow *row_room;
    GtkStack *stack_msg;
    GtkListBox *box_messages;
    GtkLabel *label_name;
    GHashTable *members;
    gboolean is_watched;
    guint64 id;
    char *room_name;
    char *customer;
    guint64 customer_id;
    long int date;
    char *desc;
    bool is_updated;
    gint uploaded;
};

struct s_gmsg {
    GtkListBoxRow *row_msg;
    GtkLabel *label_text;
    gint type;
    char *msg;
    char *login;
    guint64 date;
    int room_id;
    int message_id;
};

struct s_chat {
    GDataOutputStream *out;
    GDataInputStream *in;
    GSocketConnection *conn;
    GSocketClient *cli_conn;
    char *auth_token;
    char *login;
    gchar *desc;
    int argc;
    char **argv;
    gsize id;
    t_groom *curr_room;
    t_dtp *data;
    gboolean upl_old_msgs;
    GtkBuilder *builder;
    gboolean valid;
    void (*error_handler[ER_COUNT_ERRS])(GtkBuilder *builder);
    gboolean (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, struct s_chat *chat);
    gboolean msg_placeholder;
    GtkCssProvider *cssProv;
};

struct s_signal_data {
    t_groom *groom;
    t_chat *chat;
    GtkListBoxRow *row_msg;
};

struct s_filter_data {
    gboolean is_found_rooms;
    gchar *search_name;
};

gssize mx_send(GDataOutputStream *out, t_dtp *dtp);
int mx_tcp_connect(const char *host, const char *serv);
t_chat *mx_init_chat(GSocketConnection *connection, int argc, char **argv);
void mx_receiver(GObject *source_object, GAsyncResult *res, gpointer user_data);
void mx_init_handlers(t_chat *chat);
void mx_init_errors(t_chat *chat);
void mx_get_data(t_chat *chat);
void mx_upload_file(gchar *path, gint room_id, t_chat *chat);


//handlers
gboolean mx_error_handler(t_dtp *data, t_chat *chat);
gboolean mx_authorization_handler(t_dtp *token, t_chat *chat);
gboolean mx_new_room_handler(t_dtp *data, t_chat *chat);
gboolean mx_msg_handler(t_dtp *data, t_chat *chat);
gboolean mx_rooms_hanlder(t_dtp *data, t_chat *chat);
gboolean mx_log_out_handler(t_dtp *token, t_chat *chat);
gboolean mx_new_msgs_hanlder(t_dtp *data, t_chat *chat);
gboolean mx_upd_room_desc_handler(t_dtp *data, t_chat *chat); // HANDLER FOR ROOM UPDATE DESCRIPTION REQUEST
gboolean mx_upd_room_name_handler(t_dtp *data, t_chat *chat); // HANDLER FOR ROOM UPDATE NAME REQUEST
gboolean mx_upd_user_desc_handler(t_dtp *data, t_chat *chat); // HANDLER FOR USER UPDATE DESCRIPTION REQUEST
gboolean mx_update_users_handler(t_dtp *data, t_chat *chat); // HANDLER FOR USERS ONLINE UPDATE
gboolean mx_del_room_handler(t_dtp *data, t_chat *chat);  // HANDLER FOR DELETE ROOM
gboolean mx_edit_msg_handler(t_dtp *data, t_chat *chat); // HANDLER FOR EDIT MSG
gboolean mx_del_msg_handler(t_dtp *data, t_chat *chat); // HANDLER FOR DEL MSG
gboolean mx_upload_file_handler(t_dtp *data, t_chat *chat); // HANDLER FOR GET FILE
gboolean mx_search_rooms_handler(t_dtp *data, t_chat *chat); //HANDLER FOR SEARCHING
gboolean mx_join_room_handler(t_dtp *data, t_chat *chat); //HANDLER FOR JOIN ROOM
gboolean mx_get_members_handler(t_dtp *data, t_chat *chat); //HANDLER FOR USERS
gboolean mx_member_info_handler(t_dtp *data, t_chat *chat); //HANDLER FOR INFO MEMBER
gboolean mx_new_member_handler(t_dtp *data, t_chat *chat); //HANDLER FOR NEW MEMBER
gboolean mx_ban_member_handler(t_dtp *data, t_chat *chat); //HANDLER FOR BAN MEMBER
gboolean mx_search_msgs_handler(t_dtp *data, t_chat *chat); //HANDLER FOR SEARCH MSG
gboolean mx_del_hist_handler(t_dtp *data, t_chat *chat); //HANDLER FOR DELETE HISTORY
gboolean mx_old_msgs_hanlder(t_dtp *data, t_chat *chat); //HANDLER FOR UPD MSGS
void mx_download_file(guint64 room_id, guint64 msg_id, t_chat *chat);
void mx_file_read(gsize size, gchar *name, GInputStream *in);


/*
 *  t_dtp *dtp = mx_upd_room_desc_request(1, "0000000000");
 *  mx_send(chat->ssl, dtp);
 *  mx_free_request(&dtp);
 * 
 * 
 * 
 */
//api
t_dtp *mx_new_room_request(char *room_name, char *desc, t_room_type type);
t_dtp *mx_msg_request(char *msg, guint64 room_id);
t_dtp *mx_token_request(char *token);
t_dtp *mx_log_in_request(char *login, char *pass);
t_dtp *mx_sign_up_request(char *login, char *pass);
t_dtp *mx_get_rooms_request(guint64 date);
t_dtp *mx_log_out_request(char *token);
t_dtp *mx_get_new_msgs_request(guint64 date, guint64 room_id);
t_dtp *mx_upd_room_desc_request(guint64 room_id, char *desc); // FOR ROOM UPDATE DESCRIPTION CREATE REQUEST
t_dtp *mx_upd_room_name_request(guint64 room_id, char *name); // FOR ROOM UPDATE NAME CREATE REQUEST
t_dtp *mx_upd_user_desc_request(char *desc); // FOR USER DESCRIPTION UPDATE
t_dtp *mx_del_room_request(guint64 room_id); // FOR DELETE ROOM
t_dtp *mx_upd_user_name_request(char *name); //TODO
t_dtp *mx_del_msg_request(guint64 room_id, guint64 msg_id); // FOR DELETE MESSAGE FROM ROOM
t_dtp *mx_edit_msg_request(char *msg, guint64 room_id, guint64 msg_id); // FOR EDIT MESSAGE IN ROOM
t_dtp *mx_search_rooms_request(char *room_name); // FOR SEARCHING CHANNEL
t_dtp *mx_join_room_request(guint64 room_id); //FOR JOIN TO ROOM
t_dtp *mx_get_members_request(guint64 room_id); //FOR MEMEBERS
t_dtp *mx_member_info_request(guint64 user_id); //FOR INFO ABOUT MEMBER
t_dtp *mx_ban_member_request(guint64 room_id, guint64 user_id); // FOR BAN MEMBER
t_dtp *mx_sticker_request(char *sticker, guint64 room_id); // FOR STICKER
t_dtp *mx_search_msgs_request(char *msg, guint64 room_id); // FOR SEARCH MSGS
t_dtp *mx_del_hist_request(guint64 room_id); // FOR DELETE HISTORY
t_dtp *mx_old_msgs_request(guint64 date, guint64 room_id); // FOR UPD MSGS REQUEST
t_dtp *mx_upload_file_request(const char *name, goffset size,
                              char *token, guint64 room_id); // FOR FILE
t_dtp *mx_download_file_request(guint64 room_id, guint64 msg_id, gchar *token);

//errors api
void mx_err_auth_data_handler(GtkBuilder *builder);
void mx_err_user_exist_handler(GtkBuilder *builder);

//gui
GtkBuilder *mx_init_window(int argc, char **argv);
void mx_init_gui(t_chat *chat);
gint mx_start_gui(t_chat *chat);
void mx_start_main_window(t_chat *chat);
void mx_add_groom(t_groom *room, t_chat *chat);
void mx_delete_groom(t_groom *room);
t_groom *mx_create_groom(cJSON *room);
t_gmsg *mx_create_gmsg(cJSON *msg, t_chat *chat);
void mx_delete_gmsg(t_gmsg *gmsg);
GtkWidget *mx_create_reg_message_row(t_gmsg *gmsg,
                                     gboolean is_own, t_chat *chat);
void mx_add_message_to_room_new(t_gmsg *msg, t_chat *chat);
void mx_add_message_to_room_old(t_gmsg *msg, t_chat *chat);
void mx_logout_client(t_chat *chat);
void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder);
void mx_reset_auth(GtkNotebook *note, GtkWidget *page,
                   guint page_num, GtkBuilder *builder);
void mx_errmsg_wrong_authdata(GtkBuilder *builder);
void mx_errmsg_user_exist(GtkBuilder *builder);
void mx_delete_row_room(GtkListBoxRow *row, GtkBuilder *builder);
void mx_set_default_room_sett(GtkBuilder *builder);
void mx_set_current_room_sett(GtkBuilder *builder);
void mx_gupd_room_desc(guint64 id, char *desc, GtkBuilder *builder);
void mx_gupd_room_name(guint64 id, char *name, GtkBuilder *builder);
void mx_gdel_room(guint64 id, GtkBuilder *builder);
void mx_gdel_msg(guint64 msg_id, guint64 room_id, GtkBuilder *builder);
void mx_gupd_msg_text(guint64 msg_id, guint64 room_id,
                      char *text, GtkBuilder *builder);
void mx_reset_messege_room(t_groom *new_selected, GtkBuilder *builder);
void mx_hide_msg_editing(GtkButton *btn, GtkBuilder *builder);
void mx_set_room_widgets_visibility(GtkBuilder *builder, bool visibility);
void mx_switch_room_header(GtkBuilder *builder, gint page_index);
void mx_unselect_curr_room_messages(GtkBuilder *builder);
void mx_select_msg(gpointer *eventbox, gpointer *event, t_signal_data *data);
GtkWidget *mx_create_reg_message_row(t_gmsg *gmsg,
                                     gboolean is_own, t_chat *chat);
GtkWidget *mx_msgcreate_eventbox();
GtkWidget *mx_msgcreate_box_main(GtkWidget *eventbox, gboolean is_own);
void mx_msgcreate_box_info(GtkWidget *box_main, t_gmsg *gmsg,
                           gboolean is_own, t_chat *chat);
void mx_msgcreate_label_login(GtkWidget *box_main, t_gmsg *gmsg);
void mx_msgcreate_label_text(GtkWidget *box_info,
                             t_gmsg *gmsg, gboolean is_own);
void mx_msgcreate_img_sticker(GtkWidget *box_info,
                              t_gmsg *gmsg, gboolean is_own);
void mx_msgcreate_file(GtkWidget *box_info, t_gmsg *gmsg,
                       gboolean is_own, t_chat *chat);
GtkWidget *mx_create_message_row(t_chat *chat, t_gmsg *gmsg);
void mx_msgcreate_label_time(GtkWidget *box_info,
                             t_gmsg *gmsg, gboolean is_own);
void mx_search_delim_set_visibility(GtkBuilder *builder, gboolean is_visible);
gboolean mx_stop_search_room(gpointer *entry,
                             gpointer *data, GtkBuilder *builder);
void mx_search_local_rooms(GtkBuilder *builder, t_filter_data *data);
void mx_search_global_rooms(GtkBuilder *builder);
void mx_add_room_row(t_groom *room, t_chat *chat, gchar *listbox_name);
void mx_clear_global_search(GtkBuilder *builder);
void mx_box_messages_reached(GtkScrolledWindow *scroll,
                             GtkPositionType pos, t_chat *chat);
gboolean mx_stop_search_message(gpointer *entry,
                                gpointer *data, GtkBuilder *builder);
void mx_add_message_to_found(t_gmsg *gmsg, t_chat *chat);
void mx_clear_found_msgs(GtkBuilder *builder);
void mx_set_room_members(GtkBuilder *builder, t_groom *groom);
void mx_show_user_info(GtkBuilder *builder, gchar *login, gchar *desc);
void mx_gupd_clear_history(GtkBuilder *builder, guint64 room_id);
void mx_search_members(GtkBuilder *builder, gchar *search_login);
gboolean mx_stop_search_members(gpointer *entry,
                                gpointer *data, GtkBuilder *builder);
void mx_msgcreate_own_content(GtkWidget *box_info,
                              t_gmsg *gmsg, t_chat *chat);

void mx_msgcreate_content(GtkWidget *box_main, GtkWidget *box_info,
                          t_gmsg *gmsg, t_chat *chat);
t_groom *mx_init_groom();
void mx_add_messages_box(t_groom *room, t_chat *chat);
void mx_add_to_sett_members(gint *key,
                            gchar *value, GtkBuilder *builder);
void mx_add_to_info_members(gint *key,
                            gchar *value, GtkBuilder *builder);
void mx_reset_select_count();

// gui utils
void mx_scrlldwnd_connect(gchar *name, GtkWidget *scroll, GtkBuilder *builder, t_groom *room);
gchar *mx_entry_get_text(gchar *entry_name, GtkBuilder *builder);
gchar *mx_get_buffer_text(gchar *buff_name, GtkBuilder *builder);
void mx_clear_buffer_text(gchar *buff_name, GtkBuilder *builder);
void mx_clear_label_by_name(gchar *label_name, GtkBuilder *builder);
void mx_widget_set_visibility(GtkWidget *widget, gboolean is_visible);
void mx_widget_set_visibility_by_name(GtkBuilder *builder,
                                      gchar *name, gboolean is_visible);
void mx_widget_switch_visibility(GtkWidget *usr_ctrl, GtkWidget *widget);
void mx_widget_switch_visibility_by_name(GtkBuilder *builder, gchar *name);
t_groom *mx_get_selected_groom(GtkBuilder *builder, gchar *list_name);
t_groom *mx_get_groom_by_id(guint64 room_id, GtkBuilder *builder);
t_gmsg *mx_get_selected_gmsg(GtkBuilder *builder);
t_gmsg *mx_get_gmsg_by_id(gint msg_id, gint room_id, GtkBuilder *builder);
void mx_unselect_room(t_groom *groom, GtkBuilder *builder);
void mx_entry_set_icon_by_path(GtkEntry *entry, gchar *path,
                               GtkEntryIconPosition icon_pos);
t_signal_data *mx_create_sigdata(t_chat *chat, t_groom *groom,
                                 GtkListBoxRow *row_msg);
void mx_free_sigdata(t_signal_data *data);
char *mx_msgpage_name(gint id);
gboolean mx_widget_is_visible(gchar *widget_name, GtkBuilder *builder);
void mx_widget_set_class(GtkWidget *widget, gchar *class);
void mx_widget_remove_class(GtkWidget *widget, gchar *class);
t_filter_data *mx_create_filter_data(gchar *search_name);
void mx_free_filter_data(t_filter_data *filter_data);
gchar *mx_get_string_time(guint64 miliseconds, gint8 format);
void mx_connect_set_placeholder(t_chat *chat);
void mx_connect_unset_placeholder(t_chat *chat);
void mx_connect_addroom(t_chat *chat);
void mx_connect_send_message(t_chat *chat);
void mx_connect_profile_settings(t_chat *chat);
void mx_connect_room_settings(t_chat *chat);
void mx_connect_message_ctrl(t_chat *chat);
void mx_connect_authorization(t_chat *chat);
void mx_connect_search(t_chat *chat);
void mx_connect_join_to_room(t_chat *chat);
void mx_connect_stickers(t_chat *chat);
void mx_connect_ban_member(t_chat *chat);
void mx_connect_test_request(t_chat *chat); // DELETE
void mx_connect_filechooser(t_chat *chat);

// gui callbacks
void mx_show_edit_msg(GtkButton *btn, t_chat *chat);
void mx_delete_selected_msgs(GtkButton *btn, t_chat *chat);
void mx_unselect_msg(GtkButton *btn, GtkBuilder *builder);
void mx_req_get_member_info(GObject *popup, t_chat *chat);
void mx_req_edit_desc(GtkButton *btn, t_chat *chat);
void mx_req_logout(GtkButton *btn, t_chat *chat);
void mx_set_profile_info(GtkButton *btn, t_chat *chat);
void mx_set_room_sett(GtkButton *btn, t_chat *chat);
void mx_req_room_sett(GtkButton *btn, t_chat *chat);
void mx_req_room_clear(GtkButton *btn, t_chat *chat);
void mx_req_room_del(GtkButton *btn, t_chat *chat);
void mx_start_search_room(GtkSearchEntry *sentry, t_chat *chat);
void mx_start_search_msgs(GtkSearchEntry *sentry, t_chat *chat);
void mx_start_search_members(GtkSearchEntry *sentry, t_chat *chat);
void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder);
void mx_set_current_room_sett(GtkBuilder *builder);
void mx_select_room(GtkWidget *event_box, GdkEventButton *event,
                    gpointer *user_data);
void mx_show_join_to_room(GtkWidget *event_box, GdkEventButton *event,
                          gpointer *user_data);

// void mx_upload_file(gchar *path, gint room_id, t_chat *chat);
bool mx_handle_request(char *request, t_chat *chat);
void mx_send_auth_request(char *login, char *password,
                          t_chat *chat, t_request_type request_type);
void mx_css_connect(char *theme, t_chat *chat);
void mx_css_connect_from_file(t_chat *chat);
void mx_connect_theme_switcher(t_chat *chat);
void change_theme_icon(t_chat *chat, gchar *icon_name);
gchar *mx_format_text(gchar *text);
