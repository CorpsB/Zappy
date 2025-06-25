/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Interpreter
*/

#include "Interpreter.hpp"

Interpreter::Interpreter()
{
    _instructions = {{ "msz", std::make_pair(std::regex(R"(msz\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _msz(m); }) },
        { "bct", std::make_pair(std::regex(R"(bct\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _bct(m); }) },
        { "pnw", std::make_pair(std::regex(R"(pnw\s+#(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\S+))"), [&](const std::smatch &m) { _pnw(m); }) },
        { "ppo", std::make_pair(std::regex(R"(ppo\s+#(\d+)\s+(\d+)\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _ppo(m); }) },
        { "plv", std::make_pair(std::regex(R"(plv\s+#(\d+)\s+(\d+))"), [&](const std::smatch &m) { _plv(m); }) },
        { "pin", std::make_pair(std::regex(R"(pin\s+#(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _pin(m); }) },
        { "pex", std::make_pair(std::regex(R"(pex\s+#(\d+))"), [&](const std::smatch &m) { _pex(m); }) },
        { "pbc", std::make_pair(std::regex(R"(pbc\s+#(\d+)\s+(.+))"), [&](const std::smatch &m) { _pbc(m); }) },
        { "pic", std::make_pair(std::regex(R"(pic\s+(\d+)\s+(\d+)\s+(\d+)(?:\s+#(-?\d+))+)"), [&](const std::smatch &m) { _pic(m); }) },
        { "pie", std::make_pair(std::regex(R"(pie\s+(\d+)\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _pie(m); }) },
        { "pfk", std::make_pair(std::regex(R"(pfk\s+#(\d+))"), [&](const std::smatch &m) { _pfk(m); }) },
        { "pdr", std::make_pair(std::regex(R"(pdr\s+#(\d+)\s+(\d+))"), [&](const std::smatch &m) { _pdr(m); }) },
        { "pgt", std::make_pair(std::regex(R"(pgt\s+#(\d+)\s+(\d+))"), [&](const std::smatch &m) { _pgt(m); }) },
        { "pdi", std::make_pair(std::regex(R"(pdi\s+#(\d+))"), [&](const std::smatch &m) { _pdi(m); }) },
        { "enw", std::make_pair(std::regex(R"(enw\s+#(\d+)\s+#(-?\d+)\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _enw(m); }) },
        { "ebo", std::make_pair(std::regex(R"(ebo\s+#(\d+))"), [&](const std::smatch &m) { _ebo(m); }) },
        { "edi", std::make_pair(std::regex(R"(edi\s+#(\d+))"), [&](const std::smatch &m) { _edi(m); }) },
        { "sgt", std::make_pair(std::regex(R"(sgt\s+(\d+))"), [&](const std::smatch &m) { _sgt(m); }) },
        { "sst", std::make_pair(std::regex(R"(sst\s+(\d+))"), [&](const std::smatch &m) { _sst(m); }) },
        { "seg", std::make_pair(std::regex(R"(seg\s+(\S+))"), [&](const std::smatch &m) { _seg(m); }) },
        { "smg", std::make_pair(std::regex(R"(smg\s+(.+))"), [&](const std::smatch &m) { _smg(m); }) },
    };

    _resources = {{
        { Renderer::PartType::Q0, {25.f, -6.5f, 25.f}, sf::Color::Yellow, "./Assets/Food.stl" },
        { Renderer::PartType::Q1, {15.f, -6.5f, -25.f}, {96, 96, 96}, "./Assets/Crystals.stl" },
        { Renderer::PartType::Q2, {25.f, -6.5f, -15.f}, sf::Color::Green, "./Assets/Crystals.stl" },
        { Renderer::PartType::Q3, {-15.f, -6.5f, -25.f}, {204, 0, 102}, "./Assets/Crystals.stl" },
        { Renderer::PartType::Q4, {-25.f, -6.5f, -15.f}, {255, 255, 255}, "./Assets/Crystals.stl" },
        { Renderer::PartType::Q5, {-15.f, -6.5f, 25.f}, {127, 0, 255}, "./Assets/Crystals.stl" },
        { Renderer::PartType::Q6, {-25.f, -5.0f, 15.f}, sf::Color::Red, "./Assets/Crystals.stl", -5.0f }
    }};
}

void Interpreter::interpret(const std::string &data)
{
    std::string line;
    std::smatch matches;

    if (data == "WELCOME\n")
        return;
    _buffer += data;
    std::istringstream iss(_buffer);
    std::string newBuffer;

    while (std::getline(iss, line)) {
        bool matched = false;

        if (line.empty())
            continue;
        for (const auto &[key, pair] : _instructions) {
            const std::regex &pattern = pair.first;
            const auto &handler = pair.second;

            if (std::regex_match(line, matches, pattern)) {
                handler(matches);
                matched = true;
                break;
            }
        }
        if (!matched) {
            if (_buffer.find(line) != std::string::npos && data.find(line) == std::string::npos)
                std::cerr << "Unknown command: '" << line << "'" << std::endl;
            else
                newBuffer += line;
        }
    }
    _buffer = newBuffer;
}

void Interpreter::_msz(const std::smatch &m)
{
    int x = std::stoi(m[1]);
    int y = std::stoi(m[2]);

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

void Interpreter::_bct(const std::smatch &m)
{
    int x = std::stoi(m[1]);
    int y = std::stoi(m[2]);

    std::array<int, 7> quantities = {
        std::stoi(m[3]), std::stoi(m[4]), std::stoi(m[5]),
        std::stoi(m[6]), std::stoi(m[7]), std::stoi(m[8]),
        std::stoi(m[9])
    };

    std::array<bool, 7> exists = { false, false, false, false, false, false, false };

    for (auto it = Renderer::sceneEntities.begin(); it != Renderer::sceneEntities.end(); ) {
        Renderer::Entity &e = *it;
        bool erased = false;

        for (std::size_t i = 0; i < _resources.size(); i++) {
            const auto &r = _resources[i];
            sf::Vector3f expectedPos = {
                r.offset.x + x * TILE_SIZE,
                0.f,
                r.offset.z + y * TILE_SIZE
            };

            if (e.type == r.type && e.position.x == expectedPos.x && e.position.z == expectedPos.z) {
                if (quantities[i] == 0) {
                    it = Renderer::sceneEntities.erase(it);
                    erased = true;
                } else {
                    exists[i] = true;
                }
                break;
            }
        }
        if (!erased)
            it++;
    }
    for (std::size_t i = 0; i < _resources.size(); i++) {
        if (quantities[i] != 0 && !exists[i]) {
            const auto &r = _resources[i];
            sf::Vector3f pos = {
                r.offset.x + x * TILE_SIZE,
                r.yAdjust,
                r.offset.z + y * TILE_SIZE
            };

            Renderer::spawn(Renderer::EntityType::STL, r.type, -1, { pos.x, pos.y, pos.z }, r.color, r.assetPath, Renderer::Compass::NORTH, { 0.f, Renderer::getRandomAngle(), 0.f });
        }
    }
}

void Interpreter::_pnw(const std::smatch &m)
{
    int playerId = std::stoi(m[1]);
    int x = std::stoi(m[2]);
    int y = std::stoi(m[3]);
    Renderer::Compass orientation = static_cast<Renderer::Compass>(std::stoi(m[4]));
    int level = std::stoi(m[5]);
    std::string teamName = m[6].str();

    Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::BODY, playerId,
        {0.f + (x * TILE_SIZE), OFFSET_FROM_GROUND, 0.f + (y * TILE_SIZE)}, sf::Color::Cyan, "./Assets/body_golem.stl", orientation, {0.f, 0.f, 0.f}, level);
    Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::EYES, playerId,
        {0.f + (x * TILE_SIZE), OFFSET_FROM_GROUND + OFFSET_EYES_Y, 0.f + (y * TILE_SIZE) + Renderer::offsetEyesZ[level - 1]}, sf::Color::Black,
        Renderer::pathEyes[level - 1], orientation, {0.f, 0.f, 0.f}, level);
    std::array<std::string, 4> orienToStr = { "NORTH", "EAST", "SOUTH", "WEST" };
    Renderer::histInstruc.push_back("T" + std::to_string(playerId) + ": connected at {x: " + std::to_string(x) +
        ", y: " + std::to_string(y) + ", o: " + orienToStr[static_cast<int>(orientation)] + "}");
}

void Interpreter::_ppo(const std::smatch &m)
{
    int playerId = std::stoi(m[1]);
    int x = std::stoi(m[2]);
    int y = std::stoi(m[3]);
    Renderer::Compass orientation = static_cast<Renderer::Compass>(std::stoi(m[4]));

    float currentAngle = 0.f;
    Renderer::Vec3 currentPos;

    for (auto &e : Renderer::sceneEntities) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            currentAngle = e.rotation.y;
            currentPos = e.position;
            break;
        }
    }
    std::array<std::string, 4> orienToStr = { "NORTH", "WEST", "SOUTH", "EAST" };
    Renderer::histInstruc.push_back("T" + std::to_string(playerId) + ": moved to {x: " + std::to_string(x)
        + ", y: " + std::to_string(y) + ", o: " + orienToStr[static_cast<int>(orientation)] + "}");

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

void Interpreter::_plv(const std::smatch &m)
{
    int playerId = std::stoi(m[1]);
    int level = std::stoi(m[2]);

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

void Interpreter::_pin(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_pex(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_pbc(const std::smatch &m)
{
    int playerId = std::stoi(m[1]);
    std::string data = m[2].str();

    Renderer::histInstruc.push_back("T" + std::to_string(playerId) + ": broadcast \"" + data + "\"");
}

void Interpreter::_pic(const std::smatch &m)
{
    int x = std::stoi(m[1]);
    int y = std::stoi(m[2]);
    // int level = std::stoi(m[3]);
    std::vector<int> playersId;
    std::string full = m[0].str();
    std::regex idRegex(R"#(#(-?\d+))#");
    auto begin = std::sregex_iterator(full.begin(), full.end(), idRegex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; it++)
        playersId.push_back(std::stoi((*it)[1].str()));
    Renderer::spawn(Renderer::EntityType::STL, Renderer::PartType::RING, -1,
        {0.0f + (x * TILE_SIZE), -10.0f, 0.0f + (y * TILE_SIZE)}, sf::Color {127, 0, 255}, "./Assets/IncantationRing.stl");
    Renderer::histInstruc.push_back("T" + std::to_string(playersId.front()) + ": start incantation at {x: " + std::to_string(x)
        + ", y: " + std::to_string(y) + "}");
}

void Interpreter::_pie(const std::smatch &m)
{
    int x = std::stoi(m[1]);
    int y = std::stoi(m[2]);
    std::string result = m[3].str();

    for (auto it = Renderer::sceneEntities.begin(); it != Renderer::sceneEntities.end(); ) {
        Renderer::Entity &e = *it;
        if (e.position.x == 0.f + (x * TILE_SIZE) && e.position.z == 0.f + (y * TILE_SIZE) && e.type == Renderer::PartType::RING) {
            it = Renderer::sceneEntities.erase(it);
        } else {
            ++it;
        }
    }
    Renderer::histInstruc.push_back("SERVER : incantation at {x:" + std::to_string(y) + "} ended");
}

void Interpreter::_pfk(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_pdr(const std::smatch &m)
{
    int playerId = std::stoi(m[1]);
    int resourceNumber = std::stoi(m[2]);
    std::array<std::string, 7> resourcesName = { "FOOD", "LINEMATE", "DERAUMERE", "SIBUR", "MENDIANE", "PHIRAS", "THYSTAME" };

    Renderer::histInstruc.push_back("T" + std::to_string(playerId) +  ": drops " + (resourcesName[resourceNumber - 1]));
}

void Interpreter::_pgt(const std::smatch &m)
{
    int playerId = std::stoi(m[1]);
    int resourceNumber = std::stoi(m[2]);
    std::array<std::string, 7> resourcesName = { "FOOD", "LINEMATE", "DERAUMERE", "SIBUR", "MENDIANE", "PHIRAS", "THYSTAME" };

    Renderer::histInstruc.push_back("T" + std::to_string(playerId) +  ": takes " + (resourcesName[resourceNumber]));
}

void Interpreter::_pdi(const std::smatch &m)
{
    int playerId = std::stoi(m[1]);

    for (auto it = Renderer::sceneEntities.begin(); it != Renderer::sceneEntities.end(); ) {
        Renderer::Entity &e = *it;
        if (e.clientId == playerId) {
            if (e.type == Renderer::PartType::BODY)
                std::cerr << "Player " << e.clientId << " died. Rip." << std::endl;
            it = Renderer::sceneEntities.erase(it);
        } else {
            ++it;
        }
    }
    Renderer::histInstruc.push_back("T" + std::to_string(playerId) + ": died");
}

void Interpreter::_enw(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_ebo(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_edi(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_sgt(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_sst(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_seg(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_smg(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_suc(const std::smatch &m)
{
    (void) m;
    std::cerr << "Unknown command" << std::endl;
}
