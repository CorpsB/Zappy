/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AI
*/

#include "AI.hpp"
#include "../network/Socket.hpp"
#include <thread>

ai::entity::AI::AI(int id)
{
    _free_slots = 0;
    _id = id;
    _level = 1;
    _food_level = 1;
    _goal = FOOD;
    _thread_name = std::string("[Bot ") + std::to_string(id) + std::string("]");
}

void ai::entity::AI::start(const ai::parser::Config &config)
{
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    logger.setup(config.debug, _thread_name);
    logger.log("Starting...");

    _socket.setup(_thread_name, config.name);
    _socket.initSocket(config.port, config.host);
    _socket.connectServer();
    _socket.greetsServer();
}

void ai::entity::AI::stop()
{
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    logger.log("Connection closed. Final state: Level " + std::to_string(_level) +
    ", Goal " + std::to_string(_goal) + ", Food " + std::to_string(_food_level) + ".");
    logger.display();
}

std::string ai::entity::AI::doAction(const std::string &action)
{
    if (!action.empty())
        _socket.sendCommand(action);

    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    while (true) {
        const std::string result = _socket.readSocketBuffer();

        if (result == "dead")
            return "dead";
        if (result.rfind("message", 0) == 0) {
            const Direction dir = _sound_system.setSound(result);
            if (dir != NONE) {
                const SoundCell &cell = _sound_system.getDirectionSound(dir);
                logger.log("Message received from " + std::to_string(cell.id) + " '" + cell.message + "'");

                // incantate to level up
                if (cell.message == "INCANTATION_" + std::to_string(_level + 1) && dir == HERE)
                    if (!incantate(doAction("")))
                        return "dead";
            }
            continue;
        }
        if (result.rfind("eject", 0) == 0) {
            logger.log("Got ejected! " + result);
            continue;
        }
        return result;
    }
}

bool ai::entity::AI::doKoAction(const std::string &action)
{
    const std::string result = doAction(action);

    if (result == "ko") {
        utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
        logger.log("[Warn] Action failed: '" + action + "'.");
        return true;
    }
    if (result == "dead")
        return false;
    return true;
}

bool ai::entity::AI::useBroadcast(const std::string &message)
{
    return doAction("Broadcast " + std::to_string(_id) + "|" + message) != "dead";
}

void ai::entity::AI::run(const ai::parser::Config &config)
{
    start(config);
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();

    while (1) {
        // clear old broadcast messages
        _sound_system.update();

        // update inventory
        const std::string inv_str = doAction("Inventory");
        if (inv_str == "dead") {
            logger.log("Died looking Inventory.");
            break;
        }
        _inventory.update(inv_str);
        _food_level = _inventory.getItem("food");

        // check starvation
        if (_food_level < 1) {
            logger.log("Died from starvation.");
            break;
        }

        // look around
        std::string look_str = doAction("Look");
        if (look_str == "dead") {
            logger.log("Died looking around.");
            break;
        }

        // check available slots to reproduce
        if (_level < 8 && _food_level >= FOOD_THRESHOLD) {
            try {
                _free_slots = std::stoi(doAction("Connect_nbr"));
            } catch (...) {
                logger.log("Died checking slots to reproduce.");
                break;
            }
        }

        // goal fullfill
        _goal = getGoal(look_str);

        if (!performActionForGoal(look_str)) {
            logger.log("Action failed or led to 'dead' state. Terminating.");
            break;
        }
    }
    stop();
}
