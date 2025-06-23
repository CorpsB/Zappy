##
## EPITECH PROJECT, 2023
## MAKEFILE MAIN
## File description:
## A program that do simple operation.
##

.PHONY: all clean fclean re zappy_ai

zappy_ai:
	make -C ai

all: zappy_ai

clean:
	make clean -C ai

fclean:	clean
	make fclean -C ai

re:	fclean all
