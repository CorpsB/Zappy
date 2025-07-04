/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** clock
*/

/**
 * @file clock.c
 * @brief Server clock management for time-based updates in Zappy.
 *
 * Handles initialization and updates of the server clock using `clock_gettime`
 * with `CLOCK_MONOTONIC`, and manages the time accumulator based on a
 * configurable frequency (ticks per second).
 *
 * Used to manage the game loop and event timing.
 *
 * @author Noé Carabin
 * @date 2025
 */

#include "include/include.h"
#include "include/function.h"
#include "include/structure.h"

/**
 * @brief Get the elapsed time units since the last tick.
 * Calculates the time difference from the last recorded tick and converts it
 * to the server's time units based on the clock frequency.
 * @param clock Pointer to the clock structure.
 * @return double Elapsed time units.
*/
static double get_elapsed_time_units(zappy_clock_t *clock)
{
    struct timespec now;
    double elapsed_sec;

    clock_gettime(CLOCK_MONOTONIC, &now);
    elapsed_sec = (now.tv_sec - clock->last_tick.tv_sec)
        + (now.tv_nsec - clock->last_tick.tv_nsec) / 1e9;
    return elapsed_sec * (double)clock->freq;
}

void update_clock(zappy_clock_t *clock, server_t *server)
{
    clock->freq = server->frequency;
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
    server->clock = clock;
    return clock;
}
