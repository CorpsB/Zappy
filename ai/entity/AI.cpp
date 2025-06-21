/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** AI
*/

#include "AI.hpp"
#include "../network/Socket.hpp"

ai::entity::AI::AI(int id)
{
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
    logger.display();
}

std::string ai::entity::AI::doAction(const std::string &action)
{
    const std::string result = _socket.doAction(action);
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();

    if (result == "dead")
        return "dead";
    if (result.rfind("message", 0) == 0) {
        const Direction dir = _sound_system.setSound(result);
        const SoundCell &cell = _sound_system.getDirectionSound(dir);
        logger.log("Message received from " + std::to_string(cell.id) + " '" + cell.message + "'");
        return doAction(action);
    }
    if (result.rfind("eject", 0) == 0) {
        logger.log("Got ejected! " + result);
        return doAction(action);
    }
    return result;
}

void ai::entity::AI::run(const ai::parser::Config &config)
{
    start(config);
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();

    try {
        while (1) {
            // update inventory
            const std::string inv_str = doAction("Inventory");
            if (inv_str == "dead") {
                logger.log("Died looking Inventory.");
                break;
            }
            _inventory.update(inv_str);

            // check starvation
            if (_inventory.getItem("food") < 1) {
                logger.log("Died from starvation.");
                break;
            }

            // look around
            const std::string look_str = doAction("Look");
            if (look_str == "dead") {
                logger.log("Died looking around.");
                break;
            }

            // goal fullfill
            _goal = getGoal(look_str);
            logger.log("Tick: Lvl:" + std::to_string(_level) + ", Food:" +
            std::to_string(_food_level) + ", Goal:" + std::to_string(_goal) +
            ", HeardK:{last_k_for_decision}, Inv:" + _inventory.print());
        }
    } catch (...) {
    }
    stop();
}
