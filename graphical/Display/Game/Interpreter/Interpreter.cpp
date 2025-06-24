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
        { pnw, [&](const std::smatch &m) { _pnw(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), static_cast<Renderer::Compass>(std::stoi(m[4]) - 1), std::stoi(m[5]), m[6]); } },
        { ppo, [&](const std::smatch &m) { _ppo(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3]), static_cast<Renderer::Compass>(std::stoi(m[4]) - 1)); } },
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
        for (int j = 0; j < y; j++) {
            if (j == 0 && i == 0) {
                Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::GROUND, -1,
                {0.0f + (i * TILE_SIZE), 0.0f, 0.0f + (j * TILE_SIZE)}, sf::Color::Red, "./Assets/ground.stl");
            } else
                Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::GROUND, -1,
                {0.0f + (i * TILE_SIZE), 0.0f, 0.0f + (j * TILE_SIZE)}, sf::Color {65, 65, 65}, "./Assets/ground.stl");
        }
    Renderer::map_size_x = x;
    Renderer::map_size_y = y;
}

void Interpreter::_bct(int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
    bool q0Exists = false;
    bool q1Exists = false;
    bool q2Exists = false;
    bool q3Exists = false;
    bool q4Exists = false;
    bool q5Exists = false;
    bool q6Exists = false;

    // If there is no more of a particular ressources, we have to verify if there was before, and if yes, we have to remove it.
    for (auto it = Renderer::sceneEntities.begin(); it != Renderer::sceneEntities.end(); ) {
        Renderer::Entity &e = *it;
        if (e.type == Renderer::PartType::Q0 && e.position.x == 25.0f + (x * TILE_SIZE) && e.position.z == 25.0f + (y * TILE_SIZE)) {
            if (q0 == 0) {
                it = Renderer::sceneEntities.erase(it);
            } else
                q0Exists = true;
        } else if (e.type == Renderer::PartType::Q1 && e.position.x == 15.0f + (x * TILE_SIZE) && e.position.z == -25.0f + (y * TILE_SIZE)) {
            if (q1 == 0) {
                it = Renderer::sceneEntities.erase(it);
            } else
                q1Exists = true;
        } else if (e.type == Renderer::PartType::Q2 && e.position.x == 25.0f + (x * TILE_SIZE) && e.position.z == -15.0f + (y * TILE_SIZE)) {
            if (q2 == 0) {
                it = Renderer::sceneEntities.erase(it);
            } else
                q2Exists = true;
        } else if (e.type == Renderer::PartType::Q3 && e.position.x == -15.0f + (x * TILE_SIZE) && e.position.z == -25.0f + (y * TILE_SIZE)) {
            if (q3 == 0) {
                it = Renderer::sceneEntities.erase(it);
            } else
                q3Exists = true;
        } else if (e.type == Renderer::PartType::Q4 && e.position.x == -25.0f + (x * TILE_SIZE) && e.position.z == -15.0f + (y * TILE_SIZE)) {
            if (q4 == 0) {
                it = Renderer::sceneEntities.erase(it);
            } else
                q4Exists = true;
        } else if (e.type == Renderer::PartType::Q5 && e.position.x == -15.0f + (x * TILE_SIZE) && e.position.z == 25.0f + (y * TILE_SIZE)) {
            if (q5 == 0) {
                it = Renderer::sceneEntities.erase(it);
            } else
                q5Exists = true;
        } else if (e.type == Renderer::PartType::Q6 && e.position.x == -25.0f + (x * TILE_SIZE) && e.position.z == 15.0f + (y * TILE_SIZE)) {
            if (q6 == 0) {
                it = Renderer::sceneEntities.erase(it);
            } else
                q6Exists = true;
        } else {
            ++it;
        }
    }
    // food
    if (q0 != 0 && !q0Exists)
        Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::Q0, -1,
        {25.0f + (x * TILE_SIZE), -6.5f, 25.0f + (y * TILE_SIZE)}, sf::Color::Yellow, "./Assets/Food.stl");
    // Linemate
    if (q1 != 0 && !q1Exists)
        Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::Q1, -1,
        {15.0f + (x * TILE_SIZE), -6.5f, -25.0f + (y * TILE_SIZE)}, sf::Color {96, 96, 96}, "./Assets/Crystals.stl",
        Renderer::Compass::NORTH, {0.f, Renderer::getRandomAngle(), 0.f});
    // Deraumere
    if (q2 != 0 && !q2Exists)
        Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::Q2, -1,
        {25.0f + (x * TILE_SIZE), -6.5f, -15.0f + (y * TILE_SIZE)}, sf::Color::Green, "./Assets/Crystals.stl",
        Renderer::Compass::NORTH, {0.f, Renderer::getRandomAngle(), 0.f});
    // Sibur
    if (q3 != 0 && !q3Exists)
        Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::Q3, -1,
        {-15.0f + (x * TILE_SIZE), -6.5f, -25.0f + (y * TILE_SIZE)}, sf::Color {204, 0, 102}, "./Assets/Crystals.stl",
        Renderer::Compass::NORTH, {0.f, Renderer::getRandomAngle(), 0.f});
    // Mendiane
    if (q4 != 0 && !q4Exists)
        Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::Q4, -1,
        {-25.0f + (x * TILE_SIZE), -6.5f, -15.0f + (y * TILE_SIZE)}, sf::Color {255, 255, 255}, "./Assets/Crystals.stl",
        Renderer::Compass::NORTH, {0.f, Renderer::getRandomAngle(), 0.f});
    // Phiras
    if (q5 != 0 && !q5Exists)
        Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::Q5, -1,
        {-15.0f + (x * TILE_SIZE), -6.5f, 25.0f + (y * TILE_SIZE)}, sf::Color {127, 0, 255}, "./Assets/Crystals.stl",
        Renderer::Compass::NORTH, {0.f, Renderer::getRandomAngle(), 0.f});
    // Thystame
    if (q6 != 0 && !q6Exists)
        Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::Q6, -1,
        {-25.0f + (x * TILE_SIZE), -5.0f, 15.0f + (y * TILE_SIZE)}, sf::Color::Red, "./Assets/Crystals.stl",
        Renderer::Compass::NORTH, {0.f, Renderer::getRandomAngle(), 0.f});
    std::cerr << "Content of " << x << y << ": " << q0 << " " << q1 << " " << q2 << " " << q3 << " " << q4 << " " << q5 << " " << q6 << std::endl;
}

