/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** CMDInterpreter
*/

#pragma once

#include "../HUD/HUD.hpp"
#include "CMDMatches.hpp"

class CMDInterpreter {
    public:
        CMDInterpreter() {}
        ~CMDInterpreter() {}

        void interpret(HUD &hud, const std::string &msg);
    private:
        void _msz(HUD &hud, int x, int y);
        void _bct(HUD &hud, int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6);
        void _tna(HUD &hud, std::string teamName);
        void _pnw(HUD &hud, int playerId, int x, int y, Renderer::Compass orientation, int level, std::string teamName);
        void _ppo(HUD &hud, int playerId, int x, int y, Renderer::Compass orientation);
        void _plv(HUD &hud, int playerId, int level);
        void _pin(HUD &hud, int playerId, int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6);
        void _pex(HUD &hud, int playerId);
        void _pbc(HUD &hud, int playerId, std::string msg);
        void _pic(HUD &hud, int x, int y, int level, std::vector<int> playersId);
        void _pie(HUD &hud, int x, int y, std::string result);
        void _pfk(HUD &hud, int playerId);
        void _pdr(HUD &hud, int playerId, int resourceNumber);
        void _pgt(HUD &hud, int playerId, int resourceNumber);
        void _pdi(HUD &hud, int playerId);
        void _enw(HUD &hud, int eggId, int playerId, int x, int y);
        void _ebo(HUD &hud, int eggId);
        void _edi(HUD &hud, int eggId);
        void _sgt(HUD &hud, int timeUnit);
        void _sst(HUD &hud, int timeUnit);
        void _seg(HUD &hud, std::string teamName);
        void _smg(HUD &hud, std::string msg);
        void _suc(std::string data);
        void _sbp() {}
};
