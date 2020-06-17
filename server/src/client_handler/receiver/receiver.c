#include "server.h"

void mx_init_receiver(t_info *chat) {
    chat->request_handler[RQ_SIGN_UP] = mx_sign_up_handler;
    chat->request_handler[RQ_TOKEN] = mx_log_in_token_handler;
    chat->request_handler[RQ_LOG_IN] = mx_log_in_handler;
    chat->request_handler[RQ_NEW_ROOM] = mx_new_room_handler;
    chat->request_handler[RQ_MSG] = mx_msg_handler;
    chat->request_handler[RQ_GET_ROOMS] = mx_get_rooms_handler;
    chat->request_handler[RQ_LOG_OUT] = mx_log_out_handler;
    chat->request_handler[RQ_GET_NEW_MSGS] = mx_get_msgs_handler;
    chat->request_handler[RQ_UPD_ROOM_DESC] = mx_upd_room_desc_handler;
    chat->request_handler[RQ_UPD_ROOM_NAME] = mx_upd_room_name_handler;
    chat->request_handler[RQ_UPD_USER_DESC] = mx_upd_user_desc_handler;
    chat->request_handler[RQ_DEL_ROOM] = mx_del_room_handler;
    chat->request_handler[RQ_RECONNECT] = NULL;
    chat->request_handler[RQ_DEL_MSG] = mx_del_msg_handler;
    chat->request_handler[RQ_EDIT_MSG] = mx_edit_msg_handler;
    chat->request_handler[RQ_FILE] = mx_upload_file_handler;
}

void mx_handle_request(char *request, t_client *client) {
    t_dtp *data = mx_request_creation(request);

    if (data) {
        printf("recv = %s\n", cJSON_Print(data->json));
        if (client->user || data->type == RQ_LOG_IN
            || data->type == RQ_SIGN_UP
            || data->type == RQ_TOKEN) {
            if (!client->info->request_handler[data->type]
                || !client->info->request_handler[data->type](data, client)) {
                    return;
            }
        }
        else
            return;
        mx_free_request(&data);
        usleep(MX_DELAY);
    }
}
