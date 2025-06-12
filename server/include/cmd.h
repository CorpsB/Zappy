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


/**
 * @brief Handle the Zappy “Take <object>” command.
 *
 * The player at poll index @p idx attempts to pick up one unit of the
 * resource named in @p arg. If the tile contains at least one unit,
 * the resource is moved from the map to the player’s inventory.
 * @param server    Pointer to the global server structure.
 * @param index     Index of the client in @c s->poll.client_list.
 * @param args      Null-terminated resource name sent by the client.
*/
void cmd_take_object(server_t *server, int index, const char *args);

#endif /* !CMD_H_ */