void Interpreter::_pnw(int playerId, int x, int y, Renderer::Compass orientation, int level, std::string teamName)
{
    std::cerr << "level: " << level << std::endl;
    (void) teamName;
    Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::BODY, playerId,
        {0.f + (x * TILE_SIZE), OFFSET_FROM_GROUND, 0.f + (y * TILE_SIZE)}, sf::Color::Cyan, "./Assets/body_golem.stl", orientation, {0.f, 0.f, 0.f}, level);
    Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::EYES, playerId,
        {0.f + (x * TILE_SIZE), OFFSET_FROM_GROUND + OFFSET_EYES_Y, 0.f + (y * TILE_SIZE) + Renderer::offsetEyesZ[level - 1]}, sf::Color::Black,
        Renderer::pathEyes[level - 1], orientation, {0.f, 0.f, 0.f}, level);
    std::cerr << " (*TILE_SIZE) x: " << x * TILE_SIZE << " y: " << y * TILE_SIZE << std::endl;
    std::cerr << "PlayerID " << playerId << std::endl;
    std::array<std::string, 4> orienToStr = {"NORTH", "EAST", "SOUTH", "WEST"};
    Renderer::histInstruc.push_back("T" + std::to_string(playerId) + ": connected at {x: " + std::to_string(x)
        + ", y: " + std::to_string(y) + ", o: " + orienToStr[static_cast<int>(orientation)] + "}");
}

