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
		src/cmd/cmd_IA/cmd_eject.c				\
		src/cmd/cmd_IA/cmd_fork.c				\
		src/cmd/cmd_IA/cmd_forward.c			\
		src/cmd/cmd_GUI/cmd_graphic.c			\
		src/cmd/cmd_IA/cmd_inventory.c			\
		src/cmd/cmd_IA/cmd_left.c				\
		src/cmd/cmd_IA/cmd_player.c				\
		src/cmd/cmd_IA/cmd_right.c				\
		src/cmd/cmd_IA/cmd_set_object.c			\
		src/cmd/cmd_IA/cmd_take_object.c		\
		src/cmd/cmd_IA/cmd_test.c				\
		src/cmd/cmd_IA/cmd_connect_nbr.c		\
		src/utils/server/add_server.c			\
		src/utils/server/free_server.c			\
		src/utils/server/see_server.c			\
		src/utils/teams/add_teams.c				\
		src/utils/teams/free_teams.c			\
		src/utils/eggs/free_eggs.c				\
		src/utils/eggs/eggs_size.c				\
		src/utils/player/free_player.c			\
		src/utils/teams/see_teams.c				\
		src/utils/player/add_player.c			\
		src/utils/player/search_player.c		\
		src/utils/player/see_player.c			\
		src/utils/inventory/add_ressources.c	\
		src/utils/inventory/see_inventory.c		\
		src/utils/eggs/add_eggs.c				\
		src/utils/eggs/search_eggs.c			\
		src/utils/eggs/see_eggs.c				\
		src/utils/loger/log.c					\
		src/utils/poll/see_poll.c				\
		src/utils/poll/free_poll.c				\
		src/cmd/cmd_GUI/cmd_msz.c				\
		src/cmd/cmd_GUI/cmd_bct.c				\
		src/cmd/cmd_GUI/cmd_mct.c				\
		src/cmd/cmd_GUI/cmd_tna.c				\
		src/cmd/cmd_GUI/cmd_ppo.c				\
		src/cmd/cmd_GUI/cmd_plv.c				\
		src/cmd/cmd_GUI/cmd_pin.c				\
		src/cmd/cmd_GUI/cmd_sst_t.c				\
		src/cmd/cmd_GUI/cmd_sgt_t.c				\
		src/utils/map/density_table.c			\
		src/utils/map/map_generator.c			\
		src/utils/map/map_update.c				\
		src/utils/map/see_map.c					\
		src/event/event_msz.c					\
		src/event/event_pdi.c					\
		src/event/event_bct.c					\
		src/event/event_sgt.c					\
		src/event/event_tna.c					\
		src/event/event_enw.c					\
		src/event/event_pfk.c					\
		src/event/event_ebo.c					\
		src/event/event_pnw.c					\
		src/event/event_pin.c					\
		src/event/event_ppo.c					\
		src/event/event_edi.c					\
		src/event/event_pdr.c					\
		src/event/event_pgt.c					\
		src/utils/eggs/del_egg.c				\
		src/utils/eggs/hatching_eggs.c			\
		src/utils/teams/complete_team_data.c	\
		src/utils/send_and_recieve/send_to_all_gui.c		\
		src/event/event_plv.c					\
		src/event/event_pex.c					\
		src/event/event_pbc.c					\
		src/event/event_seg.c					\
		src/event/event_smg.c					\
		src/event/event_sbp.c					\
		src/event/event_suc.c					\
		src/cmd/cmd_IA/cmd_look.c				\
		src/cmd/cmd_IA/cmd_look_next.c			\
		src/cmd/cmd_IA/cmd_broadcast_text.c		\
		src/cmd/cmd_IA/cmd_broadcast_text2.c	\
		src/cmd/cmd_IA/cmd_broadcast_text3.c	\
		src/clock.c								\
		src/utils/map/del_map.c					\
		src/player_cmd_execution.c				\
		src/cmd/cmd_IA/cmd_incantation.c		\
		src/cmd/cmd_IA/incantation_table.c		\
		src/event/event_pic.c					\
		src/event/event_pie.c					\
		src/utils/send_and_recieve/add_cmd.c	\
		src/utils/send_and_recieve/send_str.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	zappy_server

CFLAGS  = -Wall -Wextra -I. -g -Werror

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc $(SRC) -o $(NAME) $(CFLAGS)
	mv $(NAME) ..

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re:	fclean all

.PHONY: all clean fclean re
