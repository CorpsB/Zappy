/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Interpreter
*/

/**
 * @file Interpreter.cpp
 * @brief Implementation of the Interpreter class for handling server commands in the Zappy client.
 *
 * This file implements the logic of the `Interpreter` class, which is responsible for parsing,
 * matching, and executing commands sent by the Zappy server using regular expressions.
 * Each recognized instruction is associated with a handler function that applies changes
 * to the in-game 3D world using the `Renderer` system.
 *
 * Commands such as map updates (`msz`, `bct`), player actions (`pnw`, `ppo`, `pdi`, etc.),
 * and global events (`seg`, `smg`) are all processed dynamically through a dispatch table
 * built with regex-function pairs.
 *
 * The interpreter updates the 3D scene by spawning or removing entities (players, eggs, items),
 * adjusting player orientation or movement, managing team colors, and displaying broadcast messages.
 * It also ensures buffered input is correctly reprocessed in case of partial data.
 *
 * Constants like `TILE_SIZE`, `OFFSET_FROM_GROUND`, and `OFFSET_EYES_Y` control
 * visual placement and animation behavior.
 *
 * @author Thomas Camuset
 * @date 2025
 * @version 1.0
 * @see Interpreter.hpp, Renderer, sf::Color
 * @note This interpreter is designed to be easily extended with new command patterns.
 */

#include "Interpreter.hpp"

