#include "client.h"

t_dtp *mx_upd_msgs_request(long int date, int room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_MSGS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "date", date))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "count", MX_BUF_MSGS))
        return NULL;
    return mx_get_transport_data(json_result);
}

// static void insert_msg(cJSON *room, t_chat *chat, int room_id) {
//     t_dtp *dtp = NULL;
//     cJSON *dup = cJSON_Duplicate(room, cJSON_True);

//     if (!cJSON_AddNumberToObject(dup, "type", RQ_MSG))
//         return;
//     if (!cJSON_AddNumberToObject(dup, "room_id", room_id))
//         return;
//     dtp = mx_get_transport_data(dup);
//     mx_msg_handler(dtp, chat);
//     mx_free_request(&dtp);
// }

bool mx_upd_msgs_hanlder(t_dtp *data, t_chat *chat) {
    // cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    // cJSON *msgs = cJSON_GetObjectItemCaseSensitive(data->json, "messages");
    // cJSON *msg = NULL;

    // if (!cJSON_IsNumber(room_id))
    //     return false;
    // if (!cJSON_IsArray(msgs))
    //     return false;
    // for (int i = cJSON_GetArraySize(msgs) - 1; i >= 0; i--) {
    //     msg = cJSON_GetArrayItem(msgs, i);
    //     insert_msg(msg, chat, room_id->valueint);
    // }
    // g_message("received = %s\n")
    g_message("updated msg = %s\n", cJSON_Print(data->json));
    (void)data;
    (void)chat;
    return true;
}
