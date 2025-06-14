##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-tekspice-noe.carabin
## File description:
## Makefile
##

FLAGS	= -std=c++20 -Wall -Wextra -Werror -g

SRC	=	main.cpp	\
		entity/AI.cpp	\
		entity/bot/helper/count_player.cpp	\
		entity/bot/goal.cpp	\
		entity/inventory/Inventory.cpp	\
		entity/persona/Persona.cpp	\
		entity/sound/SoundSystem.cpp	\
		network/Socket.cpp	\
		parser/parser.cpp	\
		parser/help.cpp	\
		utils/debug/Logger.cpp	\
		utils/exception/Error.cpp	\
		utils/random/number.cpp	\
		utils/string/split.cpp	\
		utils/validation/integer.cpp	\
		utils/validation/ipv4.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	zappy_ai

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(FLAGS)
	mv $(NAME) ..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
