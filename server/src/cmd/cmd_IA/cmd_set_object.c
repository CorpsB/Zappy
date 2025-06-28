/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_set_object.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"
#include "include/density_table.h"

static int get_ressource(server_t *, player_t *pl, r_ressource_t type)
{
    if (type == FOOD)
        return pl->inventory.food;
    if (type == LINEMATE)
        return pl->inventory.linemate;
    if (type == DERAUMERE)
        return pl->inventory.deraumere;
    if (type == SIBUR)
        return pl->inventory.sibur;
    if (type == MENDIANE)
        return pl->inventory.mendiane;
    if (type == PHIRAS)
        return pl->inventory.phiras;
    if (type == THYSTAME)
        return pl->inventory.thystame;
    return 0;
}

static void pl_del_ressource(server_t *, player_t *pl,
    r_ressource_t type)
{
    if (type == FOOD)
        pl->inventory.food = 0;
    if (type == LINEMATE)
        pl->inventory.linemate = 0;
    if (type == DERAUMERE)
        pl->inventory.deraumere = 0;
    if (type == SIBUR)
        pl->inventory.sibur = 0;
    if (type == MENDIANE)
        pl->inventory.mendiane = 0;
    if (type == PHIRAS)
        pl->inventory.phiras = 0;
    if (type == THYSTAME)
        pl->inventory.thystame = 0;
}

static void add_theorique_map_inventory(server_t *server,
    r_ressource_t type, int nbr)
{
    if (type == FOOD)
        server->actual_map_inventory.food += nbr;
    if (type == LINEMATE)
        server->actual_map_inventory.linemate += nbr;
    if (type == DERAUMERE)
        server->actual_map_inventory.deraumere += nbr;
    if (type == SIBUR)
        server->actual_map_inventory.sibur += nbr;
    if (type == MENDIANE)
        server->actual_map_inventory.mendiane += nbr;
    if (type == PHIRAS)
        server->actual_map_inventory.phiras += nbr;
    if (type == THYSTAME)
        server->actual_map_inventory.thystame += nbr;
}

static void map_add_ressource(server_t *server, int *pos,
    r_ressource_t type, int quanity)
{
    if (type == FOOD)
        server->map[pos[0]][pos[1]].food += quanity;
    if (type == LINEMATE)
        server->map[pos[0]][pos[1]].linemate += quanity;
    if (type == DERAUMERE)
        server->map[pos[0]][pos[1]].deraumere += quanity;
    if (type == SIBUR)
        server->map[pos[0]][pos[1]].sibur += quanity;
    if (type == MENDIANE)
        server->map[pos[0]][pos[1]].mendiane += quanity;
    if (type == PHIRAS)
        server->map[pos[0]][pos[1]].phiras += quanity;
    if (type == THYSTAME)
        server->map[pos[0]][pos[1]].thystame += quanity;
}

static void set_obj(server_t *server, r_ressource_t obj, int index)
{
    player_t *pl = server->poll.client_list[index].player;
    int nbr = get_ressource(server, pl, obj);
    int *pos = malloc(sizeof(int) * 2);

    if (!pos)
        logger(server, "MALLOC : POSITION", PERROR, true);
    if (nbr <= 0) {
        dprintf(pl->socket_fd, "ko\n");
        return;
    }
    pos[0] = pl->position[0];
    pos[1] = pl->position[1];
    map_add_ressource(server, pos, obj, nbr);
    pl_del_ressource(server, pl, obj);
    change_arround(server, pos, obj, density_table[obj].repartition_value);
    add_theorique_map_inventory(server, obj, nbr);
    event_pdr(server, pl->id, obj);
    event_pin(server, pl);
    event_bct_per_tile(server, pl->position[0], pl->position[1]);
    if (pos)
        free(pos);
    dprintf(pl->socket_fd, "ok\n");
}

void cmd_set_object(server_t *server, int index, char **args)
{
    for (int i = FOOD; i < THYSTAME; i++) {
        if (strncmp(args[1], density_table[i].name,
            strlen(density_table[i].name)) == 0) {
                set_obj(server, (r_ressource_t)i, index);
                return;
            }
    }
    dprintf(server->poll.pollfds[index].fd, "ko\n");
}
