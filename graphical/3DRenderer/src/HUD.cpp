/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** HUD
*/

#include "HUD.hpp"

namespace Renderer {

    Hud::Hud()
    {
        std::array<std::string, 4> orientation = {"NORTH", "WEST", "SOUTH", "EAST"};
        colorResources = {
            sf::Color::Yellow,
            sf::Color {96, 96, 96},
            sf::Color::Green,
            sf::Color {204, 0, 102},
            sf::Color {255, 255, 255},
            sf::Color {127, 0, 255},
            sf::Color::Red
        };
        nameResources = {
            "FOOD: ",
            "LINEMATE: ",
            "DERAUMERE: ",
            "SIBUR: ",
            "MENDIANE: ",
            "PHIRAS: ",
            "THYSTAME: "
        };
    }

    void Hud::init(sf::Font &hudFont)
    {
        hudText.setFont(hudFont);
        hudText.setCharacterSize(16);
        hudText.setFillColor(sf::Color::White);
        hudText.setOutlineColor(sf::Color::Black);
        hudText.setOutlineThickness(1.0f);
    }

    void Hud::displayInfoTrantorian(Entity currentTrantorian, sf::RenderWindow &window)
    {
        if (currentTrantorian.clientId != -1) {
            float y = 100.f;
            hudText.setFillColor(currentTrantorian.color);
            // id trantorian
            hudText.setString("Id Trantorian: " + std::to_string(currentTrantorian.clientId));
            hudText.setPosition(50.f, y);
            window.draw(hudText);
            // team name
            hudText.setString("Team: " + currentTrantorian.teamName);
            hudText.setPosition(50.f, y + 25.f);
            window.draw(hudText);
            // level
            hudText.setString("Level: " + std::to_string(currentTrantorian.level));
            hudText.setPosition(50.f, y + 50.f);
            window.draw(hudText);
            // position
            hudText.setString("Position:");
            hudText.setPosition(50.f, y + 75.f);
            window.draw(hudText);
            hudText.setString("x: " + std::to_string(static_cast<int>(currentTrantorian.position.x) / 70) +
                                "(real value: " + std::to_string(static_cast<int>(currentTrantorian.position.x)) + ")");
            hudText.setPosition(75.f, y + 100.f);
            window.draw(hudText);
            hudText.setString("y: " + std::to_string(static_cast<int>(currentTrantorian.position.z) / 70) +
                                "(real value: " + std::to_string(static_cast<int>(currentTrantorian.position.z)) + ")");
            hudText.setPosition(75.f, y + 125.f);
            window.draw(hudText);
            // orientation
            hudText.setString("Orientation: " + orientation[static_cast<int>(currentTrantorian.orientation)]);
            hudText.setPosition(50.f, y + 150.f);
            window.draw(hudText);
            // inventory
            hudText.setString("Inventory:");
            hudText.setPosition(50.f, y + 175.f);
            window.draw(hudText);
            y += 200.f;
            for (int i = 0; i < 7; i++) {
                hudText.setString(nameResources[i] + std::to_string(currentTrantorian.inventory[i]));
                hudText.setFillColor(colorResources[i]);
                hudText.setPosition(75.f, y);
                window.draw(hudText);
                y += 25.f;
            }
        }
    }

    void Hud::displayInfoTile(std::unordered_map<int, std::array<int, 7>> _resourcesOnTiles,
        std::pair<int, int> currentTile, int map_size_y, sf::RenderWindow &window)
    {
        if (_resourcesOnTiles.find(currentTile.first * map_size_y + currentTile.second) != _resourcesOnTiles.end()) {
            hudText.setFillColor(sf::Color {255, 255, 255});
            float x = window.getSize().x / 2 - 75;
            hudText.setString("Content of the selected tile:");
            hudText.setPosition(x, 100);
            window.draw(hudText);
            hudText.setString("x: " + std::to_string(currentTile.first));
            hudText.setPosition(x + 25, 125);
            window.draw(hudText);
            hudText.setString("y: " + std::to_string(currentTile.second));
            hudText.setPosition(x + 25, 150);
            window.draw(hudText);
            float y = 175.f;
            for (int i = 0; i < 7; i++) {
                hudText.setString(nameResources[i] + std::to_string(_resourcesOnTiles[currentTile.first * map_size_y + currentTile.second][i]));
                hudText.setFillColor(colorResources[i]);
                hudText.setPosition(x + 25, y);
                window.draw(hudText);
                y += 25.f;
            }
        }
    }

