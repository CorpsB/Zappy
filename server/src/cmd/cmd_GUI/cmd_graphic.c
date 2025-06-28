/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** graphic
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
        send_str(server, server->poll.pollfds[index].fd, "ok\n");
        start_gui_event(server);
    } else {
        send_str(server, server->poll.pollfds[index].fd, "ko\n");
    }
}
