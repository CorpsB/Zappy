##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## Makefile
##

SRC	=	src/main.c				\
		src/parser/parser.c				\
		src/parser/parse_teams.c			\
		src/utils/server/add_server.c		\
		src/utils/server/free_server.c		\
		src/utils/server/see_server.c		\
		src/utils/teams/add_teams.c		\
		src/utils/teams/free_teams.c		\
		src/utils/teams/search_teams.c		\
		src/utils/teams/see_teams.c		\
		src/utils/player/add_player.c		\
		src/utils/player/del_player.c		\
		src/utils/player/search_player.c	\
		src/utils/player/see_player.c		\
		src/utils/inventory/add_ressources.c	\
		src/utils/inventory/see_inventory.c


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