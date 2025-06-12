/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** cmd
*/

#ifndef CMD_H_
    #define CMD_H_

    #include "include/include.h"
    #include "include/function.h"
    #include "include/structure.h"

void cmd_forward(server_t *server, int index, const char *args);
void cmd_right(server_t *server, int index, const char *args);
void cmd_left(server_t *server, int index, const char *args);
void cmd_look(server_t *server, int index, const char *args);

#endif /* !CMD_H_ */
