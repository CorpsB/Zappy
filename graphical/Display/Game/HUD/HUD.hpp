/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** HUD
*/

#pragma once

#include "../../../3DRenderer/include/Renderer.hpp"

#include <iostream>

class HUD {
    public:
        HUD() {}
        ~HUD() {}

        void setMapSize(std::size_t x, std::size_t z);
    private:
        std::size_t _mapSizeX, _mapSizeZ;
};
