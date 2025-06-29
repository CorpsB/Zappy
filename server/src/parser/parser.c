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
    char *endptr;
    long nbr = strtol(str, &endptr, 10);

    if (*endptr != '\0' || nbr <= 0) {
        logger(server, "A port cannot be NULL or negative.", ERROR, false);
        return -1;
    }
    server->port = nbr;
    return i + 1;
}

int parse_width(char *str, server_t *server, int i)
{
    char *endptr;
    long nbr = strtol(str, &endptr, 10);

    if (*endptr != '\0' || nbr <= 0) {
        logger(server, "Width cannot be NULL or negative.", ERROR, false);
        return -1;
    }
    server->width = nbr;
    return i + 1;
}

int parse_height(char *str, server_t *server, int i)
{
    char *endptr;
    long nbr = strtol(str, &endptr, 10);

    if (*endptr != '\0' || nbr <= 0) {
        logger(server, "Height cannot be NULL or negative.", ERROR, false);
        return -1;
    }
    server->height = nbr;
    return i + 1;
}

int parse_client(char *str, server_t *server, int i)
{
    char *endptr;
    long nbr = strtol(str, &endptr, 10);

    if (*endptr != '\0' || nbr <= 0) {
        logger(server, "Client limit cannot be NULL or negative.",
            ERROR, false);
        return -1;
    }
    server->starter_eggs_number = nbr;
    return i + 1;
}

int parse_frequency(char *str, server_t *server, int i)
{
    char *endptr;
    long nbr = strtol(str, &endptr, 10);

    if (*endptr != '\0' || nbr <= 0) {
        logger(server, "Frequency cannot be NULL or negative.", ERROR, false);
        return -1;
    }
    server->frequency = nbr;
    return i + 1;
}
