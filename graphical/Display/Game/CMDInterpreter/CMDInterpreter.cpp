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

    const std::vector<std::pair<std::regex, std::function<void(const std::smatch &)>>> commands = {
        { msz, [&](const std::smatch &m) { _msz(hud, std::stoi(m[1]), std::stoi(m[2])); } },
        { bct, [&](const std::smatch &m) { _bct(hud, std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), std::stoi(m[4]), std::stoi(m[5]), std::stoi(m[6]), std::stoi(m[7]), std::stoi(m[8]), std::stoi(m[9])); } },
        { tna, [&](const std::smatch &m) { _tna(hud, m[1]); } },
        { pnw, [&](const std::smatch &m) { _pnw(hud, std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), static_cast<Renderer::Compass>(std::stoi(m[4])), std::stoi(m[5]), m[6]); } },
        { ppo, [&](const std::smatch &m) { _ppo(hud, std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), static_cast<Renderer::Compass>(std::stoi(m[4]))); } },
        { plv, [&](const std::smatch &m) { _plv(hud, std::stoi(m[1]), std::stoi(m[2])); } },
        { pin, [&](const std::smatch &m) { _pin(hud, std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), std::stoi(m[4]), std::stoi(m[5]), std::stoi(m[6]), std::stoi(m[7]), std::stoi(m[8]), std::stoi(m[9]), std::stoi(m[10])); } },
        { pex, [&](const std::smatch &m) { _pex(hud, std::stoi(m[1])); } },
        { pbc, [&](const std::smatch &m) { _pbc(hud, std::stoi(m[1]), m[2]); } },
        { pie, [&](const std::smatch &m) { _pie(hud, std::stoi(m[1]), std::stoi(m[2]), m[3]); } },
        { pfk, [&](const std::smatch &m) { _pfk(hud, std::stoi(m[1])); } },
        { pdr, [&](const std::smatch &m) { _pdr(hud, std::stoi(m[1]), std::stoi(m[2])); } },
        { pgt, [&](const std::smatch &m) { _pgt(hud, std::stoi(m[1]), std::stoi(m[2])); } },
        { pdi, [&](const std::smatch &m) { _pdi(hud, std::stoi(m[1])); } },
        { enw, [&](const std::smatch &m) { _enw(hud, std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), std::stoi(m[4])); } },
        { ebo, [&](const std::smatch &m) { _ebo(hud, std::stoi(m[1])); } },
        { edi, [&](const std::smatch &m) { _edi(hud, std::stoi(m[1])); } },
        { sgt, [&](const std::smatch &m) { _sgt(hud, std::stoi(m[1])); } },
        { sst, [&](const std::smatch &m) { _sst(hud, std::stoi(m[1])); } },
        { seg, [&](const std::smatch &m) { _seg(hud, m[1]); } },
        { smg, [&](const std::smatch &m) { _smg(hud, m[1]); } },
        { sbp, [&](const std::smatch &) { _sbp(); } },
        { pic, [&](const std::smatch &m) {
            std::string rest = line.substr(m.position(3) + m.length(3));
            std::vector<int> ids;

            for (std::sregex_iterator it(rest.begin(), rest.end(), playerRegex), end; it != end; ++it)
                ids.push_back(std::stoi((*it)[1]));
            _pic(hud, std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), ids);
        } },
    };

    while (std::getline(iss, line)) {
        bool matched = false;

        for (const auto &[pattern, action] : commands) {
            if (std::regex_match(line, matches, pattern)) {
                action(matches);
                matched = true;
                break;
            }
        }
        if (!matched)
            _suc(line);
    }
}

