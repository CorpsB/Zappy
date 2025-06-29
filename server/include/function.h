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

/**
 * @brief Print information of all players in a linked list.
 * Prints each player’s details with an index number. If no players exist,
 * prints a corresponding message.
 * @param players Pointer to the head of the player linked list.
 * @param fd File descriptor where output will be printed.
*/
void see_all_players(player_t *players, int fd);
//server

/**
 * @brief Allocate and initialize a new server structure.
 * Initializes all fields to default zero or NULL states,
 * including map, teams, and counters.
 * @return server_t* Pointer to the allocated and initialized server.
 */
server_t *add_server(void);

/**
 * @brief Print server information to the specified file descriptor.
 * Prints key server parameters and calls additional printing functions
 * for poll and teams.
 * @param server Pointer to the server structure.
 * @param fd File descriptor to print output to.
*/
void see_server(server_t *server, int fd);

/**
 * @brief Free all allocated resources associated with the server.
 * Frees the map, teams, poll structures, and finally the server itself.
 * @param server Pointer to the server to free.
*/
void free_server(server_t *server);

/**
 * @brief Print detailed information about the poll structure.
 * Prints socket info, client counts, pointers and detailed
 * pollfd and client lists.
 * @param poll poll_t struct (by value).
 * @param fd File descriptor for output.
 * @param size Number of connected clients.
*/
void see_poll(poll_t poll, int fd, int size);

/**
 * @brief Print debug info for the server.
 * If debug mode is enabled and a debug file descriptor is set,
 * prints to that fd, then also prints to stderr (fd=2).
 * @param server Pointer to the server structure.
*/
void debug_server(server_t *server);

/**
 * @brief Free all resources related to poll structure in the server.
 * Closes all client sockets and frees allocated arrays for client
 * list and pollfds.
 * @param server Pointer to the server structure.
*/
void free_poll(server_t *server);
//teams

/**
 * @brief Add a new team to the server's linked list of teams.
 * Allocates and initializes a new teams_t node, sets its name,
 * IDs, and links it at the head of the list.
 * @param server Pointer to the server struct.
 * @param name Name of the team to add.
*/
void add_teams(server_t *server, char *name);

/**
 * @brief Print detailed information about a single team.
 * Shows team name, ID, slots used, win/eliminated status,
 * then prints the team's eggs and players.
 * @param team Pointer to the team node.
 * @param fd File descriptor to print to.
*/
void see_one_team(teams_t *team, int fd);

/**
 * @brief Print a list of all teams and their details.
 * Iterates through the linked list of teams and prints each one.
 * @param teams Pointer to the head of the team linked list.
 * @param fd File descriptor to print to.
*/
void see_teams(teams_t *teams, int fd);

/**
 * @brief Free an entire linked list of teams.
 * Iteratively frees all nodes and their contents.
 * @param teams Pointer to the head of the team linked list.
*/
void free_all_teams(teams_t *teams);
//player
/**
 * @brief Searches for a player by ID across all teams.
 * @param server The server structure containing teams.
 * @param id The target player ID.
 * @return player_t* if found, NULL otherwise.
*/
player_t *find_player_by_id(const server_t *server, unsigned int id);

/**
 * @brief Add a new player to the server and team.
 * Calls hatching_egg to get spawn position, initializes the player node,
 * sets pointers in client list and team, triggers the player spawn event,
 * and frees the temporary position array.
 * @param server Pointer to the server structure.
 * @param index Index in the poll file descriptor array for the player.
 * @param teams Pointer to the team structure the player belongs to.
*/
void add_player(server_t *server, int socket, teams_t *teams);

/**
 * @brief Free the memory of all players in a linked list.
 * Iterates through the player linked list and frees each node.
 * @param player Pointer to the head of the player linked list.
*/
void free_all_player(player_t *player);
//cmd parser

/**
 * @brief Split a string into an array of strings based on a separator.
 * The returned array is NULL-terminated and must be freed with free_table().
 * @param str The string to split.
 * @param separator The string containing separator characters.
 * @return The array of tokens, or NULL on failure.
*/
char **str_to_array(char *str, char *separator);

