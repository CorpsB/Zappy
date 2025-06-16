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

#endif /* !FUCNTION_H_ */
