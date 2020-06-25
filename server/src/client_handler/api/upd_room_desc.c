#include "api.h"

/*
 * Function: mx_upd_room_desc_request
 * -------------------------------
 * Creates request "update room description"
 * 
 * room_id: room id that need to update description
 * desc: new description
 * 
 * returns: new request
 */
t_dtp *mx_upd_room_desc_request(int room_id, char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_DESC))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", desc))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_upd_room_desc_handler
 * -------------------------------
 * Handles request from client
 * 
 * room: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
bool mx_upd_room_desc_handler(t_dtp *room, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room->json, "room_id");
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(room->json, "desc");
    t_db_room *room_db = NULL;
    t_dtp *resend = NULL;

    if (!cJSON_IsNumber(room_id))
        return false;
    if (!cJSON_IsString(desc))
        return false;
    if (mx_get_type_member(client->info->database, client->user->user_id, room_id->valueint) != DB_CUSTOMER)
        return false;
    mx_edit_desc_room_by_id(client->info->database, room_id->valueint, desc->valuestring);
    resend = mx_upd_room_desc_request(room_id->valueint, desc->valuestring);
    if (resend)
        mx_send_to_all(resend, client, room_id->valueint);
    mx_free_request(&resend);
    mx_free_room(&room_db);
    return true;
}
