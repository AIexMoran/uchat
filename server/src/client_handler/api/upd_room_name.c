#include "server.h"

t_dtp *mx_upd_room_name_request(int room_id, char *room_name) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_NAME))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", room_name))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_upd_room_name_handler(t_dtp *room, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room->json, "room_id");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(room->json, "room_name");
    t_db_room *room_db = NULL;
    t_dtp *resend = NULL;

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (!room_name || !cJSON_IsString(room_name))
        return false;
    if (mx_get_type_member(client->info->database, client->user->user_id, room_id->valueint) != DB_CUSTOMER)
        return false;
    mx_edit_room_name_by_id(client->info->database, room_id->valueint, room_name->valuestring);
    resend = mx_upd_room_name_request(room_id->valueint, room_name->valuestring);
    if (resend)
        mx_send_to_all(resend, client, room_id->valueint);
    mx_free_request(&resend);
    mx_free_room(&room_db);
    return true;
}
