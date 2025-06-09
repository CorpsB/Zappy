##
## EPITECH PROJECT, 2023
## MAKEFILE MAIN
## File description:
## A program that do simple operation.
##

.PHONY: all clean fclean re zappy_ai

zappy_ai:
	make -C AI

all: zappy_ai

clean:
	make clean -C AI

fclean:	clean
	make fclean -C AI

re:	fclean all