// Commands
// map size
void CMDInterpreter::_msz(HUD &hud, int x, int y)
{
    (void) hud;
    std::cerr << "Map size : " << x << y << std::endl;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::GROUND, -1,
                {0.0f + (i * SIZE_GROUND), 0.0f, 0.0f + (j * SIZE_GROUND)}, sf::Color::Red, "./Assets/ground.stl");
        }
    }
}
// content of a tile
void CMDInterpreter::_bct(HUD &hud, int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
    (void) hud;
    std::cerr << "Content of " << x << y << ": " << q0 << " " << q1 << " " << q2 << " " << q3 << " " << q4 << " " << q5 << " " << q6 << std::endl;
}
// name of all the teams
void CMDInterpreter::_tna(HUD &hud, std::string teamName)
{
    (void) hud;
    std::cerr << "Teams name : " << teamName << std::endl;
}
// connection of a new player
void CMDInterpreter::_pnw(HUD &hud, int playerId, int x, int y, Renderer::Compass orientation, int level, std::string teamName)
{
    (void) hud;
    (void) playerId;
    (void) x;
    (void) y;
    (void) orientation;
    (void) level;
    (void) teamName;
    Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::BODY, playerId,
        {0.f + (x * SIZE_GROUND), -25.0f, 0.f + (y * SIZE_GROUND)}, sf::Color::Cyan, "./Assets/body_golem.stl", Renderer::Compass::NORTH);
    Renderer::rotatingEntityId = Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::EYES, playerId,
        {0.f + (x * SIZE_GROUND), -25.0f + -1.5f, 0.f + (y * SIZE_GROUND) + -6.5f}, sf::Color::Black, "./Assets/eyes_golem.stl");
}
// player’s position
void CMDInterpreter::_ppo(HUD &hud, int playerId, int x, int y, Renderer::Compass orientation)
{
    (void) hud;
    (void) playerId;
    (void) x;
    (void) y;
    (void) orientation;
}
// player’s level
void CMDInterpreter::_plv(HUD &hud, int playerId, int level)
{
    (void) hud;
    (void) playerId;
    (void) level;
}
// player’s inventory
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
// expulsion
void CMDInterpreter::_pex(HUD &hud, int playerId)
{
    (void) hud;
    (void) playerId;
}
// broadcast
void CMDInterpreter::_pbc(HUD &hud, int playerId, std::string msg)
{
    (void) hud;
    (void) playerId;
    (void) msg;
}
// start of an incantation (by the first player)
void CMDInterpreter::_pic(HUD &hud, int x, int y, int level, std::vector<int> playersId)
{
    (void) hud;
    (void) x;
    (void) y;
    (void) level;
    (void) playersId;
}
// end of an incantation
void CMDInterpreter::_pie(HUD &hud, int x, int y, std::string result)
{
    (void) hud;
    (void) x;
    (void) y;
    (void) result;
}
// egg laying by the player
void CMDInterpreter::_pfk(HUD &hud, int playerId)
{
    (void) hud;
    (void) playerId;
}
// resource dropping
void CMDInterpreter::_pdr(HUD &hud, int playerId, int resourceNumber)
{
    (void) hud;
    (void) playerId;
    (void) resourceNumber;
}
// resource collecting
void CMDInterpreter::_pgt(HUD &hud, int playerId, int resourceNumber)
{
    (void) hud;
    (void) playerId;
    (void) resourceNumber;
}
// death of a player
void CMDInterpreter::_pdi(HUD &hud, int playerId)
{
    (void) hud;
    (void) playerId;
}
// an egg was laid by a player
void CMDInterpreter::_enw(HUD &hud, int eggId, int playerId, int x, int y)
{
    (void) hud;
    (void) eggId;
    (void) playerId;
    (void) x;
    (void) y;
}
// player connection for an egg
void CMDInterpreter::_ebo(HUD &hud, int eggId)
{
    (void) hud;
    (void) eggId;
}
// death of an egg
void CMDInterpreter::_edi(HUD &hud, int eggId)
{
    (void) hud;
    (void) eggId;
}
// time unit request
void CMDInterpreter::_sgt(HUD &hud, int timeUnit)
{
    (void) hud;
    (void) timeUnit;
}
// time unit modification
void CMDInterpreter::_sst(HUD &hud, int timeUnit)
{
    (void) hud;
    (void) timeUnit;
}
// end of game
void CMDInterpreter::_seg(HUD &hud, std::string teamName)
{
    (void) hud;
    (void) teamName;
}
// message from the server
void CMDInterpreter::_smg(HUD &hud, std::string msg)
{
    (void) hud;
    (void) msg;
}
// unknown command
void CMDInterpreter::_suc(std::string data)
{
    std::cerr << "Unknown command : (" << data << ")" << std::endl;
}
