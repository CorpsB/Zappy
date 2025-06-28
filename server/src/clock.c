/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** clock
*/

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

static double get_elapsed_time_units(zappy_clock_t *clock)
{
    struct timespec now;
    double elapsed_sec;

    clock_gettime(CLOCK_MONOTONIC, &now);
    elapsed_sec = (now.tv_sec - clock->last_tick.tv_sec)
        + (now.tv_nsec - clock->last_tick.tv_nsec) / 1e9;
    return elapsed_sec * (double)clock->freq;
}

void update_clock(zappy_clock_t *clock)
{
    clock->accumulator += get_elapsed_time_units(clock);
    clock_gettime(CLOCK_MONOTONIC, &clock->last_tick);
}

zappy_clock_t *init_clock(server_t *server, size_t freq)
{
    zappy_clock_t *clock = malloc(sizeof(zappy_clock_t));

    if (!clock)
        logger(server, "MALLOC : CLOCK", PERROR, true);
    clock->freq = freq;
    clock->accumulator = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &clock->last_tick);
    return clock;
}
