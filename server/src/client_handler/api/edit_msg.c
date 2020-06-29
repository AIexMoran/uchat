#include "api.h"

/*
 * Function: mx_edit_msg_request
 * -------------------------------
 * Creates request "edit message"
 * 
 * msg: new message
 * room_id: room id where this message contains
 * msg_id: message id that need to edit
 * 
 * returns: new request
 */
t_dtp *mx_edit_msg_request(char *msg, int room_id, int msg_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_EDIT_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "msg_id", msg_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", msg))
        return NULL;
    return mx_get_transport_data(json_result);
}

static gboolean is_valid(t_client *client, gint msg_id, gint room_id) {
    if (!mx_is_member(client->info->database,
                      client->user->user_id, room_id)) {
        return FALSE;
    }
    if (!mx_is_owner_msg(client->info->database,
                         client->user->user_id, msg_id)) {
        return FALSE;
    }
    if (mx_get_type_member(client->info->database,
                           client->user->user_id, room_id) == DB_BANNED) {
        return FALSE;
    }
    return TRUE;
}

/*
 * Function: mx_edit_msg_handler
 * -------------------------------
 * Handles request from client
 * 
 * msg: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_edit_msg_handler(t_dtp *msg, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(msg->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(msg->json, "msg_id");
    cJSON *msg_str = cJSON_GetObjectItemCaseSensitive(msg->json, "msg");
    t_dtp *resend = NULL;

    if (!cJSON_IsNumber(room_id) || !cJSON_IsNumber(msg_id)
        || !cJSON_IsString(msg_str)) {
        return FALSE;
    }
    if (!is_valid(client, msg_id->valuedouble, room_id->valuedouble))
        return FALSE;
    mx_edit_message_by_id(client->info->database, msg_id->valueint,
                          msg_str->valuestring);
    resend = mx_edit_msg_request(msg_str->valuestring,
                                 room_id->valueint, msg_id->valueint);
    mx_send_to_all(resend, client, room_id->valueint);
    mx_free_request(&resend);
    return TRUE;
}
