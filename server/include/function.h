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
//server
server_t *add_server(void);
void see_server(server_t *server);
//teams
void add_teams(server_t *server, char *name);
void see_one_team(teams_t *team);
void see_teams(teams_t *teams);
//player
void add_player(server_t *server, int socket, teams_t *teams);

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
void log(server_t *server, char *message);

#endif /* !FUCNTION_H_ */
