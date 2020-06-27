#pragma once

#include "protocol.h"
#include "database.h"
#include "server.h"

/*
 * Requests
 */
t_dtp *mx_token_request(char *token, char *login, char *desc);
t_dtp *mx_error_msg_request(int error_code, char *msg);
t_dtp *mx_log_out_request(char *token);
t_dtp *mx_upd_room_desc_request(int room_id, char *room_name);
t_dtp *mx_upd_room_name_request(int room_id, char *room_name);
t_dtp *mx_upd_user_desc_request(char *desc);
t_dtp *mx_reconnect_request(char *token, char *login);
t_dtp *mx_search_rooms_request(cJSON *array);
t_dtp *mx_member_info_request(t_db_user *user);
t_dtp *mx_delete_room_request(int room_id);
t_dtp *mx_ban_member_request(int room_id, int user_id);
t_dtp *mx_search_msgs_request(cJSON *array);
t_dtp *mx_del_hist_request(int room_id);
t_dtp *mx_msg_request(t_db_message *msg);

/*
 * Handlers for requests
 */
bool mx_log_in_handler(t_dtp *login, t_client *client);
bool mx_sign_up_handler(t_dtp *signup_data, t_client *client);
bool mx_log_in_token_handler(t_dtp *token, t_client *client);
bool mx_new_room_handler(t_dtp *data, t_client *client);
bool mx_msg_handler(t_dtp *data, t_client *client);
bool mx_get_rooms_handler(t_dtp *data, t_client *client);
bool mx_log_out_handler(t_dtp *token, t_client *client);
bool mx_get_msgs_handler(t_dtp *data, t_client *client);
bool mx_upd_room_desc_handler(t_dtp *desc, t_client *client); //TODO
bool mx_upd_room_name_handler(t_dtp *desc, t_client *client); //TODO
bool mx_upd_user_desc_handler(t_dtp *desc_data, t_client *client); //TODO
bool mx_del_room_handler(t_dtp *data, t_client *client); //TODO
bool mx_del_msg_handler(t_dtp *msg, t_client *client); //TODO
bool mx_edit_msg_handler(t_dtp *msg, t_client *client); //TODO!!!!!!! DB
bool mx_search_rooms_handler(t_dtp *data, t_client *client);
bool mx_join_room_handler(t_dtp *room, t_client *client);
bool mx_get_members_handler(t_dtp *data, t_client *client);
bool mx_member_info_handler(t_dtp *id, t_client *client);
bool mx_ban_member_handler(t_dtp *ban, t_client *client);
bool mx_search_msgs_handler(t_dtp *data, t_client *client);
bool mx_del_hist_handler(t_dtp *msg, t_client *client);
bool mx_old_msgs_handler(t_dtp *data, t_client *client);
bool mx_upload_file_handler(t_dtp *file, t_client *client);

/*
 * Main request handler
 */
bool mx_handle_request(char *request, t_client *client);