/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd_parser_table
*/

#ifndef CMD_PARSER_TABLE_H_
    #define CMD_PARSER_TABLE_H_

    #include "structure.h"

typedef void (*command_func_t)(server_t *server, int index, char **args);

typedef struct {
    const char *name;
    command_func_t func;
    const int argument_nbr;
    const unsigned int time;
} player_command_t;

typedef struct {
    const char *name;
    command_func_t func;
    const int argument_nbr;
} gui_command_t;

extern const player_command_t player_command_table[];
extern const gui_command_t gui_command_table[];

#endif /* !CMD_PARSER_TABLE_H_ */
