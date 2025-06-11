##
## EPITECH PROJECT, 2025
## Graphic
## File description:
## Makefile
##

SRC	= main.cpp	\
	Client/Client.cpp	\
	Client/Config/NetConfig.cpp	\

OBJ	= $(SRC:.cpp=.o)

CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -g -lsfml-graphics  \
    -lsfml-window -lsfml-system

NAME = graphic

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
