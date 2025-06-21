/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** CMDMatches
*/

#pragma once

#include <regex>

static std::regex msz(R"(msz\s+(\d+)\s+(\d+))");
static std::regex bct(R"(bct\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))");
static std::regex tna(R"(tna\s+(\S+))");
static std::regex pnw(R"(pnw\s+#(-?\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\S+))");
static std::regex ppo(R"(ppo\s+#(-?\d+)\s+(\d+)\s+(\d+))");
static std::regex plv(R"(plv\s+#(-?\d+)\s+(\d+))");
static std::regex pin(R"(pin\s+#(-?\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))");
static std::regex pex(R"(pex\s+#(-?\d+))");
static std::regex pbc(R"(pbc\s+#(-?\d+)\s+(.+))");
static std::regex pic(R"(pic\s+(\d+)\s+(\d+)\s+(\d+)(?:\s+#(-?\d+))+)");
static std::regex pie(R"(pie\s+(\d+)\s+(\d+)\s+(\d+))");
static std::regex pfk(R"(pfk\s+#(-?\d+))");
static std::regex pdr(R"(pdr\s+#(-?\d+)\s+(\d+))");
static std::regex pgt(R"(pgt\s+#(-?\d+)\s+(\d+))");
static std::regex pdi(R"(pdi\s+#(-?\d+))");
static std::regex enw(R"(enw\s+#(-?\d+)\s+#(-?\d+)\s+(\d+)\s+(\d+))");
static std::regex ebo(R"(ebo\s+#(-?\d+))");
static std::regex edi(R"(edi\s+#(-?\d+))");
static std::regex sgt(R"(sgt\s+(\d+))");
static std::regex sst(R"(sst\s+(\d+))");
static std::regex seg(R"(seg\s+(\S+))");
static std::regex smg(R"(smg\s+(.+))");
static std::regex sbp(R"(sbp)");

static std::regex playerRegex(R"(#(-?\d+))");
