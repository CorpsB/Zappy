/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_parser_table
*/

/**
 * @file cmd_parser_table.h
 * @brief Defines the command tables for player and graphical clients in
 * Zappy.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * This file declares the structures and arrays used to map command names
 * to their respective functions for both player and graphical clients.
 * It centralizes the expected arguments and execution timing for commands.
*/

#ifndef CMD_PARSER_TABLE_H_
    #define CMD_PARSER_TABLE_H_

    #include "structure.h"

/**
 * @brief Function pointer type for command callbacks.
 * All commands for players or graphical clients must follow this signature.
*/
typedef void (*command_func_t)(server_t *server, int index, char **args);

/**
 * @brief Structure describing a player command entry.
 * Each player command has:
 * - A string name
 * - A function pointer
 * - The expected number of arguments
 * - The execution time in ticks (Zappy protocol specific)
*/
typedef struct {
    const char *name;
    command_func_t func;
    const int argument_nbr;
    const unsigned int time;
} player_command_t;


/**
 * @brief Structure describing a graphical client command entry.
 * Each graphical command has:
 * - A string name
 * - A function pointer
 * - The expected number of arguments
*/
typedef struct {
    const char *name;
    command_func_t func;
    const int argument_nbr;
} gui_command_t;

extern const player_command_t player_command_table[];
extern const gui_command_t gui_command_table[];

#endif /* !CMD_PARSER_TABLE_H_ */
