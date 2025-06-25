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

/**
 * @brief Execute the "Forward" command for a player.
 * The player moves one tile forward based on their current direction.
 * After movement, the graphical clients are notified with a "ppo" event,
 * and the player receives an "ok" confirmation.
 * @param server Pointer to the global server structure.
 * @param index Index of the player within the poll structure.
 * @param args Argument array received from the client (ignored in this case).
*/
void cmd_forward(server_t *server, int index, char **args);

/**
 * @brief Execute the "Right" command for a player.
 * Rotates the player 90 degrees to the right. After rotation,
 * the graphical clients are notified with a "ppo" event,
 * and the player receives an "ok" confirmation.
 * @param server Pointer to the global server structure.
 * @param index Index of the player within the poll structure.
 * @param args Argument array received from the client (ignored in this case).
*/
void cmd_right(server_t *server, int index, char **args);

/**
 * @brief Execute the "Left" command for a player.
 * Rotates the player 90 degrees to the left. After rotation,
 * the graphical clients are notified with a "ppo" event,
 * and the player receives an "ok" confirmation.
 * @param server Pointer to the global server structure.
 * @param index Index of the player within the poll structure.
 * @param args Argument array received from the client (ignored in this case).
*/
void cmd_left(server_t *server, int index, char **args);
void cmd_player(server_t *server, int index, teams_t *teams);
void cmd_test(server_t *server, int index, char **);

void cmd_graphic(server_t *server, int index, char **args); //=> special

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
void cmd_take_object(server_t *server, int index, char **args);


/**
 * @brief Handle the “Set <object>” player command (drop one unit).
 *
 * Moves one unit of the requested resource from the player’s inventory
 * onto the current map position, if the player owns at least one unit.
 * @param server Global server pointer.
 * @param index  Index of the client inside server->poll.client_list.
 * @param args   Null-terminated resource name.
*/
void cmd_set_object(server_t *server, int index, char **args);


/**
 * @brief Handle the “Inventory” command.
 *
 * Format sent to the client:
 *   [ food N , linemate N , deraumere N , sibur N ,
 *     mendiane N , phiras N , thystame N , time N ]\n
*/
void cmd_inventory(server_t *server, int index, char **args);


/**
 * @brief Handle the “Eject” command: push all other players
 *        one tile away in the caster's facing direction.
 *
 * Sends no protocol reply here; add your own "ok/ko" & GUI messages
 * after the push_player() calls if required by your project.
*/
void cmd_eject(server_t *srv, int idx, char **args);

/**
 * @brief Handle the “Fork” command: lay an egg on the player’s tile.
 *
 * - Creates a new egg (add_egg_at) at the player’s current position.
 * - Increments team->slots_used so a future client may connect.
 * - Updates server->eggs_count (done inside add_egg).
 * - Sends “ok\n” (success) or “ko\n” (failure) to the player.
*/
void cmd_fork(server_t *server, int index, char **args);

/**
 * @brief Handle “Connect_nbr”: send remaining free slots for the team.
 *
 * Response format : "<number>\n".
*/
void cmd_connect_nbr(server_t *server, int index, char **args);

/**
 * @brief GUI command “msz” – return map width and height.
 *
 * Client → Server :  "msz\n"
 * Server → Client :  "msz X Y\n"
 *
 * - Only a GUI may issue this command.
 */
void cmd_msz(server_t *server, int index, char **args);

/**
 * @brief GUI command bct X Y query the resources
 *        present on a specific map tile.
 *
 * Behaviour (protocol-compliant):
 *  - If the caller is not a graphical client, @c check_graphical()
 *    immediately sends "ko\\n".
 *  - If the coordinate list is missing or outside the map, reply
 *    "bad parameters\\n".
 *  - Send the canonical "bct" line with seven resource
 *    counters.
 *
 * @param server Global server context.
 * @param index  Index of the client inside @c server->poll.
 * @param args   Token array produced by @c str_to_array() for this line.
*/
void cmd_bct(server_t *server, int index, char **args);


/**
 * @brief Send the content of the entire map to the requesting graphical
 * client.
 * This function iterates over every tile of the map and sends a "bct" line
 * for each tile, following the protocol:
 * @code
 * bct X Y food linemate deraumere sibur mendiane phiras thystame\n
 * @endcode
 * This allows the graphical client to obtain a full snapshot of the map
 * state.
 * @param server Pointer to the global server structure.
 * @param index Index of the client making the request
 * (must be a valid GUI client).
 * @param args Argument array received from the client (ignored in this case).
*/
void cmd_mct(server_t *server, int index, char **args);


/**
 * @brief Handles the "tna" command from a graphical client.
 *
 * The "tna" command requests the list of all team names currently available
 * on the server. This is part of the GUI protocol and must be issued only by
 * clients identified as GUI.
 *
 * Client → Server:
 *     tna\n
 * Server → Client (for each team):
 *     tna team_name\n
 *
 * @param server Pointer to the server structure.
 * @param index Index of the client issuing the command.
 * @param args Unused for this command.
*/
void cmd_tna(server_t *server, int index, char **args);


/**
 * @brief GUI command "ppo" — gets a player position and direction.
 * Client → Server : "ppo #n"
 * Server → Client : "ppo #n X Y O"
*/
void cmd_ppo(server_t *server, int index, char **args);


/**
 * @brief GUI command “plv” – get the level of a player by ID.
 * Client → Server :  "plv <id>\n"
 * Server → Client :  "plv <id> <level>\n" or "ko\n"
 * @param server Server instance
 * @param index Index of the client in poll
 * @param args Argument array from command parser
*/
void cmd_plv(server_t *server, int index, char **args);


/**
 * @brief Handles the GUI command "pin" to return a player's inventory
 * and position.
 * Client → Server : "pin <id>\n"
 * Server → Client : "pin <id> x y q0 q1 q2 q3 q4 q5 q6\n"
 * - q0 to q6: food, linemate, deraumere, sibur, mendiane, phiras, thystame
 * - Only GUI clients are allowed to execute this command.
 * @param server Pointer to the server instance.
 * @param index Index of the client issuing the command.
 * @param args Parsed arguments array: {"pin", "<id>", NULL}
*/
void cmd_pin(server_t *server, int index, char **args);


/**
 * @brief Handles the "sst" command from a GUI client to set server frequency.
 * Validates the input, updates the server frequency if valid, and notifies
 * all GUI clients of the change. If input is invalid, sends
 * "ko" to the client.
 * @param server The server instance receiving the command.
 * @param index The index of the client in the server's poll array.
 * @param args The parsed command arguments from the GUI client.
*/
void cmd_sst(server_t *server, int index, char **args);


/**
 * @brief Handles the "sgt" command from a GUI client.
 * Sends back the current game frequency (ticks per second)
 * to the requesting GUI client.
 * If the client is not a graphical client, a "ko" message is sent instead.
 * @param server The main server structure.
 * @param index Index of the client sending the command.
 * @param args Arguments of the command (should be NULL or ignored).
*/
void cmd_sgt(server_t *server, int index, char **args);

#endif /* !CMD_H_ */