Interpreter::Interpreter(std::shared_ptr<Renderer::Renderer> renderer, std::shared_ptr<Renderer::EntityClass> entity)
{
    this->_renderer = renderer;
    this->_entity = entity;
    _instructions = {{ "msz", std::make_pair(std::regex(R"(msz\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _msz(m); }) },
        { "bct", std::make_pair(std::regex(R"(bct\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _bct(m); }) },
        { "tna", std::make_pair(std::regex(R"(tna\s+(\S+))"), [&](const std::smatch &m) { _tna(m); }) },
        { "pnw", std::make_pair(std::regex(R"(pnw\s+#(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\S+))"), [&](const std::smatch &m) { _pnw(m); }) },
        { "ppo", std::make_pair(std::regex(R"(ppo\s+#(\d+)\s+(\d+)\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _ppo(m); }) },
        { "plv", std::make_pair(std::regex(R"(plv\s+#(\d+)\s+(\d+))"), [&](const std::smatch &m) { _plv(m); }) },
        { "pin", std::make_pair(std::regex(R"(pin\s+#(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))"), [&](const std::smatch &m) { _pin(m); }) },
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
        { Renderer::PartType::Q0, {25.f, -6.5f, 15.f}, sf::Color::Yellow, "./bonus/Assets/Food.stl" },
        { Renderer::PartType::Q1, {15.f, -6.5f, -25.f}, {96, 96, 96}, "./bonus/Assets/Crystals.stl" },
        { Renderer::PartType::Q2, {25.f, -6.5f, -15.f}, sf::Color::Green, "./bonus/Assets/Crystals.stl" },
        { Renderer::PartType::Q3, {-15.f, -6.5f, -25.f}, {204, 0, 102}, "./bonus/Assets/Crystals.stl" },
        { Renderer::PartType::Q4, {-25.f, -6.5f, -15.f}, {255, 255, 255}, "./bonus/Assets/Crystals.stl" },
        { Renderer::PartType::Q5, {-15.f, -6.5f, 25.f}, {127, 0, 255}, "./bonus/Assets/Crystals.stl" },
        { Renderer::PartType::Q6, {-25.f, -6.5f, 15.f}, sf::Color::Red, "./bonus/Assets/Crystals.stl"}
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
    const int x = std::stoi(m[1]);
    const int y = std::stoi(m[2]);

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++) {
            if (j == 0 && i == 0) {
                _entity.get()->spawn(Renderer::EntityType::STL, Renderer::PartType::GROUND, -1,
                {0.0f + (i * TILE_SIZE), 0.0f, 0.0f + (j * TILE_SIZE)}, sf::Color::Red, "./bonus/Assets/ground.stl");
            } else
                _entity.get()->spawn(Renderer::EntityType::STL, Renderer::PartType::GROUND, -1,
                {0.0f + (i * TILE_SIZE), 0.0f, 0.0f + (j * TILE_SIZE)}, sf::Color {65, 65, 65}, "./bonus/Assets/ground.stl");
            _renderer.get()->addToResourcesOnTiles(i * y + j, {0, 0, 0, 0, 0, 0, 0});
        }
    _renderer.get()->setMapSizeX(x);
    _renderer.get()->setMapSizeY(y);
    // Renderer::map_size_x = x;
    // Renderer::map_size_y = y;
}

void Interpreter::_bct(const std::smatch &m)
{
    const int x = std::stoi(m[1]);
    const int y = std::stoi(m[2]);

    std::array<int, 7> quantities = {
        std::stoi(m[3]), std::stoi(m[4]), std::stoi(m[5]),
        std::stoi(m[6]), std::stoi(m[7]), std::stoi(m[8]),
        std::stoi(m[9])
    };

    _renderer.get()->setResourcesChange(true);
    _renderer.get()->addToResourcesOnTiles(x * _renderer.get()->getMapSizeY() + y, quantities);

    // Renderer::resourcesChange = true;
    // Renderer::_resourcesOnTiles[x * Renderer::map_size_y + y] = quantities;

    std::array<bool, 7> exists = { false, false, false, false, false, false, false };

    for (auto it = _entity.get()->getSceneEntities().begin(); it != _entity.get()->getSceneEntities().end(); ) {
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
                    it = _entity.get()->getSceneEntities().erase(it);
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

            _entity.get()->spawn(Renderer::EntityType::STL, r.type, -1, { pos.x, pos.y, pos.z }, r.color, r.assetPath, Renderer::Compass::NORTH, { 0.f, Renderer::getRandomAngle(), 0.f });
        }
    }
}

void Interpreter::_tna(const std::smatch &m)
{
    (void) m;
}

void Interpreter::_pnw(const std::smatch &m)
{
    const int playerId = std::stoi(m[1]);
    const int x = std::stoi(m[2]);
    const int y = std::stoi(m[3]);
    const auto orientation = static_cast<Renderer::Compass>(std::stoi(m[4]) - 1);
    const int level = std::stoi(m[5]);
    const std::string &teamName = m[6];
    auto colorIt = _teamColor.find(teamName);

    if (colorIt == _teamColor.end()) {
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_int_distribution<int> dis(0, 255);
        sf::Color color = {0, 0, 0};

        while (color.r + color.g + color.b < 55 || !_bigEnoughDiffColor(color)) {
            color.r = dis(gen);
            color.g = dis(gen);
            color.b = dis(gen);
        }
        colorIt = _teamColor.emplace(teamName, color).first;
    }

    const float posX = x * TILE_SIZE;
    const float posY = y * TILE_SIZE;

    _entity.get()->spawn(Renderer::EntityType::STL, Renderer::PartType::BODY, playerId,
        {posX, OFFSET_FROM_GROUND, posY}, colorIt->second, "./bonus/Assets/body_golem.stl",
        orientation, {0.f, static_cast<float>(90 * static_cast<int>(orientation)), 0.f}, level, teamName);
    _entity.get()->spawn(Renderer::EntityType::STL, Renderer::PartType::EYES, playerId,
        {posX, OFFSET_FROM_GROUND + OFFSET_EYES_Y, posY + _entity.get()->getOffsetEyesZ()[level - 1]},
        sf::Color::Black, _entity.get()->getPathEyes()[level - 1], orientation, {0.f, 0.f, 0.f}, level);

    static constexpr std::array<std::string_view, 4> orienToStr = { "NORTH", "WEST", "SOUTH", "EAST" };

    std::ostringstream oss;

    oss << "T" << playerId << ": connected at {x: " << x
        << ", y: " << y << ", o: " << orienToStr[static_cast<int>(orientation)] << "}";
    _renderer.get()->addToHistInstruc(oss.str(), colorIt->second);
}

void Interpreter::_ppo(const std::smatch &m)
{
    const int playerId = std::stoi(m[1]);
    const int x = std::stoi(m[2]);
    const int y = std::stoi(m[3]);
    const auto orientation = static_cast<Renderer::Compass>(std::stoi(m[4]) - 1);
    constexpr float tileSize = static_cast<float>(TILE_SIZE);

    float currentAngle = 0.f;
    Renderer::Vec3 currentPos{};
    sf::Color color = sf::Color::White;

    for (auto &e : _entity.get()->getSceneEntities()) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            currentAngle = e.rotation.y;
            currentPos = e.position;
            color = e.color;
            // Actualises the compass of the entity
            e.orientation = orientation;
            break;
        }
    }
    if (static_cast<int>(currentPos.x) % TILE_SIZE != 0)
        currentPos.x = std::round(currentPos.x / tileSize) * tileSize;
    if (static_cast<int>(currentPos.z) % TILE_SIZE != 0)
        currentPos.z = std::round(currentPos.z / tileSize) * tileSize;

    static constexpr std::array<std::string_view, 4> orienToStr = { "NORTH", "WEST", "SOUTH", "EAST" };

    std::ostringstream oss;

    oss << "T" << playerId << ": moved to {x: " << x << ", y: " << y
        << ", o: " << orienToStr[static_cast<int>(orientation)] << "}";
    _renderer.get()->addToHistInstruc(oss.str(), color);

    float targetAngle = _entity.get()->compassToAngle(orientation);

    float delta = targetAngle - currentAngle;
    if (delta > 180.f)
        delta -= 360.f;
    if (delta < -180.f)
        delta += 360.f;

    const bool goingRight = delta < 0.f;
    const int stepsNeeded = static_cast<int>(std::round(std::abs(delta) / 4.5f));

    if (stepsNeeded > 0) {
        _renderer.get()->addToActiveRotations(playerId, Renderer::RotationState{
            .totalRotated = 0.f,
            .timeElapsed = 0.f,
            .stepsRemaining = stepsNeeded,
            .active = true,
            .goingRight = goingRight
        });
    }

    const int cx = static_cast<int>(currentPos.x / tileSize);
    const int cy = static_cast<int>(currentPos.z / tileSize);
    const int dx = std::abs(cx - x);
    const int dy = std::abs(cy - y);

    const int wrapX = _renderer.get()->getMapSizeX() - 1;
    const int wrapY = _renderer.get()->getMapSizeY() - 1;

    if ((dx + dy > 1) && std::abs(cx % wrapX - x) != wrapX && std::abs(cy % wrapY - y) != wrapY) {
        for (auto &e : _entity.get()->getSceneEntities()) {
            if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
                e.position.x = x * tileSize;
                e.position.z = y * tileSize;
                _renderer.get()->addToHistInstruc("/!\\ ~~ T" + std::to_string(playerId) + ": Recalibration ~~ /!\\", color);
                return;
            }
        }
    }
    if (static_cast<int>(currentPos.x) == x * TILE_SIZE && static_cast<int>(currentPos.z) == y * TILE_SIZE)
        return;
    float angleRad = targetAngle * (3.14159265f / 180.f);
    Renderer::Vec3 dir = { std::sin(angleRad), 0.f, -std::cos(angleRad) };
    Renderer::Vec3 velocity = { dir.x * 3.5f, dir.y * 3.5f, dir.z * 3.5f };
    auto movementState = Renderer::MovementState{
        .direction = velocity,
        .timeElapsed = 0.f,
        .stepsRemaining = 40,
        .active = true
    };

    if (stepsNeeded == 0)
        _renderer.get()->addToActiveMovements(playerId, movementState);
    else
        _renderer.get()->addToPendingMovements(playerId, movementState);
}

void Interpreter::_plv(const std::smatch &m)
{
    const int playerId = std::stoi(m[1]);
    const int level = std::stoi(m[2]);
    const int levelIndex = level - 1;

    auto it = std::find_if(_entity.get()->getSceneEntities().begin(), _entity.get()->getSceneEntities().end(),
        [playerId](const Renderer::Entity &e) {
            return e.clientId == playerId && e.type == Renderer::PartType::BODY;
    });
    if (it == _entity.get()->getSceneEntities().end()) {
        std::cerr << "Somehow, the player " << playerId << " doesn't exist..." << std::endl;
        return;
    }
    const float x = it->position.x;
    const float z = it->position.z;
    const sf::Color &color = it->color;

    for (auto it = _entity.get()->getSceneEntities().begin(); it != _entity.get()->getSceneEntities().end(); ) {
        if (it->clientId == playerId && it->type == Renderer::PartType::EYES && it->level != level) {
            it = _entity.get()->getSceneEntities().erase(it);
            _entity.get()->spawn(Renderer::EntityType::STL, Renderer::PartType::EYES, playerId,
                {x, OFFSET_FROM_GROUND + OFFSET_EYES_Y, z + _entity.get()->getOffsetEyesZ()[levelIndex]},
                sf::Color::Black, _entity.get()->getPathEyes()[levelIndex],
                Renderer::Compass::NORTH, {0.f, 0.f, 0.f}, level);
            std::ostringstream oss;

            oss << "T" << playerId << ": became level " << level;
            _renderer.get()->addToHistInstruc(oss.str(), color);
        } else {
            ++it;
        }
    }
}

void Interpreter::_pin(const std::smatch &m)
{
    const int playerId = std::stoi(m[1]);
    // int x = std::stoi(m[2]);
    // int y = std::stoi(m[3]);

    const std::array<int, 7> quantities = {
        std::stoi(m[4]), std::stoi(m[5]), std::stoi(m[6]),
        std::stoi(m[7]), std::stoi(m[8]), std::stoi(m[9]),
        std::stoi(m[10])
    };

    for (auto &e : _entity.get()->getSceneEntities()) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            e.inventory = quantities;
            break;
        }
    }
}

void Interpreter::_pex(const std::smatch &m)
{
    int playerId = std::stoi(m[1]);

    for (auto &e : _entity.get()->getSceneEntities()) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            _entity.get()->spawn(Renderer::EntityType::STL, Renderer::PartType::BODY, playerId,
            {e.position.x, e.position.y, e.position.z}, e.color, "./bonus/Assets/Expulsion.stl",
            e.orientation);
            _renderer.get()->addToHistInstruc("T" + std::to_string(playerId) + " is launching EXPULSION", e.color);
            break;
        }
    }
}

void Interpreter::_pbc(const std::smatch &m)
{
    int playerId = std::stoi(m[1]);
    std::string data = m[2].str();
    sf::Color color = sf::Color::White;

    for (auto &e : _entity.get()->getSceneEntities()) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            color = e.color;
            break;
        }
    }
    std::ostringstream oss;

    oss << "T" << playerId << ": broadcast \"" << data << "\"";
    _renderer.get()->addToHistInstruc(oss.str(), color);

    // _renderer.get()->addToHistInstrucd::make_tuple("T" + std::to_string(playerId) + ": broadcast \"" + data + "\"", color));
}

