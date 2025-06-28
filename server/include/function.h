/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** fucntion
*/

/**
 * @file function.h
 * @brief Declares all utility functions, server logic and graphical
 * events for Zappy server project.
 * @author Noé Carabin
 * @version 1.0
 * @date 2025-06
 * @details
 * This header centralizes the prototypes for:
 * - Utility functions (parsing, resource handling, logging)
 * - Server initialization and management
 * - Game logic (players, teams, eggs)
 * - All graphical events following the Zappy protocol (e.g., event_ppo,
 * event_pnw, event_bct, etc.)
 * These functions ensure the correct functioning of the game server
 * and communication with graphical clients.
*/

#ifndef FUCNTION_H_
    #define FUCNTION_H_

    #include "include/structure.h"

//utils

/**
 * @brief Function that check if the client is a GUI.
 *
 * @param server Global server pointer (for id & counters).
 * @param index The index of the player.
 * @return return 1 if the client is not a GUI (PLAYER, LISTEN, UNKNOW)
 * return 0 if the client is a GUI.
*/

/**
 * @brief Print the content of a resource inventory to a file descriptor.
 * @param inv The resource inventory to display.
 * @param fd The file descriptor to write to.
*/
void see_inventory(resources_t inv, int fd);
void see_all_players(player_t *players, int fd);
//server
server_t *add_server(void);
void see_server(server_t *server, int fd);
void free_server(server_t *server);
void see_poll(poll_t poll, int fd, int size);
void debug_server(server_t *server);
void free_poll(server_t *server);
//teams
void add_teams(server_t *server, char *name);
void see_one_team(teams_t *team, int fd);
void see_teams(teams_t *teams, int fd);
void free_all_teams(teams_t *teams);
//player
/**
 * @brief Searches for a player by ID across all teams.
 * @param server The server structure containing teams.
 * @param id The target player ID.
 * @return player_t* if found, NULL otherwise.
*/
player_t *find_player_by_id(const server_t *server, unsigned int id);
void add_player(server_t *server, int socket, teams_t *teams);
void free_all_player(player_t *player);
//cmd parser
char **str_to_array(char *str, char *separator);

void run_server(server_t *server);
void cmd_parser(server_t *server, int index, char *cmd);

//EGGS
/**
 * @brief Free an entire linked list of eggs.
 * @param eggs Pointer to the head of the egg list.
*/
void free_all_egs(eggs_t *eggs);
void see_all_eggs(eggs_t *eggs, int fd);
/**
 * @brief Allocate a new egg and insert it at the head of a team list.
 *
 * @param server      Pointer to the global server structure.
 * @param creator_id  ID of the player who laid the egg (for logs/debug).
 * @param teams       Pointer to the team that owns the egg.
 *
 * @pre  @p server and @p teams are non-NULL.
 * @post
 *  - `teams->egg` points to the newly created egg.
 *  - `server->eggs_count` is incremented.
 *
 * @throw Exits the program with code 84 if memory allocation fails.
 *
 * @details
 *  - Initial position is chosen randomly within the map bounds.
 *  - Runs in O(1) time (head insertion).
*/
void add_eggs(server_t *server, unsigned int creator_id, teams_t *teams,
    int *pos);

/**
 * @brief Walk through and display an egg linked list.
 *
 * If the list is empty, prints “\[NO EGGS]”; otherwise calls
 * see_one_egg() for, each node.
 *
 * @param eggs Head of the egg list (may be NULL).
 *
 * @details Complexity : O(n) where n is the number of eggs.
*/
void see_eggs(eggs_t *head, int fd);

/**
 * @brief Search an egg by its id
 *
 * @param server  Server structure pointer.
 * @param id      Id of the eggs that we need.
 *
 * @return        A pointer on the structure 'eggs_t' if find, else NULL.
 */
eggs_t *search_egg_by_id(server_t *server, unsigned int id);


//resources
/**
 * @brief Initialize a resources_t structure with all values set to 0.
 * @return The initialized resources structure.
*/
resources_t create_resources(void);

//parser
/**
 * @brief Parse the port number for the server.
 * @param str The string containing the port number.
 * @param server Pointer to the server structure to update.
 * @param i Current index in the argument array.
 * @return The updated index if successful, -1 on error.
*/
int parse_port(char *str, server_t *server, int i);