void Interpreter::_ppo(int playerId, int x, int y, Renderer::Compass orientation)
{
    float currentAngle = 0.f;
    Renderer::Vec3 currentPos;

    for (auto &e : Renderer::sceneEntities) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            currentAngle = e.rotation.y;
            currentPos = e.position;
            break;
        }
    }
    std::array<std::string, 4> orienToStr = {"NORTH", "WEST", "SOUTH", "EAST"};
    Renderer::histInstruc.push_back("T" + std::to_string(playerId) + ": moved to {x: " + std::to_string(x)
        + ", y: " + std::to_string(y) + ", o: " + orienToStr[static_cast<int>(orientation)] + "}");
    std::cerr << "Pos x: " << (int)currentPos.x << " Pos z: " << (int)currentPos.z << " (*TILE_SIZE) x: " << x * TILE_SIZE << " y: " << y * TILE_SIZE << std::endl;
    std::cerr << "PPO : " << x << " " << y << std::endl;

    float targetAngle = Renderer::compassToAngle(orientation);

    // Calculation angle difference
    float delta = targetAngle - currentAngle;
    if (delta > 180.f) delta -= 360.f;
    if (delta < -180.f) delta += 360.f;

    bool goingRight = delta < 0.f; // right if negative angle (trigo)
    int stepsNeeded = static_cast<int>(std::round(std::abs(delta) / 4.5f));

    if (stepsNeeded > 0) {
        Renderer::activeRotations[playerId] = Renderer::RotationState{
            .totalRotated = 0.f,
            .timeElapsed = 0.f,
            .stepsRemaining = stepsNeeded,
            .active = true,
            .goingRight = goingRight
        };
    }

    // Check if at the same position as before
    if ((int)currentPos.x == x * TILE_SIZE && (int)currentPos.z == y * TILE_SIZE)
        return;
    // Calculation of movement direction from targeted orientation
    float angleRad = targetAngle * (3.14159265f / 180.f);

    Renderer::Vec3 dir = {
        std::sin(angleRad),  // x
        0.f,                 // y
        -std::cos(angleRad)  // z
    };

    // The entity can only start to move if no rotation is required
    if (stepsNeeded == 0) {
        Renderer::activeMovements[playerId] = Renderer::MovementState{
            .direction = {dir.x * 3.5f, dir.y * 3.5f, dir.z * 3.5f},
            .timeElapsed = 0.f,
            .stepsRemaining = 40,
            .active = true
        };
    } else {
        // Else, the movement action is stocked to be started after the rotation
        Renderer::pendingMovementsAfterRotation[playerId] = Renderer::MovementState{
            .direction = {dir.x * 3.5f, dir.y * 3.5f, dir.z * 3.5f},
            .timeElapsed = 0.f,
            .stepsRemaining = 40,
            .active = true
        };
    }
}

void Interpreter::_plv(int playerId, int level)
{
    float x;
    float z;
    bool exists = false;

    for (auto &e : Renderer::sceneEntities) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            x = e.position.x;
            z = e.position.z;
            exists = true;
            break;
        }
    }
    if (!exists) {
        std::cerr << "Somehow, the player " << playerId << " doesn't exists..." << std::endl;
        return;
    }
    for (auto it = Renderer::sceneEntities.begin(); it != Renderer::sceneEntities.end(); ) {
        Renderer::Entity &e = *it;
        // Will also remove the eyes
        if (e.clientId == playerId && e.type == Renderer::PartType::EYES && e.level != level) {
            it = Renderer::sceneEntities.erase(it);
            Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::EYES, playerId,
            {x, OFFSET_FROM_GROUND + OFFSET_EYES_Y, z + Renderer::offsetEyesZ[level - 1]}, sf::Color::Black,
            Renderer::pathEyes[level - 1], Renderer::Compass::NORTH, {0.f, 0.f, 0.f}, level);
            // std::cerr << "PathEyes: " << Renderer::pathEyes[1] << std::endl;
        } else {
            ++it;
        }
    }
}

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