void Interpreter::_pic(const std::smatch &m)
{
    const int x = std::stof(m[1]);
    const int y = std::stof(m[2]);

    std::vector<int> playersId;
    const std::string &full = m[0].str();
    const std::regex idRegex(R"#(#(-?\d+))#");
    
    for (std::sregex_iterator it(full.begin(), full.end(), idRegex), end; it != end; ++it)
        playersId.push_back(std::stoi((*it)[1].str()));

    _entity.get()->spawn(Renderer::EntityType::STL, Renderer::PartType::RING, -1,
        {0.0f + x * TILE_SIZE, -10.0f, 0.0f + y * TILE_SIZE}, sf::Color{127, 0, 255}, "./bonus/Assets/IncantationRing.stl");

    if (playersId.empty())
        return;

    sf::Color color = sf::Color::White;
    const int firstPlayerId = playersId.front();

    for (const auto &e : _entity.get()->getSceneEntities()) {
        if (e.clientId == firstPlayerId && e.type == Renderer::PartType::BODY) {
            color = e.color;
            break;
        }
    }
    std::ostringstream oss;

    oss << "T" << firstPlayerId << ": start incantation at {x: " << x << ", y: " << y << "}";
    _renderer.get()->addToHistInstruc(oss.str(), color);
}

void Interpreter::_pie(const std::smatch &m)
{
    const int x = std::stoi(m[1]);
    const int y = std::stoi(m[2]);
    const std::string &result = m[3];

    const float posX = x * TILE_SIZE;
    const float posZ = y * TILE_SIZE;

    for (auto it = _entity.get()->getSceneEntities().begin(); it != _entity.get()->getSceneEntities().end(); ) {
        if (it->position.x == posX && it->position.z == posZ && it->type == Renderer::PartType::RING) {
            it = _entity.get()->getSceneEntities().erase(it);
        } else {
            ++it;
        }
    }
    std::ostringstream oss;

    oss << "SERVER: incantation at {x:" << x << ", y:" << y << "} ended";
    _renderer.get()->addToHistInstruc(oss.str(), sf::Color::White);
}

