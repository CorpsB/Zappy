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
 * @return 0 on success (unit transferred), 1 on failure (src==0).
*/
static int transfer_one_unit(unsigned int *src, unsigned int *dst)
{
    if (*src == 0)
        return 1;
    (*src)--;
    (*dst)++;
    return 0;
}

void cmd_set_object(server_t *server, int index, const char *args)
{
    resources_t *pos;
    resources_t *inv;
    unsigned int *src;
    unsigned int *dst;
    int is_ok;

    if (!server || !server->poll.client_list
        || !server->poll.client_list[index].player || !args)
        return;
    pos = &server->map[
        server->poll.client_list[index].player->position[1]]
        [server->poll.client_list[index].player->position[0]];
    inv = &server->poll.client_list[index].player->inventory;
    src = select_src(args, pos, inv, &dst);
    if (!src)
        return;
    is_ok = transfer_one_unit(dst, src);
    dprintf(server->poll.client_list[index].player->socket_fd,
        is_ok == 0 ? "ok\n" : "ko\n");
}
