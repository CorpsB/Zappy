/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** CMDInterpreter
*/

#include "CMDInterpreter.hpp"

void CMDInterpreter::interpret(HUD &hud, const std::string &msg)
{
    std::smatch matches;

    if (std::regex_match(msg, matches, msz))
        _msz(hud, std::stoi(matches[1]), std::stoi(matches[2]));
    else if (std::regex_match(msg, matches, bct))
        _bct(hud, std::stoi(matches[1]), std::stoi(matches[2]), std::stoi(matches[3]), std::stoi(matches[4]), std::stoi(matches[5]), std::stoi(matches[6]), std::stoi(matches[7]), std::stoi(matches[8]), std::stoi(matches[9]));
    else if (std::regex_match(msg, matches, tna))
        _tna(hud, matches[1]);
    _suc(msg);
}

// Commands
void CMDInterpreter::_msz(HUD &hud, int x, int y)
{
    (void) hud;
    std::cerr << "Map size : " << x << y << std::endl;
}

void CMDInterpreter::_bct(HUD &hud, int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
    (void) hud;
    std::cerr << "Content of " << x << y << ": " << q0 << " " << q1 << " " << q2 << " " << q3 << " " << q4 << " " << q5 << " " << q6 << std::endl;
}

void CMDInterpreter::_tna(HUD &hud, std::string teamName)
{
    (void) hud;
    std::cerr << "Teams name : " << teamName << std::endl;
}

void CMDInterpreter::_suc(std::string data)
{
    std::cerr << "Unknown command : (" << data << ")" << std::endl;
}
