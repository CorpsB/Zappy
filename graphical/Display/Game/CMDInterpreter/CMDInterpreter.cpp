/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** CMDInterpreter
*/

#include "CMDInterpreter.hpp"

void CMDInterpreter::interpret(HUD &hud, const std::string &msg)
{
    std::string line;
    std::smatch matches;
    std::istringstream iss(msg);

    while (std::getline(iss, line)) {
        if (std::regex_match(line, matches, msz))
            _msz(hud, std::stoi(matches[1]), std::stoi(matches[2]));
        else if (std::regex_match(line, matches, bct))
            _bct(hud, std::stoi(matches[1]), std::stoi(matches[2]), std::stoi(matches[3]), std::stoi(matches[4]), std::stoi(matches[5]), std::stoi(matches[6]), std::stoi(matches[7]), std::stoi(matches[8]), std::stoi(matches[9]));
        else if (std::regex_match(line, matches, tna))
            _tna(hud, matches[1]);
        else if (std::regex_match(line, matches, pnw))
            _pnw(hud, std::stoi(matches[1]), std::stoi(matches[2]), std::stoi(matches[3]), static_cast<Renderer::Compass>(std::stoi(matches[4])), std::stoi(matches[5]), matches[6]);
        else if (std::regex_match(line, matches, ppo))
            _ppo(hud, std::stoi(matches[1]), std::stoi(matches[2]), std::stoi(matches[3]), static_cast<Renderer::Compass>(std::stoi(matches[4])));
        else if (std::regex_match(line, matches, plv))
            _plv(hud, std::stoi(matches[1]), std::stoi(matches[2]));
        else if (std::regex_match(line, matches, pin))
            _pin(hud, std::stoi(matches[1]), std::stoi(matches[2]), std::stoi(matches[3]), std::stoi(matches[4]), std::stoi(matches[5]), std::stoi(matches[6]), std::stoi(matches[7]), std::stoi(matches[8]), std::stoi(matches[9]), std::stoi(matches[10]));
        else if (std::regex_match(line, matches, pex))
            _pex(hud, std::stoi(matches[1]));
        else if (std::regex_match(line, matches, pbc))
            _pbc(hud, std::stoi(matches[1]), matches[2]);
        else if (std::regex_match(line, matches, pic)) {
            std::string rest = line.substr(matches.position(3) + matches.length(3));
            auto playerBegin = std::sregex_iterator(rest.begin(), rest.end(), playerRegex);
            auto playerEnd = std::sregex_iterator();
            std::vector<int> playerIds;

            for (std::sregex_iterator i = playerBegin; i != playerEnd; i++) {
                playerIds.push_back(std::stoi((*i)[1]));
            }
            _pic(hud, std::stoi(matches[1]), std::stoi(matches[2]), std::stoi(matches[3]), playerIds);
        } else if (std::regex_match(line, matches, pie))
            _pie(hud, std::stoi(matches[1]), std::stoi(matches[2]), matches[3]);
        else if (std::regex_match(line, matches, pfk))
            _pfk(hud, std::stoi(matches[1]));
        else if (std::regex_match(line, matches, pdr))
            _pdr(hud, std::stoi(matches[1]), std::stoi(matches[2]));
        else if (std::regex_match(line, matches, pgt))
            _pgt(hud, std::stoi(matches[1]), std::stoi(matches[2]));
        else if (std::regex_match(line, matches, pdi))
            _pdi(hud, std::stoi(matches[1]));
        else if (std::regex_match(line, matches, enw))
            _enw(hud, std::stoi(matches[1]), std::stoi(matches[2]), std::stoi(matches[3]), std::stoi(matches[4]));
        else if (std::regex_match(line, matches, ebo))
            _ebo(hud, std::stoi(matches[1]));
        else if (std::regex_match(line, matches, edi))
            _edi(hud, std::stoi(matches[1]));
        else if (std::regex_match(line, matches, sgt))
            _sgt(hud, std::stoi(matches[1]));
        else if (std::regex_match(line, matches, sst))
            _sst(hud, std::stoi(matches[1]));
        else if (std::regex_match(line, matches, seg))
            _seg(hud, matches[1]);
        else if (std::regex_match(line, matches, smg))
            _smg(hud, matches[1]);
        else if (std::regex_match(line, matches, sbp))
            _sbp();
        else
            _suc(line);
    }
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

void CMDInterpreter::_pnw(HUD &hud, int playerId, int x, int y, Renderer::Compass orientation, int level, std::string teamName)
{
    (void) hud;
    (void) playerId;
    (void) x;
    (void) y;
    (void) orientation;
    (void) level;
    (void) teamName;
}

void CMDInterpreter::_ppo(HUD &hud, int playerId, int x, int y, Renderer::Compass orientation)
{
    (void) hud;
    (void) playerId;
    (void) x;
    (void) y;
    (void) orientation;
}

void CMDInterpreter::_plv(HUD &hud, int playerId, int level)
{
    (void) hud;
    (void) playerId;
    (void) level;
}

void CMDInterpreter::_pin(HUD &hud, int playerId, int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
    (void) hud;
    (void) playerId;
    (void) x;
    (void) y;
    (void) q0;
    (void) q1;
    (void) q2;
    (void) q3;
    (void) q4;
    (void) q5;
    (void) q6;
}

void CMDInterpreter::_pex(HUD &hud, int playerId)
{
    (void) hud;
    (void) playerId;
}

void CMDInterpreter::_pbc(HUD &hud, int playerId, std::string msg)
{
    (void) hud;
    (void) playerId;
    (void) msg;
}

void CMDInterpreter::_pic(HUD &hud, int x, int y, int level, std::vector<int> playersId)
{
    (void) hud;
    (void) x;
    (void) y;
    (void) level;
    (void) playersId;
}

void CMDInterpreter::_pie(HUD &hud, int x, int y, std::string result)
{
    (void) hud;
    (void) x;
    (void) y;
    (void) result;
}

void CMDInterpreter::_pfk(HUD &hud, int playerId)
{
    (void) hud;
    (void) playerId;
}

void CMDInterpreter::_pdr(HUD &hud, int playerId, int resourceNumber)
{
    (void) hud;
    (void) playerId;
    (void) resourceNumber;
}

void CMDInterpreter::_pgt(HUD &hud, int playerId, int resourceNumber)
{
    (void) hud;
    (void) playerId;
    (void) resourceNumber;
}

void CMDInterpreter::_pdi(HUD &hud, int playerId)
{
    (void) hud;
    (void) playerId;
}

void CMDInterpreter::_enw(HUD &hud, int eggId, int playerId, int x, int y)
{
    (void) hud;
    (void) eggId;
    (void) playerId;
    (void) x;
    (void) y;
}

void CMDInterpreter::_ebo(HUD &hud, int eggId)
{
    (void) hud;
    (void) eggId;
}

void CMDInterpreter::_edi(HUD &hud, int eggId)
{
    (void) hud;
    (void) eggId;
}

void CMDInterpreter::_sgt(HUD &hud, int timeUnit)
{
    (void) hud;
    (void) timeUnit;
}

void CMDInterpreter::_sst(HUD &hud, int timeUnit)
{
    (void) hud;
    (void) timeUnit;
}

void CMDInterpreter::_seg(HUD &hud, std::string teamName)
{
    (void) hud;
    (void) teamName;
}

void CMDInterpreter::_smg(HUD &hud, std::string msg)
{
    (void) hud;
    (void) msg;
}

void CMDInterpreter::_suc(std::string data)
{
    std::cerr << "Unknown command : (" << data << ")" << std::endl;
}