/**
 * @brief Parse the width of the game map.
 * @param str The string containing the map width.
 * @param server Pointer to the server structure to update.
 * @param i Current index in the argument array.
 * @return The updated index if successful, -1 on error.
*/
int parse_width(char *str, server_t *server, int i);

/**
 * @brief Parse the height of the game map.
 * @param str The string containing the map height.
 * @param server Pointer to the server structure to update.
 * @param i Current index in the argument array.
 * @return The updated index if successful, -1 on error.
*/
int parse_height(char *str, server_t *server, int i);

/**
 * @brief Parse the maximum number of starter eggs per team.
 * @param str The string containing the client (starter eggs) limit.
 * @param server Pointer to the server structure to update.
 * @param i Current index in the argument array.
 * @return The updated index if successful, -1 on error.
*/
int parse_client(char *str, server_t *server, int i);

/**
 * @brief Parse the frequency of the server ticks.
 * @param str The string containing the tick frequency.
 * @param server Pointer to the server structure to update.
 * @param i Current index in the argument array.
 * @return The updated index if successful, -1 on error.
*/
int parse_frequency(char *str, server_t *server, int i);

/**
 * @brief Parse and register team names for the Zappy server.
 * This function iterates over the argument array starting at index `i + 1`,
 * and adds each team name to the server until it encounters an option
 * starting with '-'.
 * @param av The array of command-line arguments.
 * @param server Pointer to the server structure to update.
 * @param i Current index of the "-n" argument in the array.
 * @return The index of the last processed argument corresponding to a
 * team name.
*/
int parse_teams(char **av, server_t *server, int i);

//logs
/**
 * @brief Print a log message to stderr and optionally to the debug log.
 * @param server Pointer to the server structure.
 * @param message The message to log.
 * @param log The log level (ERROR, PERROR, DEBUG, INFO).
 * @param is_end If true, the server is freed and the program exits.
*/
void logger(server_t *server, char *message, logs_t log, bool is_end);

/**
 * @brief Debug function to print quantities and repartition maps of all
 * resources. 
 * Iterates through all resource types and prints both the tile quantities
 * and repartition map values for each resource in a readable format.
 * Useful for visualizing resource distribution and debugging the map state.
 * @param server Pointer to the server structure containing the map and
 * resources.
*/
void debug_print_resource_map(server_t *server);

/**
 * @brief Allocates and initializes the server's map with empty resource
 * cells.
 * Allocates memory for a 2D array representing the map grid. Each cell is
 * zero-initialized. Calls other functions to reset inventory, define goals,
 * initialize repartition cells, update the map and spawn eggs.
 * @param server Pointer to the server for which the map is generated.
*/
void map_generator(server_t *server);

/**
 * @brief Updates the map by spawning resources until all goals are met.
 * Repeatedly calls ressource_update for each resource type if the
 * actual count
 * is below the goal, looping until all goals are satisfied.
 * @param server Pointer to the server containing the map and inventories.
*/
void map_update(server_t *server);

/**
 * @brief Updates the repartition map influence around a position
 * based on a weight.
 * Calls draw_circle in a square radius of size 'weight' around 'pos',
 * adjusting repartition values with decreasing weight.
 * @param srv Pointer to the server containing the map.
 * @param pos Array of two integers [row, column] representing the position.
 * @param type Resource type to update.
 * @param weight Influence radius and intensity.
*/
void change_arround(server_t *server, int *pos, r_ressource_t type,
    int weight);

/**
 * @brief Send a message to all connected graphical clients.
 * @param server Pointer to the server structure.
 * @param message The message to send (must be a valid string).
*/
void send_to_all_gui(server_t *server, char *message);
/**
 * @brief Count the number of eggs in a linked list.
 * @param eggs Pointer to the head of the egg list.
 * @return The number of eggs in the list.
*/
int eggs_size(eggs_t *eggs);

/**
 * @brief Generate a starter egg at a random position for a team.
 * @param server Pointer to the server structure (used for map
 * bounds and egg ID).
 * @param teams Pointer to the team receiving the new egg.
*/
void generate_starter_eggs(server_t *server, teams_t *teams);

