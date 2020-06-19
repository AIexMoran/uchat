#include "server.h"

void mx_free_user(t_db_user **user) {
    if (!user || !*user)
        return;
    if ((*user)->login)
        mx_free((void**)&(*user)->login);
    if ((*user)->pass)
        mx_free((void**)&(*user)->pass); 
    if ((*user)->token) 
        mx_free((void**)&(*user)->token);
    if ((*user)->desc)
        mx_free((void**)&(*user)->desc);
    if ((*user)->name)
        mx_free((void **)&(*user)->name);
    mx_free((void**)user); 
    *user = NULL;
}

void mx_free_room(t_db_room **room) {
    if (!room || !*room)
        return;
    if ((*room)->customer)
        mx_free((void**)&(*room)->customer);
    if ((*room)->room_name)
        mx_free((void**)&(*room)->room_name);
    if ((*room)->desc)
        mx_free((void **)&(*room)->desc);
    mx_free((void**)room);
    room = NULL;
}

void mx_free_message(t_db_message **message) {
    if (!message || !*message)
        return;
    if ((*message)->message)
        mx_free((void **)&(*message)->message);
    if ((*message)->name_file)
        mx_free((void **)&(*message)->name_file);
    mx_free((void**)message);
    message = NULL;
}