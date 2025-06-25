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

static int get_ressource(server_t *server, int y, int x, r_ressource_t type)
{
    if (type == FOOD)
        return server->map[y][x].food;
    if (type == LINEMATE)
        return server->map[y][x].linemate;
    if (type == DERAUMERE)
        return server->map[y][x].deraumere;
    if (type == SIBUR)
        return server->map[y][x].sibur;
    if (type == MENDIANE)
        return server->map[y][x].mendiane;
    if (type == PHIRAS)
        return server->map[y][x].phiras;
    if (type == THYSTAME)
        return server->map[y][x].thystame;
    return 0;
}

static void del_ressource(server_t *server, int y, int x, r_ressource_t type)
{
    if (type == FOOD)
        server->map[y][x].food = 0;
    if (type == LINEMATE)
        server->map[y][x].linemate = 0;
    if (type == DERAUMERE)
        server->map[y][x].deraumere = 0;
    if (type == SIBUR)
        server->map[y][x].sibur = 0;
    if (type == MENDIANE)
        server->map[y][x].mendiane = 0;
    if (type == PHIRAS)
        server->map[y][x].phiras = 0;
    if (type == THYSTAME)
        server->map[y][x].thystame = 0;
}

static void del_map_inventory(server_t *server, r_ressource_t type, int nbr)
{
    if (type == FOOD)
        server->actual_map_inventory.food -= nbr;
    if (type == LINEMATE)
        server->actual_map_inventory.linemate -= nbr;
    if (type == DERAUMERE)
        server->actual_map_inventory.deraumere -= nbr;
    if (type == SIBUR)
        server->actual_map_inventory.sibur -= nbr;
    if (type == MENDIANE)
        server->actual_map_inventory.mendiane -= nbr;
    if (type == PHIRAS)
        server->actual_map_inventory.phiras -= nbr;
    if (type == THYSTAME)
        server->actual_map_inventory.thystame -= nbr;
}

static void player_add_ressource(server_t *, player_t *player,
    r_ressource_t type, int quanity)
{
    if (type == FOOD)
        player->inventory.food += quanity;
    if (type == LINEMATE)
        player->inventory.linemate += quanity;
    if (type == DERAUMERE)
        player->inventory.deraumere += quanity;
    if (type == SIBUR)
        player->inventory.sibur += quanity;
    if (type == MENDIANE)
        player->inventory.mendiane += quanity;
    if (type == PHIRAS)
        player->inventory.phiras += quanity;
    if (type == THYSTAME)
        player->inventory.thystame += quanity;
}

static void take_obj(server_t *srv, r_ressource_t obj, int index)
{
    player_t *pl = srv->poll.client_list[index].player;
    int nbr = get_ressource(srv, pl->position[0], pl->position[1], obj);
    int *pos = malloc(sizeof(int) * 2);

    if (!pos)
        logger(srv, "MALLOC : POS", PERROR, true);
    pos[0] = pl->position[0];
    pos[1] = pl->position[1];
    player_add_ressource(srv, pl, obj, nbr);
    del_ressource(srv, pl->position[0], pl->position[1], obj);
    change_arround(srv, pos, obj, density_table[obj].repartition_value * -1);
    del_map_inventory(srv, obj, nbr);
    event_pgt(srv, pl->id, obj);
    event_pin(srv, pl);
    event_bct_per_tile(srv, pl->position[0], pl->position[1]);
    if (pos)
        free(pos);
}

void cmd_take_object(server_t *server, int index, char **args)
{
    for (int i = FOOD; i < THYSTAME; i++) {
        if (strncmp(args[1], density_table[i].name,
            strlen(density_table[i].name)) == 0)
                take_obj(server, (r_ressource_t)i, index);
    }
}
