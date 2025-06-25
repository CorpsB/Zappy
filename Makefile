##
## EPITECH PROJECT, 2025
## Graphic
## File description:
## Makefile
##

SRC	= graphical/main.cpp	\
	graphical/Display/Window/Window.cpp	\
	graphical/Display/Event/Event.cpp	\
	graphical/Display/Game/Game.cpp	\
	graphical/Display/Game/Interpreter/Interpreter.cpp	\
	graphical/Client/Client.cpp	\
	graphical/Client/Config/NetConfig.cpp	\
	graphical/3DRenderer/src/Camera.cpp \
	graphical/3DRenderer/src/Clipper.cpp \
	graphical/3DRenderer/src/Entity.cpp \
	graphical/3DRenderer/src/Geometry.cpp \
	graphical/3DRenderer/src/HUD.cpp \
	graphical/3DRenderer/src/Math.cpp \
	graphical/3DRenderer/src/Renderer.cpp \
	graphical/3DRenderer/src/STLLoader.cpp \

OBJ	= $(SRC:.cpp=.o)

# CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -g -I3DRenderer/include -O3 -march=x86-64 -mtune=generic
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -g -Igraphical/3DRenderer/include -O3 -march=native
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
