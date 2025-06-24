##
## EPITECH PROJECT, 2025
## Graphic
## File description:
## Makefile
##

SRC	= main.cpp	\
	Display/Window/Window.cpp	\
	Display/Event/Event.cpp	\
	Display/Game/Game.cpp	\
	Display/Game/Interpreter/Interpreter.cpp	\
	Client/Client.cpp	\
	Client/Config/NetConfig.cpp	\
	3DRenderer/src/Camera.cpp \
	3DRenderer/src/Clipper.cpp \
	3DRenderer/src/Entity.cpp \
	3DRenderer/src/Geometry.cpp \
	3DRenderer/src/HUD.cpp \
	3DRenderer/src/Math.cpp \
	3DRenderer/src/Renderer.cpp \
	3DRenderer/src/STLLoader.cpp \

OBJ	= $(SRC:.cpp=.o)

# CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -g -I3DRenderer/include -O3 -march=x86-64 -mtune=generic
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -g -I3DRenderer/include -O3 -march=native 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

NAME = zappy_gui

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