    void Hud::displayMenu(sf::RectangleShape escapeMenuBg, sf::RenderWindow &window)
    {
        window.draw(escapeMenuBg);

        sf::Vector2f menuPos = escapeMenuBg.getPosition();
        
        hudText.setString("PAUSE");
        hudText.setFillColor(sf::Color::White);
        hudText.setCharacterSize(30);
        hudText.setPosition(menuPos.x + 250.f, menuPos.y + 20.f);
        window.draw(hudText);
        hudText.setCharacterSize(20);

        hudText.setString("CAMERA :");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 100.f);
        window.draw(hudText);
        hudText.setString("A : horizontal rotation - left");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 150.f);
        window.draw(hudText);
        hudText.setString("E : horizontal rotation - right");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 170.f);
        window.draw(hudText);
        hudText.setString("R : vertical rotation - down");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 190.f);
        window.draw(hudText);
        hudText.setString("F : vertical rotation - up");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 210.f);
        window.draw(hudText);
        hudText.setString("LSHIFT : vertical translation - down");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 230.f);
        window.draw(hudText);
        hudText.setString("SPACE : vertical translation - up");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 250.f);
        window.draw(hudText);
        hudText.setString("Arrow up : horizontal translation - forward");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 270.f);
        window.draw(hudText);
        hudText.setString("Arrow down : horizontal translation - rearward");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 290.f);
        window.draw(hudText);
        hudText.setString("Arrow left : horizontal translation - left");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 310.f);
        window.draw(hudText);
        hudText.setString("Arrow right : horizontal translation - right");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 330.f);
        window.draw(hudText);
        hudText.setString("GAME");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 370.f);
        window.draw(hudText);
        hudText.setString("Tab : informations");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 400.f);
        window.draw(hudText);
        hudText.setString("ZQSD : select a tile to see what it contains");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 420.f);
        window.draw(hudText);
        hudText.setString("Note : You can press the grey button in the information menu");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 450.f);
        window.draw(hudText);
        hudText.setString("in order to display informations about the next Trantorian");
        hudText.setPosition(menuPos.x + 50.f, menuPos.y + 470.f);
        window.draw(hudText);
        // reset the size of the text
        hudText.setCharacterSize(16);
    }

    void Hud::displayFps(int lastFps, sf::RenderWindow &window)
    {
        hudText.setFillColor(sf::Color {255, 255, 255});
        hudText.setString("FPS: " + std::to_string(lastFps));
        hudText.setPosition(5.f, 5.f);
        window.draw(hudText);
    }

    void Hud::displayHistInstruc(std::deque<std::tuple<std::string, sf::Color>> histInstruc, sf::RenderWindow &window)
    {
        float y = 200.f;
        for (auto it = histInstruc.rbegin(); it != histInstruc.rend(); ++it) {
            const std::string& text = std::get<0>(*it);
            const sf::Color& color = std::get<1>(*it);

            hudText.setString(text);
            hudText.setFillColor(color);
            hudText.setPosition(window.getSize().x - 300, y);
            window.draw(hudText);
            y += 25.f;
        }
    }

    void Hud::displayTotalResources(std::array<int, 7> totalResources, sf::RenderWindow &window)
    {
        float y = 10.f;
        for (int i = 0; i < 7; i++) {
            hudText.setString(nameResources[i] + std::to_string(totalResources[i]));
            hudText.setFillColor(colorResources[i]);
            hudText.setPosition(window.getSize().x - 300, y);
            window.draw(hudText);
            y += 25.f;
        }
    }

} // namespace Renderer