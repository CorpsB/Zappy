/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_look.c
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

char *append_token(char *dest, const char *token, server_t *srv)
{
    char *out = NULL;

    if (dest == NULL) {
        if (asprintf(&out, "%s", token) == -1)
            logger(srv, "ASPRINTF : LOOK", PERROR, true);
    } else {
        if (asprintf(&out, "%s%s", dest, token) == -1)
            logger(srv, "ASPRINTF : LOOK", PERROR, true);
        free(dest);
    }
    return out;
}

static unsigned int player_on_team(teams_t *t, int y, int x)
{
    unsigned int nb = 0;

    for (player_t *p = t->player; p; p = p->next)
        if ((int)p->position[1] == x && (int)p->position[0] == y)
            nb++;
    return nb;
}

unsigned int players_at(server_t *srv, int y, int x)
{
    unsigned int nb = 0;

    for (teams_t *t = srv->teams; t; t = t->next)
        nb += player_on_team(t, y, x);
    return nb;
}

static unsigned int egg_on_team(teams_t *t, int y, int x)
{
    unsigned int nb = 0;

    for (eggs_t *e = t->egg; e; e = e->next)
        if ((int)e->position[1] == x && (int)e->position[0] == y)
            nb++;
    return nb;
}

unsigned int eggs_at(server_t *srv, int y, int x)
{
    unsigned int nb = 0;

    for (teams_t *t = srv->teams; t; t = t->next)
        nb += egg_on_team(t, y, x);
    return nb;
}

static char *build_look(server_t *srv, player_t *pl)
{
    char *out = strdup("[");
    char *tmp = NULL;

    for (unsigned int lvl = 0; lvl <= pl->lvl; ++lvl) {
        tmp = build_line(srv, pl, (int)lvl);
        out = append_token(out, tmp, srv);
        if (lvl < pl->lvl)
            out = append_token(out, ", ", srv);
        free(tmp);
    }
    out = append_token(out, "]", srv);
    return out;
}

void cmd_look(server_t *srv, int idx, char **)
{
    player_t *pl = srv->poll.client_list[idx].player;
    char *msg = build_look(srv, pl);

    dprintf(pl->socket_fd, "%s\n", msg);
    free(msg);
}