/**
 * @brief Notify the GUI and the player that a player has died.
 * GUI clients receive: pdi <id>
 * The player receives: dead
 * @param server Pointer to the game server.
 * @param player Pointer to the player who has died.
*/
void event_pdi(server_t *server, player_t *player, bool is_open);


//EVENTS

/**
 * @brief Notify all GUI clients with the map size.
 *
 * @param server The main server structure containing map and clients.
 */
void event_msz(server_t *server);

/**
 * @brief Broadcast the entire map content to all connected graphical clients.
 * This function is typically called when a new graphical client connects,
 * allowing them to synchronize their map view.
 * @param server Pointer to the global server structure.
*/
void event_bct(server_t *server);

void event_pdi_by_index(server_t *server, int index);

/**
 * @brief Sends a "sgt" event broadcasting the server's frequency value.
 * This function formats and broadcasts a message containing the server's
 * frequency parameter to all connected GUI clients.
 * If the server pointer is NULL or message formatting fails, it safely
 * returns or logs an error.
 * @param server Pointer to the server containing the frequency value.
*/
void event_sgt(server_t *server);

/**
 * @brief Sends "tna" events listing all team names.
 * This function iterates through the linked list of teams in the server,
 * sending a "tna" message with each team's name to all connected GUI clients.
 * If the server or team list is NULL, the function returns immediately.
 * If message formatting fails, an error is logged.
 * @param server Pointer to the server containing the teams.
*/
void event_tna(server_t *server);

/**
 * @brief Handles the "pfk" event triggered by a player laying an egg.
 * This function creates a new egg from the player, then broadcasts a
 * "pfk" event
 * to all connected GUI clients. It also triggers the "enw" event with
 * the new egg.
 * If any step fails, the function safely returns without action.
 * @param server Pointer to the server structure managing the
 * game state and clients.
 * @param player Pointer to the player who triggered the event.
*/
void event_pfk(server_t *server, player_t *player);


/**
 * @brief Notify all graphical clients that an egg has been laid.
 * Sends an "enw" message with information about the new egg.
 * If the player pointer is provided, their ID is used as the creator;
 * otherwise, the egg's creator_id is used.
 * Protocol format:
 * @code
 * enw #<egg_id> #<creator_id> <x> <y>\n
 * @endcode
 * @param server Pointer to the global server structure.
 * @param player Pointer to the player who laid the egg
 * (optional, can be NULL).
 * @param egg Pointer to the egg structure.
*/
void event_enw(server_t *server, player_t *player, eggs_t *egg);

/**
 * @brief Send "enw" messages for all existing eggs to all connected
 * graphical clients.
 * This is typically called when a graphical client connects,
 * to synchronize them with the current state of the game.
 * @param server Pointer to the global server structure.
*/
void event_new_gui_enw(server_t *server);

/**
 * @brief Notify all graphical clients that an egg has hatched.
 * Sends the "ebo" protocol line to all graphical clients to indicate
 * that the egg with the given ID has successfully hatched.
 * Protocol format:
 * @code
 * ebo #<egg_id>\n
 * @endcode
 * @param server Pointer to the global server structure.
 * @param egg_id Unique identifier of the hatched egg.
*/
void event_ebo(server_t *server, unsigned int egg_id);

/**
 * @brief Send an "enw" message to a graphical client for a specific egg.
 * This message informs the client that an egg has been laid.
 * Protocol format:
 * @code
 * enw #<egg_id> #<creator_id> <x> <y>\n
 * @endcode
 * @param fd File descriptor of the graphical client.
 * @param egg Pointer to the egg structure.
*/
void send_enw(int fd, eggs_t *egg);

/**
 * @brief Creates a new egg associated with the given player.
 * This function allocates and initializes a new egg structure
 * based on the player's
 * team and position. The egg's ID is generated using the team's ID combined
 * with a random number.
 * The new egg is added to the front of the team's egg linked list.
 * @param player Pointer to the player from whom the egg is created.
 * @return Pointer to the newly created egg, or NULL if player
 * or player's team is invalid, or if memory allocation fails.
*/
eggs_t *create_egg_from_player(player_t *player);

/**
 * @brief Remove a specific egg from a team's egg list.
 * @param server Pointer to the server structure (unused, present
 * for consistency).
 * @param teams Pointer to the team containing the egg.
 * @param egg Pointer to the egg to remove.
*/
void del_egg(server_t *server, teams_t *teams, eggs_t *egg);

