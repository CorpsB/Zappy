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
} command_t;

extern const command_t command_table1[];
extern const command_t command_table2[];

#endif /* !CMD_PARSER_TABLE_H_ */