/**
 * @brief Main server loop.
 * Initializes the server, accepts new clients, processes events, manages
 * player commands, handles food consumption, and checks game state.
 * @param server Pointer to the server structure.
*/
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

/**
 * @brief Triggers a player death event for a player at the given index.
 * @param server Pointer to the server structure.
 * @param index Index of the player in the client list.
*/
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
void send_enw(server_t *server, int fd, eggs_t *egg);

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

/**
 * @brief Update the slots_max value for all teams.
 * Sets the maximum slots per team to the current starter eggs number
 * stored in the server struct.
 * @param server Pointer to the server struct.
*/
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

/**
 * @brief Free a NULL-terminated array of strings.
 * @param table The array to free.
*/
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

/**
 * @brief Get the size of a NULL-terminated array of strings.
 * @param table The array to measure.
 * @return The number of elements in the array.
*/
int table_size(char **table);

/**
 * @brief Command handler for the "Look" player command.
 * Sends a description of the surroundings to the player.
 * @param srv The server structure.
 * @param idx The index of the player in the poll list.
 * @param args Command arguments (unused).
*/
void cmd_look(server_t *server, int index, char **);

/**
 * @brief Handles the "Broadcast" command from a player.
 * Sends the message to all other alive players on the map
 * with directional information.
 * @param srv Pointer to the server structure.
 * @param idx Index of the sending player in the client list.
 * @param args Array of command arguments (the message is built
 * from args[1] onward).
*/
void cmd_broadcast_text(server_t *server, int index, char **args);

typedef char *(*line_builder_t)(server_t *, int, int, int);

char *build_line(server_t *srv, player_t *pl, int lvl);

/**
 * @brief Append a token to a string, reallocating memory if necessary.
 * @param dest The original string (can be NULL).
 * @param token The token to append.
 * @param srv The server structure (used for logging on error).
 * @return A new string with the token appended, or NULL on error.
*/
char *append_token(char *dest, const char *token, server_t *srv);

/**
 * @brief Count the number of eggs on a specific tile.
 * @param srv The server structure.
 * @param y The Y coordinate of the tile.
 * @param x The X coordinate of the tile.
 * @return The total number of eggs on the tile.
*/
unsigned int eggs_at(server_t *srv, int y, int x);

/**
 * @brief Count the number of players on a specific tile.
 * @param srv The server structure.
 * @param y The Y coordinate of the tile.
 * @param x The X coordinate of the tile.
 * @return The total number of players on the tile.
*/
unsigned int players_at(server_t *srv, int y, int x);

/**
 * @brief Free a dynamically allocated 2D integer map.
 * @param y The number of rows in the map.
 * @param map Pointer to the 2D integer array to free.
*/
void free_int_map(int y, int **map);

/**
 * @brief Initialize and start a new clock.
 * Allocates a new clock structure, sets its frequency, and starts
 * tracking time.
 * @param server Pointer to the server structure for logging in case
 * of failure.
 * @param freq Frequency of the clock in server units.
 * @return zappy_clock_t* Pointer to the initialized clock structure.
*/
zappy_clock_t *init_clock(server_t *server, size_t freq);

/**
 * @brief Update the clock accumulator and last_tick.
 * Adds elapsed time units to accumulator and updates last_tick.
 * @param clock Pointer to zappy_clock_t struct.
*/
void update_clock(zappy_clock_t *clock, server_t *server);

/**
 * @brief Execute pending player commands based on their timers.
 * This function iterates over all connected clients, checks if
 * they are players,
 * and executes commands if timers allow it.
 * @param server Pointer to the server structure.
*/
void player_cmd_execution(server_t *server);

/**
 * @brief Command handler for the "Incantation" player command.
 * @param server The server structure.
 * @param index The index of the player in the poll list.
 * @param args Command arguments (unused).
*/
void cmd_incantation(server_t *server, int index, char **args);

/**
 * @brief Start an incantation attempt for a player.
 * Freezes all involved players and notifies them if conditions are met.
 * @param server The server structure.
 * @param pl The player initiating the incantation.
 * @return true if the incantation has started, false otherwise.
*/
bool start_incantation(server_t *server, player_t *pl);