/**
 * @brief Select a random egg from the team, remove it, and return its
 * position.
 * @param server Pointer to the server structure (used for logging).
 * @param teams Pointer to the team from which to hatch an egg.
 * @return A dynamically allocated array containing the [x, y] position
 * of the egg.
 * @warning The caller is responsible for freeing the returned array.
*/
unsigned int *hatching_egg(server_t *server, teams_t *teams);
void complete_team_data(server_t *server);

/**
 * @brief Sends a "pnw" event announcing a new player on the map.
 * This function constructs and broadcasts a message containing the
 * player's ID,
 * position coordinates, direction, level, and team name to all
 * connected GUI clients.
 * After broadcasting the "pnw" event, it also sends a "pin"
 * event to report the player's status.
 * The function returns early if the server, player, or
 * player's team is NULL.
 * If message formatting fails, an error is logged.
 * @param server Pointer to the server managing the game state
 * and connected clients.
 * @param player Pointer to the player being announced.
*/
void event_pnw(server_t *server, player_t *player);

/**
 * @brief Sends a "pin" event broadcasting the player's current status.
 * This function constructs and sends a message containing the player's ID,
 * position coordinates, and the quantities of each resource in their
 * inventory.
 * It ignores the call if the server or player is NULL, or if the player
 * is marked as dead.
 * The message is broadcast to all connected GUI clients.
 * If message formatting fails, an error is logged.
 * @param server Pointer to the server managing game state and clients.
 * @param player Pointer to the player whose status is being reported.
*/
void event_pin(server_t *server, player_t *player);

/**
 * @brief Sends a "ppo" event broadcasting a player's position and direction.
 * This function formats a message containing the player's ID, position
 * coordinates,
 * and direction, then broadcasts it to all connected GUI clients.
 * The event is skipped if the server or player pointer is NULL, or if
 * the player is marked as dead.
 * If message formatting fails, an error is logged.
 * @param server Pointer to the server managing game state and clients.
 * @param player Pointer to the player whose position is being reported.
*/
void event_ppo(server_t *server, player_t *player);

/**
 * @brief Notify all graphical clients that an egg has been destroyed.
 * Sends the "edi" protocol line to all graphical clients to indicate
 * that the egg with the given ID has been removed from the game
 * (e.g., destroyed).
 * Protocol format:
 * @code
 * edi #<egg_id>\n
 * @endcode
 * @param server Pointer to the global server structure.
 * @param egg_id Unique identifier of the destroyed egg.
*/
void event_edi(server_t *server, unsigned int egg_id);

void free_table(char **table);

/**
 * @brief Notify all graphical clients of a resource change on a specific
 * tile.
 * Sends the "bct" line for the given tile to all graphical clients,
 * typically after an action modifies the resources of the tile.
 * @param server Pointer to the global server structure.
 * @param y Y coordinate of the tile.
 * @param x X coordinate of the tile.
*/
void event_bct_per_tile(server_t *server, int y, int x);

/**
 * @brief Sends a "pgt" event indicating a resource update for a player.
 * This function formats a message reporting that a player identified by `id`
 * has performed an action related to a resource of the given `type`.
 * The message is then broadcast to all connected GUI clients.
 * If message formatting fails, an error is logged.
 * @param server Pointer to the server managing the game state
 * and connected clients.
 * @param id The unique identifier of the player associated
 * with the event.
 * @param type The type of resource involved in the event
 * (cast to int for message).
*/
void event_pgt(server_t *server, int id, r_ressource_t type);

/**
 * @brief Notify all graphical clients that a player has dropped a resource.
 * Sends a "pdr" message indicating that the player with the given ID
 * dropped a specific resource type on their current tile.
 * Protocol format:
 * @code
 * pdr #<player_id> <resource_type>\n
 * @endcode
 * @param server Pointer to the global server structure.
 * @param id Unique identifier of the player.
 * @param type Type of resource that was dropped
 * (as defined by r_ressource_t).
*/
void event_pdr(server_t *server, int id, r_ressource_t type);