void Interpreter::_pfk(const std::smatch &m)
{
    const int playerId = std::stoi(m[1]);

    for (const auto &e : _entity.get()->getSceneEntities()) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            std::ostringstream oss;

            oss << "T" << playerId << " layed an egg";
            _renderer.get()->addToHistInstruc(oss.str(), e.color);
            return;
        }
    }
}

void Interpreter::_pdr(const std::smatch &m)
{
    const int playerId = std::stoi(m[1]);
    const int resourceNumber = std::stoi(m[2]);

    static constexpr std::array<std::string_view, 7> resourcesName = { "FOOD", "LINEMATE", "DERAUMERE", "SIBUR", "MENDIANE", "PHIRAS", "THYSTAME" };

    if (resourceNumber > static_cast<int>(resourcesName.size())) {
        std::cerr << "Invalid resource number: " << resourceNumber << std::endl;
        return;
    }
    sf::Color color = sf::Color::White;

    for (const auto &e : _entity.get()->getSceneEntities()) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            color = e.color;
            break;
        }
    }
    std::ostringstream oss;

    oss << "T" << playerId << ": drops " << resourcesName[resourceNumber];
    _renderer.get()->addToHistInstruc(oss.str(), color);
}

void Interpreter::_pgt(const std::smatch &m)
{
    const int playerId = std::stoi(m[1]);
    const int resourceNumber = std::stoi(m[2]);

    static constexpr std::array<std::string_view, 7> resourcesName = { "FOOD", "LINEMATE", "DERAUMERE", "SIBUR", "MENDIANE", "PHIRAS", "THYSTAME" };

    if (resourceNumber > static_cast<int>(resourcesName.size())) {
        std::cerr << "Invalid resource number: " << resourceNumber << std::endl;
        return;
    }
    sf::Color color = sf::Color::White;

    for (const auto &e : _entity.get()->getSceneEntities()) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            color = e.color;
            break;
        }
    }
    std::ostringstream oss;

    oss << "T" << playerId << ": takes " << resourcesName[resourceNumber];
    _renderer.get()->addToHistInstruc(oss.str(), color);
}


