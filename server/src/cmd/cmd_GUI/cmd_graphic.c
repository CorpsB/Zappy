/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** graphic
*/

/**
 * @file cmd_graphic.c
 * @brief Handles the graphical client connection for the Zappy server.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * This file implements the "graphic" command, allowing a client to register
 * as a graphical client. Upon successful registration, initial game state
 * information is sent to the client to synchronize its view with the server.
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static void start_gui_event(server_t *server)
{
    event_msz(server);
    event_sgt(server);
    event_bct(server);
    event_tna(server);
    event_new_gui_enw(server);
    event_all_plv(server);
}

void cmd_graphic(server_t *server, int index, char **)
{
    if (server->poll.client_list[index].whoAmI == UNKNOWN) {
        server->poll.client_list[index].whoAmI = GUI;
        start_gui_event(server);
    } else {
        send_str(server, server->poll.pollfds[index].fd, "ko\n", false);
    }
}