/**
 * @brief Sends "plv" events for all connected players.
 * This function iterates through all connected clients on the server,
 * and for each client identified as a player, it calls `event_plv`
 * to broadcast their current level to all GUI clients.
 * @param server Pointer to the server managing the game state and clients.
*/
void event_all_plv(server_t *server);

/**
 * @brief Sends a "plv" event indicating a player's current level.
 * This function formats a message with the player's ID and level,
 * then broadcasts it to all connected GUI clients.
 * If message formatting fails, an error is logged.
 * @param server Pointer to the server managing the game state and clients.
 * @param player Pointer to the player whose level is being reported.
*/
void event_plv(server_t *server, player_t *player);

/**
 * @brief Sends a "pex" event to all connected GUI clients.
 * This function formats a message of type "pex" containing the
 * given player's ID,
 * then broadcasts it to all GUI clients connected to the server.
 * If message creation fails, an error is logged.
 * @param server Pointer to the server structure containing the list
 * of GUI clients.
 * @param player Pointer to the player structure whose ID is included
 * in the event.
*/
void event_pex(server_t *server, player_t *player);

/**
 * @brief Notify all graphical clients that a player has broadcast a message.
 * Sends a "pbc" message to all graphical clients indicating that
 * the player has performed a broadcast with the given message content.
 * Protocol format:
 * @code
 * pbc #<player_id> <message>\n
 * @endcode
 * @param server Pointer to the global server structure.
 * @param player Pointer to the player who sent the broadcast.
 * @param message Null-terminated string containing the broadcast message.
*/
void event_pbc(server_t *server, player_t *player, char *message);

/**
 * @brief Sends a "seg" event with a given name string.
 * This function formats and broadcasts a message containing the given name
 * to all connected GUI clients.
 * If message formatting fails, an error is logged.
 * @param server Pointer to the server managing clients.
 * @param name String to be included in the "seg" event.
*/
void event_seg(server_t *server, char *name);

/**
 * @brief Sends an "SMG" event with a specified name string.
 * This function formats a message containing the given name prefixed by
 * "SMG",
 * then broadcasts it to all connected GUI clients.
 * If message formatting fails, an error is logged.
 * @param server Pointer to the server managing clients.
 * @param name String to be included in the "SMG" event message.
*/
void event_smg(server_t *server, char *name);

/**
 * @brief Sends a "suc" event indicating an unknown GUI command received.
 * This function writes "suc" to the client socket at the specified index,
 * logs that an unknown GUI command was received, and logs the command string.
 * @param server Pointer to the server managing client connections.
 * @param index Index of the client in the server's pollfd array.
 * @param args Array of argument strings where args[0] is the unknown command.
*/
void event_suc(server_t *server, int index, char **args);

/**
 * @brief Sends an "sbp" event indicating invalid arguments or wrong
 * number of arguments for a command.
 * This function sends the "sbp" message to the client socket
 * at the specified index,
 * logs an informational message about invalid arguments,
 * and, if debug mode is enabled, prints detailed command and
 * argument information to stdout and debug file.
 * @param server Pointer to the server managing client connections.
 * @param index Index of the client in the server's pollfd array.
 * @param args Array of argument strings passed to the command.
 * @param i Index of the command in the gui_command_table.
*/
void event_sbp(server_t *server, int index, char **args, int i);
int table_size(char **table);
void cmd_look(server_t *server, int index, char **);

void cmd_broadcast_text(server_t *server, int index, char **args);
typedef char *(*line_builder_t)(server_t *, int, int, int);

char *build_line(server_t *srv, player_t *pl, int lvl);
char *append_token(char *dest, const char *token, server_t *srv);
unsigned int eggs_at(server_t *srv, int y, int x);
unsigned int players_at(server_t *srv, int y, int x);

/**
 * @brief Free a dynamically allocated 2D integer map.
 * @param y The number of rows in the map.
 * @param map Pointer to the 2D integer array to free.
*/
void free_int_map(int y, int **map);
void update_clock(zappy_clock_t *clock, server_t *server);
zappy_clock_t *init_clock(server_t *server, size_t freq);
void player_cmd_execution(server_t *server);
void cmd_incantation(server_t *server, int index, char **args);
bool start_incantation(server_t *server, player_t *pl);
void event_pic(server_t *server, player_t *player);
void event_pie(server_t *server, player_t *player, bool succes);
#endif /* !FUCNTION_H_ */
