/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** ipv4
*/

/**
 * @file ipv4.cpp
 * @brief Helper for validating IPv4 addresses.
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @see ai::utils::validation::ipv4
 */

#include "../utils.hpp"
#include <sstream>

/**
 * @brief Checks internal IPv4 formatting rules on each segment.
 * @param ip The IPv4 string to inspect.
 * @return true if ip consists of exactly four numeric segments in [0,255], false otherwise.
 */
static bool assert_ipv4(const std::string &ip)
{
    std::stringstream ss(ip);
    std::string segment;
    int count = 0;
    int val;

    for (; std::getline(ss, segment, '.'); ++count) {
        if (count > 4)
            return false;
        if (segment.empty() || segment.size() > 3)
            return false;
        val = std::stoi(segment);
        if (val < 0 || val > 255)
            return false;
        if (!ai::utils::validation::integer(val, segment))
            return false;
    }
    return count == 4;
}

bool ai::utils::validation::ipv4(const std::string &ip)
{
    if (assert_ipv4(ip))
        return true;
    utils::debug::Logger &logger = utils::debug::Logger::GetInstance();
    logger.log("[Error] Invalid ipv4 " + ip);
    return false;
}