void Interpreter::_pdi(const std::smatch &m)
{
    const int playerId = std::stoi(m[1]);
    sf::Color color = sf::Color::White;
    float x = 0.f;
    float z = 0.f;

    for (auto it = _entity.get()->getSceneEntities().begin(); it != _entity.get()->getSceneEntities().end(); ) {
        if (it->clientId == playerId) {
            if (static_cast<int>(it->position.x) % TILE_SIZE != 0)
                it->position.x = std::round(it->position.x / TILE_SIZE) * TILE_SIZE;
            if (static_cast<int>(it->position.z) % TILE_SIZE != 0)
                it->position.z = std::round(it->position.z / TILE_SIZE) * TILE_SIZE;
            if (it->type == Renderer::PartType::BODY)
                color = it->color;
            x = it->position.x;
            z = it->position.z;
            it = _entity.get()->getSceneEntities().erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = _entity.get()->getSceneEntities().begin(); it != _entity.get()->getSceneEntities().end(); ) {
        if (it->type == Renderer::PartType::RING && x == it->position.x && z == it->position.z) {
            it = _entity.get()->getSceneEntities().erase(it);
        } else
            ++it;
    }
    std::ostringstream oss;

    oss << "T" << playerId << ": died";
    _renderer.get()->addToHistInstruc(oss.str(), color);
}

void Interpreter::_enw(const std::smatch &m)
{
    const int eggId = std::stoi(m[1]);
    const int playerId = std::stoi(m[2]);
    const int x = std::stoi(m[3]);
    const int y = std::stoi(m[4]);

    const float posX = x * TILE_SIZE + 15.f;
    const float posZ = y * TILE_SIZE + 25.f;

    for (const auto &e : _entity.get()->getSceneEntities()) {
        if (e.clientId == playerId && e.type == Renderer::PartType::BODY) {
            _entity.get()->spawn(Renderer::EntityType::STL, Renderer::PartType::EGG, eggId, {posX, OFFSET_FROM_GROUND, posZ}, e.color,
                "./bonus/Assets/Egg.stl", Renderer::Compass::NORTH, {0.f, 0.f, 0.f}, -1, e.teamName);
            return;
        }
    }
}

void Interpreter::_ebo(const std::smatch &m)
{
    const int eggId = std::stoi(m[1]);

    for (auto it = _entity.get()->getSceneEntities().begin(); it != _entity.get()->getSceneEntities().end(); ) {
        if (it->clientId == eggId && it->type == Renderer::PartType::EGG) {
            std::ostringstream oss;

            oss << "Egg #" << eggId << " hatched !";
            _renderer.get()->addToHistInstruc(oss.str(), it->color);
            it = _entity.get()->getSceneEntities().erase(it);
            return;
        } else {
            ++it;
        }
    }
}

void Interpreter::_edi(const std::smatch &m)
{
    const int eggId = std::stoi(m[1]);

    for (auto it = _entity.get()->getSceneEntities().begin(); it != _entity.get()->getSceneEntities().end(); ) {
        if (it->clientId == eggId && it->type == Renderer::PartType::EGG) {
            std::ostringstream oss;

            oss << "Egg #" << eggId << " died...";
            _renderer.get()->addToHistInstruc(oss.str(), it->color);
            it = _entity.get()->getSceneEntities().erase(it);
            return;
        } else {
            ++it;
        }
    }
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

bool Interpreter::_bigEnoughDiffColor(sf::Color newColor)
{
    if (_teamColor.empty())
        return true;
    for (auto &e : _entity.get()->getSceneEntities()) {
        sf::Color color = _teamColor[e.teamName];
        // minimum euclidian distance > 100 --> about 15-25 teams
        int dr = static_cast<int>(color.r) - static_cast<int>(newColor.r);
        int dg = static_cast<int>(color.g) - static_cast<int>(newColor.g);
        int db = static_cast<int>(color.b) - static_cast<int>(newColor.b);
        if (std::sqrt(dr * dr + dg * dg + db * db) < 100.0f)
            return false;
    }
    return true;
}
