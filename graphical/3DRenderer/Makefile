##
## EPITECH PROJECT, 2025
## B-YEP-400-STG-4-1-zappy-noe.carabin
## File description:
## Makefile
##

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -O3 -march=native
MAKEFLAGS += -j$(shell nproc)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = zappy_gui

SRC = src/Camera.cpp \
	src/Clipper.cpp \
	src/Entity.cpp \
	src/Geometry.cpp \
	src/HUD.cpp \
	src/Math.cpp \
	src/Renderer.cpp \
	src/STLLoader.cpp \
	src/main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_PATH) $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(SFML_INC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all
