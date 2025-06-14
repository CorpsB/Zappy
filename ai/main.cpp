/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** main
*/

#include "parser/parser.hpp"

int main(int ac, char **av)
{
    Config config;

    if (!parse_args(ac, av, config) && !config.help)
        return 84;
    printf("ok\n");
    return 0;
}
