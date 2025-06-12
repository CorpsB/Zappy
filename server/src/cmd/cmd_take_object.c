/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_set_object.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Move one unit of a resource from @p src to @p dst.
 *
 * Does nothing if @p src is already zero.
 *
 * @param src Pointer to the source counter (will be decremented).
 * @param dst Pointer to the destination counter (will be incremented).
*/
static void transfert_one_unit(unsigned int *src, unsigned int *dst)
{
    if (*src == 0)
        return;
    (*src)--;
    (*dst)++;
}

/**
 * @brief Resolve “mendiane”.
*/
static unsigned int *select_src4(const char *args,
    resources_t *pos, resources_t *inv, unsigned int **dst)
{
    switch (args[0]) {
    case 'm':
        if (strcmp(args, "mendiane") == 0) {
            *dst = &inv->mendiane;
            return &pos->mendiane;
        }
        break;
    default:
        break;
    }
    return NULL;
}

/**
 * @brief Resolve “deraumere” or “sibur”; otherwise delegates downward.
*/
static unsigned int *select_src3(const char *args,
    resources_t *pos, resources_t *inv, unsigned int **dst)
{
    switch (args[0]) {
    case 'd':
        if (strcmp(args, "deraumere") == 0) {
            *dst = &inv->deraumere;
            return &pos->deraumere;
        }
        break;
    case 's':
        if (strcmp(args, "sibur") == 0) {
            *dst = &inv->sibur;
            return &pos->sibur;
        }
        break;
    default:
        break;
    }
    return select_src4(args, pos, inv, dst);
}

/**
 * @brief Resolve “phiras” or “thystame”; otherwise delegates downward.
 *
 * Identical semantics to select_src(), but for a second subset of names.
*/
static unsigned int *select_src2(const char *args,
    resources_t *pos, resources_t *inv, unsigned int **dst)
{
    switch (args[0]) {
    case 'p':
        if (strcmp(args, "phiras") == 0) {
            *dst = &inv->phiras;
            return &pos->phiras;
        }
        break;
    case 't':
        if (strcmp(args, "thystame") == 0) {
            *dst = &inv->thystame;
            return &pos->thystame;
        }
        break;
    default:
        break;
    }
    return select_src3(args, pos, inv, dst);
}

/**
 * @brief Resolve “food” or “linemate”.
 *
 * If @p args matches one of those names, sets *@p dst to the
 * player-inventory counter and returns the pointer to the
 * corresponding map-pos counter. Otherwise delegates to select_src2().
 * @param args      Resource name received from the client.
 * @param pos      Pointer to the map tile’s resource structure.
 * @param inv       Pointer to the player’s inventory structure.
 * @param dst       [out] receives the inventory counter to update.
 * @return Pointer to the map-pos counter, or NULL if the name is
 *         unknown at this level.
*/
static unsigned int *select_src(const char *args,
    resources_t *pos, resources_t *inv, unsigned int **dst)
{
    switch (args[0]) {
    case 'f':
        if (strcmp(args, "food") == 0) {
            *dst = &inv->food;
            return &pos->food;
        }
        break;
    case 'l':
        if (strcmp(args, "linemate") == 0) {
            *dst = &inv->linemate;
            return &pos->linemate;
        }
        break;
    default:
        break;
    }
    return select_src2(args, pos, inv, dst);
}

void cmd_take_object(server_t *server, int index, const char *args)
{
    resources_t *pos;
    resources_t *inv;
    unsigned int *src;
    unsigned int *dst;

    pos = &server->map[
        server->poll.client_list[index].player->position[1]]
        [server->poll.client_list[index].player->position[0]];
    inv = &server->poll.client_list[index].player->inventory;
    src = select_src(args, pos, inv, &dst);
    if (!src)
        return;
    transfer_one_unit(src, dst);
}