void Interpreter::_pex(int playerId)
{
    (void) playerId;
}

void Interpreter::_pbc(int playerId, std::string data)
{
    Renderer::histInstruc.push_back("T" + std::to_string(playerId) +  ": broadcasts \"" + data + "\"");
}

void Interpreter::_pic(int x, int y, int level, std::vector<int> playersId)
{
    (void) level;
    (void) playersId;
    Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::RING, -1,
    {0.0f + (x * TILE_SIZE), -10.0f, 0.0f + (y * TILE_SIZE)}, sf::Color {127, 0, 255}, "./Assets/IncantationRing.stl");
    Renderer::histInstruc.push_back("T" + std::to_string(playersId.front()) +  ": start incantation at {x: " + std::to_string(x)
        + ", y: " + std::to_string(y) + "}");
}

void Interpreter::_pie(int x, int y, std::string result)
{
    (void) result;
    for (auto it = Renderer::sceneEntities.begin(); it != Renderer::sceneEntities.end(); ) {
        Renderer::Entity &e = *it;
        if (e.position.x == 0.f + (x * TILE_SIZE) && e.position.z == 0.f + (y * TILE_SIZE) && e.type == Renderer::PartType::RING) {
            it = Renderer::sceneEntities.erase(it);
        } else {
            ++it;
        }
    }
    Renderer::histInstruc.push_back("SERVER : incantation at {x:" + std::to_string(x) + ", y: " + std::to_string(y) + "} ended");
}

void Interpreter::_pfk(int playerId)
{
    (void) playerId;
}

void Interpreter::_pdr(int playerId, int resourceNumber)
{
    std::array<std::string, 6> ressources = {"LINEMATE", "DERAUMERE", "SIBUR", "MENDIANE", "PHIRAS", "THYSTAME"};
    Renderer::histInstruc.push_back("T" + std::to_string(playerId) +  ": drops " + (ressources[resourceNumber - 1]));
}

void Interpreter::_pgt(int playerId, int resourceNumber)
{
    std::array<std::string, 7> ressources = {"FOOD", "LINEMATE", "DERAUMERE", "SIBUR", "MENDIANE", "PHIRAS", "THYSTAME"};
    Renderer::histInstruc.push_back("T" + std::to_string(playerId) +  ": takes " + (ressources[resourceNumber]));
}

void Interpreter::_pdi(int playerId)
{
    for (auto it = Renderer::sceneEntities.begin(); it != Renderer::sceneEntities.end(); ) {
        Renderer::Entity &e = *it;
        // Will also remove the eyes
        if (e.clientId == playerId) {
            if (e.type == Renderer::PartType::BODY)
                std::cerr << "Player " << e.clientId << " died. Rip." << std::endl;
            it = Renderer::sceneEntities.erase(it);
        } else {
            ++it;
        }
    }
    Renderer::histInstruc.push_back("T" + std::to_string(playerId) +  ": died");
}

void Interpreter::_enw(int eggId, int playerId, int x, int y)
{
    (void) eggId;
    (void) playerId;
    (void) x;
    (void) y;
    std::cerr << "ENW : " << x << " " << y << std::endl;
}

void Interpreter::_ebo(int eggId)
{
    (void) eggId;
}

void Interpreter::_edi(int eggId)
{
    (void) eggId;
}

void Interpreter::_sgt(int timeUnit)
{
    (void) timeUnit;
}

void Interpreter::_sst(int timeUnit)
{
    (void) timeUnit;
}

void Interpreter::_seg(std::string teamName)
{
    (void) teamName;
}

void Interpreter::_smg(std::string msg)
{
    (void) msg;
}

void Interpreter::_suc(std::string data)
{
    std::cerr << "Unknown command : (" << data << ")" << std::endl;
}
