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

void cmd_forward(server_t *server, int index, char **args);
void cmd_right(server_t *server, int index, char **args);
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
 * Format de réponse : "<number>\n".
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
 * @brief Handle the GUI command "mct" (map content).
 *
 * This command returns the resource content of every tile on the map
 * using the same format as the "bct" command.
 *
 * @param server Pointer to the global server structure.
 * @param index  Index of the client in the poll list.
 * @param args   Command arguments (unused).
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

#endif /* !CMD_H_ */
