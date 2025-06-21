/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Interpreter
*/

#include "Interpreter.hpp"

void Interpreter::interpret(const std::string &data)
{
    std::string line;
    std::smatch matches;
    std::istringstream iss(data);

    const std::vector<std::pair<std::regex, std::function<void(const std::smatch &)>>> commands = {
        { msz, [&](const std::smatch &m) { _msz(std::stoi(m[1]), std::stoi(m[2])); } },
        { bct, [&](const std::smatch &m) { _bct(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), std::stoi(m[4]), std::stoi(m[5]), std::stoi(m[6]), std::stoi(m[7]), std::stoi(m[8]), std::stoi(m[9])); } },
        { tna, [&](const std::smatch &m) { _tna(m[1]); } },
        { pnw, [&](const std::smatch &m) { _pnw(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), static_cast<Renderer::Compass>(std::stoi(m[4])), std::stoi(m[5]), m[6]); } },
        { ppo, [&](const std::smatch &m) { _ppo(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), static_cast<Renderer::Compass>(std::stoi(m[4]))); } },
        { plv, [&](const std::smatch &m) { _plv(std::stoi(m[1]), std::stoi(m[2])); } },
        { pin, [&](const std::smatch &m) { _pin(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), std::stoi(m[4]), std::stoi(m[5]), std::stoi(m[6]), std::stoi(m[7]), std::stoi(m[8]), std::stoi(m[9]), std::stoi(m[10])); } },
        { pex, [&](const std::smatch &m) { _pex(std::stoi(m[1])); } },
        { pbc, [&](const std::smatch &m) { _pbc(std::stoi(m[1]), m[2]); } },
        { pie, [&](const std::smatch &m) { _pie(std::stoi(m[1]), std::stoi(m[2]), m[3]); } },
        { pfk, [&](const std::smatch &m) { _pfk(std::stoi(m[1])); } },
        { pdr, [&](const std::smatch &m) { _pdr(std::stoi(m[1]), std::stoi(m[2])); } },
        { pgt, [&](const std::smatch &m) { _pgt(std::stoi(m[1]), std::stoi(m[2])); } },
        { pdi, [&](const std::smatch &m) { _pdi(std::stoi(m[1])); } },
        { enw, [&](const std::smatch &m) { _enw(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), std::stoi(m[4])); } },
        { ebo, [&](const std::smatch &m) { _ebo(std::stoi(m[1])); } },
        { edi, [&](const std::smatch &m) { _edi(std::stoi(m[1])); } },
        { sgt, [&](const std::smatch &m) { _sgt(std::stoi(m[1])); } },
        { sst, [&](const std::smatch &m) { _sst(std::stoi(m[1])); } },
        { seg, [&](const std::smatch &m) { _seg(m[1]); } },
        { smg, [&](const std::smatch &m) { _smg(m[1]); } },
        { sbp, [&](const std::smatch &) { _sbp(); } },
        { pic, [&](const std::smatch &m) {
            std::string rest = line.substr(m.position(3) + m.length(3));
            std::vector<int> ids;

            for (std::sregex_iterator it(rest.begin(), rest.end(), playerRegex), end; it != end; ++it)
                ids.push_back(std::stoi((*it)[1]));
            _pic(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), ids);
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

void Interpreter::_msz(int x, int y)
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::GROUND, -1,
                {0.0f + (i * SIZE_GROUND), 0.0f, 0.0f + (j * SIZE_GROUND)}, sf::Color::Red, "./Assets/ground.stl");
}

void Interpreter::_bct(int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
    (void) x;
    (void) y;
    (void) q0;
    (void) q1;
    (void) q2;
    (void) q3;
    (void) q4;
    (void) q5;
    (void) q6;
    // std::cerr << "Content of " << x << y << ": " << q0 << " " << q1 << " " << q2 << " " << q3 << " " << q4 << " " << q5 << " " << q6 << std::endl;
}
// name of all the teams
void Interpreter::_tna(std::string teamName)
{
    std::cerr << "Teams name : " << teamName << std::endl;
}
// connection of a new player
void Interpreter::_pnw(int playerId, int x, int y, Renderer::Compass orientation, int level, std::string teamName)
{
    (void) level;
    (void) teamName;
    Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::BODY, playerId,
        {0.f + (x * SIZE_GROUND), -25.0f, 0.f + (y * SIZE_GROUND)}, sf::Color::Cyan, "./Assets/body_golem.stl", orientation);
    Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::EYES, playerId,
        {0.f + (x * SIZE_GROUND), -25.0f + -1.5f, 0.f + (y * SIZE_GROUND) + -6.5f}, sf::Color::Black, "./Assets/eyes_golem.stl", orientation);
}
// player’s position
void Interpreter::_ppo(int playerId, int x, int y, Renderer::Compass orientation)
{
    (void) playerId;
    (void) x;
    (void) y;
    (void) orientation;
    std::cerr << "PPO : " << x << " " << y << std::endl;
}
// player’s level
void Interpreter::_plv(int playerId, int level)
{
    (void) playerId;
    (void) level;
}
// player’s inventory
void Interpreter::_pin(int playerId, int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
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
void Interpreter::_pex(int playerId)
{
    (void) playerId;
}
// broadcast
void Interpreter::_pbc(int playerId, std::string data)
{
    (void) playerId;
    (void) data;
}
// start of an incantation (by the first player)
void Interpreter::_pic(int x, int y, int level, std::vector<int> playersId)
{
    (void) x;
    (void) y;
    (void) level;
    (void) playersId;
}
// end of an incantation
void Interpreter::_pie(int x, int y, std::string result)
{
    (void) x;
    (void) y;
    (void) result;
}
// egg laying by the player
void Interpreter::_pfk(int playerId)
{
    (void) playerId;
}
// resource dropping
void Interpreter::_pdr(int playerId, int resourceNumber)
{
    (void) playerId;
    (void) resourceNumber;
}
// resource collecting
void Interpreter::_pgt(int playerId, int resourceNumber)
{
    (void) playerId;
    (void) resourceNumber;
}
// death of a player
void Interpreter::_pdi(int playerId)
{
    (void) playerId;
}
// an egg was laid by a player
void Interpreter::_enw(int eggId, int playerId, int x, int y)
{
    (void) eggId;
    (void) playerId;
    (void) x;
    (void) y;
    std::cerr << "ENW : " << x << " " << y << std::endl;
}
// player connection for an egg
void Interpreter::_ebo(int eggId)
{
    (void) eggId;
}
// death of an egg
void Interpreter::_edi(int eggId)
{
    (void) eggId;
}
// time unit request
void Interpreter::_sgt(int timeUnit)
{
    (void) timeUnit;
}
// time unit modification
void Interpreter::_sst(int timeUnit)
{
    (void) timeUnit;
}
// end of game
void Interpreter::_seg(std::string teamName)
{
    (void) teamName;
}
// message from the server
void Interpreter::_smg(std::string msg)
{
    (void) msg;
}
// unknown command
void Interpreter::_suc(std::string data)
{
    std::cerr << "Unknown command : (" << data << ")" << std::endl;
}
