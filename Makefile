##
## EPITECH PROJECT, 2023
## MAKEFILE MAIN
## File description:
## A program that do simple operation.
##

.PHONY: all clean fclean re zappy_ai zappy_server zappy_gui

all: zappy_ai zappy_server zappy_gui

zappy_ai:
	make -C ai

zappy_server:
	make -C server

zappy_gui:
	make -C graphical

clean:
	make clean -C ai
	make clean -C graphical
	make clean -C server

fclean:	clean
	make fclean -C server
	make fclean -C graphical
	make fclean -C ai

re:	fclean all
