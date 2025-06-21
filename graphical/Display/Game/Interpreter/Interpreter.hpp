/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Interpreter
*/

#pragma once

#include <iostream>

#include "../../../3DRenderer/include/Renderer.hpp"
#include "RegexMatches.hpp"

#define SIZE_GROUND 70

class Interpreter {
    public:
        Interpreter() {}
        ~Interpreter() {}

        /**
         * @brief Interprête la commande reçu par le client
         * @param data La commande reçu par le client
         */
        void interpret(const std::string &data);
    private:
        /**
         * @brief Défini la taille de la map
         * @param x Largeur de la map
         * @param y Longueur de la map
         */
        void _msz(int x, int y);
        /**
         * @brief Défini le contenu d'un emplacement
         * @param x Position X de l'emplacement
         * @param y Position Y de l'emplacement
         * @param q0, q1, q2, q3, q4, q5, q6 Resources
         */
        void _bct(int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6);
        void _tna(std::string teamName);
        void _pnw(int playerId, int x, int y, Renderer::Compass orientation, int level, std::string teamName);
        void _ppo(int playerId, int x, int y, Renderer::Compass orientation);
        void _plv(int playerId, int level);
        void _pin(int playerId, int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6);
        void _pex(int playerId);
        void _pbc(int playerId, std::string msg);
        void _pic(int x, int y, int level, std::vector<int> playersId);
        void _pie(int x, int y, std::string result);
        void _pfk(int playerId);
        void _pdr(int playerId, int resourceNumber);
        void _pgt(int playerId, int resourceNumber);
        void _pdi(int playerId);
        void _enw(int eggId, int playerId, int x, int y);
        void _ebo(int eggId);
        void _edi(int eggId);
        void _sgt(int timeUnit);
        void _sst(int timeUnit);
        void _seg(std::string teamName);
        void _smg(std::string msg);
        void _suc(std::string data);
        void _sbp() {}
};
