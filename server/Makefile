##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## Makefile
##

SRC	=	src/main.c								\
		src/poll.c								\
		src/parser/parser.c						\
		src/parser/parse_teams.c				\
		src/cmd_parser/cmd_parser.c				\
		src/cmd_parser/parser_table.c			\
		src/cmd_parser/str_to_array.c			\
		src/cmd/cmd_eject.c						\
		src/cmd/cmd_forward.c					\
		src/cmd/cmd_graphic.c					\
		src/cmd/cmd_inventory.c					\
		src/cmd/cmd_left.c						\
		src/cmd/cmd_player.c					\
		src/cmd/cmd_right.c						\
		src/cmd/cmd_set_object.c				\
		src/cmd/cmd_take_object.c				\
		src/cmd/test.c							\
		src/utils/server/add_server.c			\
		src/utils/server/free_server.c			\
		src/utils/server/see_server.c			\
		src/utils/teams/add_teams.c				\
		src/utils/teams/free_teams.c			\
		src/utils/teams/search_teams.c			\
		src/utils/teams/see_teams.c				\
		src/utils/player/add_player.c			\
		src/utils/player/del_player.c			\
		src/utils/player/search_player.c		\
		src/utils/player/see_player.c			\
		src/utils/inventory/add_ressources.c	\
		src/utils/inventory/see_inventory.c		\
		src/utils/eggs/add_eggs.c				\
		src/utils/eggs/search_eggs.c			\
		src/utils/eggs/see_eggs.c				\
		src/utils/loger/log.c



OBJ	=	$(SRC:.c=.o)

NAME	=	zappy_server

CFLAGS  = -Wall -Wextra -I. -g -Werror

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc $(SRC) -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
