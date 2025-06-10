/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** parser
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

int parse_port(char *str, server_t *server, int i)
{
    int nbr = atoi(str);

    if (nbr <= 0) {
        write(2, "[ERROR] - A port cannot be NULL or negative.\n", 45);
        return -1;
    }
    server->port = nbr;
    return i + 1;
}

int parse_width(char *str, server_t *server, int i)
{
    int nbr = atoi(str);

    if (nbr <= 0) {
        write(2, "[ERROR] - Width cannot be NULL or negative.\n", 45);
        return -1;
    }
    server->width = nbr;
    return i + 1;
}

int parse_height(char *str, server_t *server, int i)
{
    int nbr = atoi(str);

    if (nbr <= 0) {
        write(2, "[ERROR] - Height cannot be NULL or negative.\n", 45);
        return -1;
    }
    server->height = nbr;
    return i + 1;
}

int parse_client(char *str, server_t *server, int i)
{
    int nbr = atoi(str);

    if (nbr <= 0) {
        write(2, "[ERROR] - Client limit cannot be NULL or negative.\n", 45);
        return -1;
    }
    server->max_connections_per_team = nbr;
    return i + 1;
}

int parse_frequency(char *str, server_t *server, int i)
{
    int nbr = atoi(str);

    if (nbr <= 0) {
        write(2, "[ERROR] - Frequency cannot be NULL or negative.\n", 45);
        return -1;
    }
    server->frequency = nbr;
    return i + 1;
}
