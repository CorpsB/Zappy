// include/Renderer.hpp
#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Camera.hpp"
// #include "InputHandler.hpp"
#include "Entity.hpp"
#include "Clipper.hpp"
#include "Geometry.hpp"
#include "HUD.hpp"
#include "Math.hpp"
#include "Update.hpp"
#include <memory>

#define TILE_SIZE 70
#define OFFSET_EYES_Y -1.5f

namespace Renderer {
    // Initialisation et boucle
    class Renderer {
        public:
            bool initRenderer(sf::RenderWindow &window, std::shared_ptr<EntityClass> entity);
            void update(float dt, sf::RenderWindow &window);
            void render(float dt, sf::RenderWindow &window);

            inline void drawTriangle(const Vec4& p1, const Vec4& p2, const Vec4& p3, const sf::Color& color);

            std::unordered_map<int, MovementState> getActiveMovements() const;
            std::unordered_map<int, RotationState> getActiveRotations() const;
            std::unordered_map<int, MovementState> getPendingMovements() const;
            int getMapSizeX() const;
            int getMapSizeY() const;
            std::unordered_map<int, std::array<int, 7>> getResourcesOnTiles() const;
            bool getResourcesChange() const;

            void setActiveMovements(std::unordered_map<int, MovementState> activemovements);
            void setActiveRotations(std::unordered_map<int, RotationState> activerotations);
            void setPendingMovements(std::unordered_map<int, MovementState> pendingmovements);
            void setMapSizeX(int mapsizex);
            void setMapSizeY(int mapsizey);
            void setResourcesOnTiles(std::unordered_map<int, std::array<int, 7>> resourcesontiles);
            void setResourcesChange(bool resourceschange);

            void addToActiveMovements(int index, MovementState move);
            void addToActiveRotations(int index, RotationState rotation);
            void addToPendingMovements(int index, MovementState move);
            void addToResourcesOnTiles(int index, std::array<int, 7> resources);
            void addToHistInstruc(std::string instruc, sf::Color color);
        private:
        // Variables to be get and modified
            std::unordered_map<int, MovementState> activeMovements;
            std::unordered_map<int, RotationState> activeRotations;
            std::unordered_map<int, MovementState> pendingMovementsAfterRotation;
            int map_size_x = 0;
            int map_size_y = 0;
            // We need it to display it even though it's not really supposed to be here
            std::unordered_map<int, std::array<int, 7>> _resourcesOnTiles;
            bool resourcesChange;
            std::deque<std::tuple<std::string, sf::Color>> histInstruc;

        // "static" variables
            sf::Image backBuffer;
            sf::Texture backBufferTexture;
            sf::Sprite backBufferSprite;
            std::vector<float> depthBuffer;
            sf::Font hudFont;
            sf::Text hudText;
            float fpsTimer = 0.0f;
            int frameCount = 0;
            int lastFps = 0;
            float cooldownAction = 0.f;
            sf::RectangleShape bgMenu;
            std::array<int, 7> totalResources;
            std::array<sf::Color, 7> colorResources;
            std::array<std::string, 7> nameResources;
            sf::RectangleShape buttonNextTrantorian;
            sf::Color buttonIdleColor = sf::Color(100, 100, 100);
            sf::Color buttonHoverColor = sf::Color(150, 150, 150);
            Entity currentTrantorian;
            std::array<std::string, 4> orientation = {"NORTH", "WEST", "SOUTH", "EAST"};
            sf::RectangleShape escapeMenuBg;
            std::pair<int, int> currentTile;

            bool buttonToggle = false;
            bool buttonIsPressed = false;
            bool escapeMenuToggle = false;
            bool escapeWasPressed = false;
            bool zToggle = false;
            bool zWasPressed = false;
            bool sToggle = false;
            bool sWasPressed = false;
            bool qToggle = false;
            bool qWasPressed = false;
            bool dToggle = false;
            bool dWasPressed = false;
            bool tabToggle = false;
            bool tabWasPressed = false;

            Update _update;
            InputHandler _inputhandler;
            Camera _camera;
            Clipper _clipper;
            Hud _hud;
            std::shared_ptr<EntityClass> _entity;
    };
}
