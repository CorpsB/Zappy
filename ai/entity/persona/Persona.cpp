/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Persona
*/

/**
 * @file Persona.cpp
 * @brief Implements Persona methods for generating and exposing trait values.  
 * @author Jason KOENIG
 * @version 1.0
 * @date 29/06/2025
 *
 * @see Persona.hpp
 */

#include "Persona.hpp"
#include "../../utils/utils.hpp"

ai::entity::Persona::Persona()
{
    generatePersona();
}

unsigned int ai::entity::Persona::getIntroversion()
{
    return _introversion;
}

unsigned int ai::entity::Persona::getLostInThought()
{
    return _lost_in_thought;
}

unsigned int ai::entity::Persona::getEmpatic()
{
    return _empatic;
}

unsigned int ai::entity::Persona::getSpontaneous()
{
    return _spontaneous;
}

std::string ai::entity::Persona::getMBTI()
{
    const unsigned int mbti = utils::random::number(0, 100);

    if (mbti < 13)
        return std::string("ISFJ");
    if (mbti < 25.5)
        return std::string("ISTJ");
    if (mbti < 36.5)
        return std::string("ESFJ");
    if (mbti < 45.5)
        return std::string("ESTJ");
    if (mbti < 52.5)
        return std::string("ENFP");
    if (mbti < 59.5)
        return std::string("ISTP");
    if (mbti < 66)
        return std::string("ESFP");
    if (mbti < 72)
        return std::string("ISFP");
    if (mbti < 78)
        return std::string("ESTP");
    if (mbti < 83.5)
        return std::string("ENTP");
    if (mbti < 88.5)
        return std::string("INFP");
    if (mbti < 93)
        return std::string("INTP");
    if (mbti < 95.5)
        return std::string("ENFJ");
    if (mbti < 97.5)
        return std::string("ENTJ");
    if (mbti < 99)
        return std::string("INTJ");
    return std::string("INFJ");
}

void ai::entity::Persona::generatePersona()
{
    const std::string mbti = getMBTI();

    _introversion = mbti[0] == 'E' ? utils::random::number(0, 50) : utils::random::number(50, 100);
    _lost_in_thought = mbti[0] == 'S' ? utils::random::number(0, 50) : utils::random::number(50, 100);
    _empatic = mbti[0] == 'T' ? utils::random::number(0, 50) : utils::random::number(50, 100);
    _spontaneous = mbti[0] == 'J' ? utils::random::number(0, 50) : utils::random::number(50, 100);
}
