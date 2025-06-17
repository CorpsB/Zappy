/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** CMDMatches
*/

#pragma once

#include <regex>

static std::regex msz(R"(msz\s+(\d+)\s+(\d+);)");
static std::regex bct(R"(bct\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))");
static std::regex tna(R"(tna\s+(\S+))");
