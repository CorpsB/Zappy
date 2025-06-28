/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_pin.c
*/

#include "include/include.h"
#include "include/structure.h"
#include "include/function.h"
#include "include/cmd.h"
#include "include/cmd_parser_table.h"

/**
 * @brief Sends inventory of a player to GUI.
 */
static void send_pin(server_t *server, int fd, const player_t *p)
{
    char *buffer = NULL;

    if (asprintf(&buffer, "pin %u %u %u %u %u %u %u %u %u %u\n",
        p->id, p->position[0], p->position[1],
        p->inventory.food, p->inventory.linemate,
        p->inventory.deraumere, p->inventory.sibur,
        p->inventory.mendiane, p->inventory.phiras,
        p->inventory.thystame) == -1)
        logger(server, "ASPRINTF : PIN", PERROR, true);
    send_str(server, fd, buffer);
}

static int find_gui_command_index(const char *name)
{
    for (int i = 0; gui_command_table[i].name; i++) {
        if (strcmp(gui_command_table[i].name, name) == 0)
            return i;
    }
    return -1;
}

void cmd_pin(server_t *server, int index, char **args)
{
    int fd;
    long id;
    char *e;
    player_t *p;
    int i = find_gui_command_index("pin");

    fd = server->poll.pollfds[index].fd;
    if (!args || !args[1])
        return event_sbp(server, index, args, i);
    id = strtol(args[1], &e, 10);
    while (*e && isspace((unsigned char)*e))
        e++;
    if (*e || id < 0)
        return event_sbp(server, index, args, i);
    p = find_player_by_id(server, (unsigned int)id);
    if (!p)
        return event_sbp(server, index, args, i);
    send_pin(server, fd, p);
}
