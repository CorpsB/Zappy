/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main graphic
*/

#include "../include/Header.hpp"

int main()
{
    Window win;
    Event event;

    win.init();
    while (true) {
        if (event.getEvent(win.getWindow()) == -1) {
            win.stop();
            return 0;
        }
        win.clear();
        win.display();
    }
    return 0;
}