/**
 * @brief Triggers the "pic" (player incantation start) event for all
 * GUI clients.
 * Constructs the "pic" message with the incantation initiator's
 * position, level, and ID.
 * Adds the IDs of all other participating players on the same tile
 * who meet the conditions.
 * Sends the final message to all graphical clients.
 * @param server Pointer to the server structure.
 * @param player Pointer to the player initiating the incantation.
*/
void event_pic(server_t *server, player_t *player);

/**
 * @brief Triggers the "pie" (player incantation end) event
 * for all GUI clients.
 * Sends a message to all graphical clients indicating the result
 * of the incantation
 * on the specified tile, including the position and success state.
 * @param server Pointer to the server structure.
 * @param player Pointer to the player whose tile the event occurred on.
 * @param succes Boolean indicating if the incantation succeeded (true)
 * or failed (false).
*/
void event_pie(server_t *server, player_t *player, bool succes);

/**
 * @brief Initialize the main server socket and bind it.
 * This function creates the listening socket, configures its parameters,
 * binds it to the specified port, and starts listening for connections.
 * @param server Pointer to the server structure.
*/
void init_server(server_t *server);

/**
 * @brief Add a command to the player's command queue.
 * If the command queue is full, the player receives a "suc" response.
 * Non-player clients have their command handled immediately.
 * @param server Pointer to the server structure.
 * @param cmd Command string.
 * @param index Index of the client in the poll list.
*/
void add_cmd(server_t *server, char *cmd, int index);

/**
 * @brief Sends a broadcast message to a player located on the same
 * tile as the sender.
 * The message follows the protocol format: "message 0, <msg>".
 * @param srv Pointer to the server structure.
 * @param rcv Pointer to the receiving player.
 * @param msg The message to send.
*/
void send_same_tile_message(server_t *srv, player_t *rcv,
    const char *msg);

/**
 * @brief Sends a directional broadcast message to a player.
 * Calculates the direction from the sender to the receiver
 * based on map topology and player orientation,
 * then sends a formatted message following the protocol:
 * "message <direction>, <msg>".
 * @param srv Pointer to the server structure.
 * @param snd Pointer to the sending player.
 * @param rcv Pointer to the receiving player.
 * @param msg The message to send.
*/
void send_directional_message(server_t *srv, player_t *snd,
    player_t *rcv, const char *msg);

/**
 * @brief Adjusts the raw direction based on the receiver's orientation.
 * @param raw The raw direction index.
 * @param pl Pointer to the receiving player.
 * @return The adjusted direction index (1 to 8).
*/
int adjust_to_player_dir(int raw, player_t *pl);

/**
 * @brief Computes the raw direction index from the sender to the receiver.
 * @param map The 2D broadcast map.
 * @param srv Pointer to the server structure.
 * @param rcv Pointer to the receiving player.
 * @return The raw direction index (1 to 8).
*/
int get_raw_direction(int **map, server_t *srv, player_t *rcv);

/**
 * @brief Initializes sound propagation from the sender's position.
 * @param map The 2D broadcast map.
 * @param srv Pointer to the server structure.
 * @param sender Pointer to the player sending the broadcast.
 * @param receiver Pointer to the player receiving the broadcast.
*/
void propagate_sound_map(int **map, server_t *srv,
    player_t *sender, player_t *receiver);

/**
 * @brief Frees the memory of a broadcast map.
 * @param srv Pointer to the server structure.
 * @param map The 2D int array to free.
*/
void free_broadcast_map(server_t *srv, int **map);

/**
 * @brief Creates a 2D int map initialized for broadcast propagation.
 *
 * The map dimensions correspond to the server's map size, and
 * all values are initialized to -1.
 * If allocation fails at any point, previously allocated memory
 * is freed and NULL is returned.
 *
 * @param srv Pointer to the server structure.
 * @return A pointer to the allocated 2D map, or NULL on failure.
*/
int **create_broadcast_map(server_t *srv);
void send_str(server_t *server, int fd, char *message, bool need_free);

#endif /* !FUCNTION_H_ */
