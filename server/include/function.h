/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** fucntion
*/

#ifndef FUCNTION_H_
    #define FUCNTION_H_

    #include "include/structure.h"

//utils
/**
 * @brief Function that check if the client is a PLAYER.
 *
 * @param server Global server pointer (for id & counters).
 * @param index The index of the player.
 * @return return 1 if the client is not a PLAYER (GRAPHICAL, LISTEN, UNKNOW)
 * return 0 if the client is a PLAYER.
*/
int check_autorized(server_t *server, int index);

/**
 * @brief Function that check if the client is a GUI.
 *
 * @param server Global server pointer (for id & counters).
 * @param index The index of the player.
 * @return return 1 if the client is not a GUI (PLAYER, LISTEN, UNKNOW)
 * return 0 if the client is a GUI.
*/

int check_graphical(server_t *server, int index);
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
resources_t create_resources(void);

//parser
int parse_port(char *str, server_t *server, int i);
int parse_width(char *str, server_t *server, int i);
int parse_height(char *str, server_t *server, int i);
int parse_client(char *str, server_t *server, int i);
int parse_frequency(char *str, server_t *server, int i);
int parse_teams(char **av, server_t *server, int i);

//logs
void logger(server_t *server, char *message, logs_t log, bool is_end);

void debug_print_resource_map(server_t *server);
void map_generator(server_t *server);
void map_update(server_t *server);
void change_arround(server_t *server, int *pos, r_ressource_t type,
    int weight);

void send_to_all_gui(server_t *server, char *message);
int eggs_size(eggs_t *eggs);
void generate_starter_eggs(server_t *server, teams_t *teams);
void event_pdi(server_t *server, player_t *player);


//EVENTS

/**
 * @brief Notify all GUI clients with the map size.
 *
 * @param server The main server structure containing map and clients.
 */
void event_msz(server_t *server);

/**
 * @brief Notify the GUI and the player that a player has died.
 *
 * GUI clients receive: pdi <id>
 * The player receives: dead
 *
 * @param server Pointer to the game server.
 * @param player Pointer to the player who has died.
 */
void event_pdi(server_t *server, player_t *player);

void event_bct(server_t *server);

void event_pdi_by_index(void);

void event_sgt(server_t *server);

void event_tna(server_t *server);

void event_pfk(server_t *server, player_t *player);

void event_enw(server_t *server, player_t *player, eggs_t *egg);

void event_new_gui_enw(server_t *server);

void event_ebo(server_t *server, unsigned int egg_id);

void send_enw(int fd, eggs_t *egg);

eggs_t *create_egg_from_player(player_t *player);

void del_egg(server_t *server, teams_t *teams, eggs_t *egg);
unsigned int *hatching_egg(server_t *server, teams_t *teams);
void complete_team_data(server_t *server);

void event_pnw(server_t *server, player_t *player);

void event_pin(server_t *server, player_t *player);

void event_ppo(server_t *server, player_t *player);

void event_edi(server_t *server, unsigned int egg_id);

#endif /* !FUCNTION_H_ */
