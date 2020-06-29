#include "api.h"

static void resend_file(t_client *client, gchar *filename, gint room_id) {
    t_dtp *file_request = NULL;
    cJSON *msg = cJSON_CreateObject();
    t_db_message *db_msg = NULL;

    cJSON_AddNumberToObject(msg, "room_id", room_id);
    cJSON_AddStringToObject(msg, "message", filename);
    cJSON_AddNumberToObject(msg, "msg_type", DB_FILE_MSG);
    db_msg = mx_parse_message(msg);
    db_msg->user_id = client->user->user_id;
    mx_insert_message(client->info->database, db_msg);
    file_request = mx_msg_request(db_msg);
    mx_free_message(&db_msg);
    cJSON_Delete(msg);
    mx_send_to_all(file_request, client, room_id);
    mx_free_request(&file_request);
}

static gboolean is_valid(t_client *client, guint64 room_id) {
    if (!mx_is_member(client->info->database, client->user->user_id,
                      room_id)) {
        return FALSE;
    }
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id) == DB_BANNED) {
        return FALSE;
    }
    return TRUE;
}

static gboolean create_file(t_client *client, guint64 size, guint64 room_id,
                            gchar *name) {
    gchar *filename = g_strdup_printf(
        "%s%"G_GUINT64_FORMAT"%s%s", MX_FILES_DIR, mx_get_time(DB_MICROSECOND),
        client->user->login, name);
    if (!mx_read_file(client, size, filename)) {
        g_free(filename);
        return FALSE;
    }
    resend_file(client, filename, room_id);
    g_io_stream_close(G_IO_STREAM(client->conn), NULL, NULL);
    g_free(filename);
    return TRUE;
}

/*
 * Function: mx_upload_file_handler
 * -------------------------------
 * Handles request from client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_upload_file_handler(t_dtp *data, t_client *client) {
    cJSON *size = cJSON_GetObjectItemCaseSensitive(data->json, "size");
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->json, "name");
    cJSON *token = cJSON_GetObjectItemCaseSensitive(data->json, "token");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!cJSON_IsNumber(size) || !cJSON_IsString(name))
        return FALSE;
    if (!cJSON_IsString(token) || !cJSON_IsNumber(room_id))
        return FALSE;
    client->user = mx_get_user_by_token(client->info->database,
                                        token->valuestring);
    if (!is_valid(client, room_id->valuedouble))
        return FALSE;
    if (!create_file(client, size->valuedouble, room_id->valuedouble,
                     name->valuestring)) {
        return FALSE;
    }
    mx_free_user(&client->user);
    return TRUE;
}
