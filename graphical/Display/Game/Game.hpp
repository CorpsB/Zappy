/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Game
*/

#pragma once

#include <iostream>

#include "../Window/Window.hpp"
#include "../Event/Event.hpp"
#include "../../3DRenderer/include/Renderer.hpp"

#include "Interpreter/Interpreter.hpp"

class Game {
    public:
        Game() {}
        ~Game() = default;

        static Game &GetInstance();

        /**
         * @brief Initialise la fenêtre d'affichage
         */
        void init();
        /**
         * @brief Lance la boucle principale d'update de l'affichage
         */
        void run();
        /**
         * Stop la fenêtre d'affichage
         */
        void stop();

        /**
         * @brief Analyse la donnée et modifie les éléments graphique en fonction de 'data'
         * @param data La ligne de commande reçu par le client
         */
        void processData(const std::string &data);
    private:
        Window _window;
        Event _event;
        sf::Clock _clock;

        Interpreter _interpreter;
};
