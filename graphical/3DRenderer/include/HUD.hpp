// include/HUD.hpp
#pragma once
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Math.hpp"
#include <queue>
#include "Entity.hpp"

namespace Renderer {
    class Hud {
        public:
            Hud();
            ~Hud() = default;
            void init(sf::Font &hudFont);
            void displayInfoTrantorian(Entity currentTrantorian, sf::RenderWindow &window);
            void displayInfoTile(std::unordered_map<int, std::array<int, 7>> _resourcesOnTiles,
                std::pair<int, int> currentTile, int map_size_y, sf::RenderWindow &window);
            void displayMenu(sf::RectangleShape escapeMenuBg, sf::RenderWindow &window);
            void displayFps(int lastFps, sf::RenderWindow &window);
            void displayHistInstruc(std::deque<std::tuple<std::string, sf::Color>> histInstruc, sf::RenderWindow &window);
            void displayTotalResources(std::array<int, 7> totalResources, sf::RenderWindow &window);
        private:
            std::array<std::string, 4> orientation;
            sf::Text hudText;
            std::array<sf::Color, 7> colorResources;
            std::array<std::string, 7> nameResources;
            sf::RenderWindow window;
    };
}
