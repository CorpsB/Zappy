/*
** EPITECH PROJECT, 2025
** B-YEP-400-STG-4-1-zappy-noe.carabin
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>

namespace Renderer {

    // static sf::RenderWindow window;
    static sf::Image backBuffer;
    static sf::Texture backBufferTexture;
    static sf::Sprite backBufferSprite;
    static std::vector<float> depthBuffer;
    static sf::Font hudFont;
    static sf::Text hudText;
    static float fpsTimer = 0.0f;
    static int frameCount = 0;
    static int lastFps = 0;
    static float cooldownAction = 0.f;
    std::unordered_map<int, MovementState> activeMovements;
    std::unordered_map<int, RotationState> activeRotations;
    std::unordered_map<int, Renderer::MovementState> pendingMovementsAfterRotation;
    int map_size_x = 0;
    int map_size_y = 0;
    static sf::RectangleShape bgMenu;
    // We need it to display it even though it's not really supposed to be here
    std::unordered_map<int, std::array<int, 7>> _resourcesOnTiles;
    static std::array<int, 7> totalResources;
    static std::array<sf::Color, 7> colorResources;
    static std::array<std::string, 7> nameResources;
    bool resourcesChange;
    static sf::RectangleShape buttonNextTrantorian;
    static sf::Color buttonIdleColor = sf::Color(100, 100, 100);
    static sf::Color buttonHoverColor = sf::Color(150, 150, 150);
    static Entity currentTrantorian;
    static std::array<std::string, 4> orientation = {"NORTH", "WEST", "SOUTH", "EAST"};
    static sf::RectangleShape escapeMenuBg;
    static std::pair<int, int> currentTile;
    Update _update;

    bool initRenderer(sf::RenderWindow &window) {
        // window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        if (!window.isOpen()) return false;

        window.setVerticalSyncEnabled(true);
        backBuffer.create(window.getSize().x, window.getSize().y);
        depthBuffer.assign(window.getSize().x * window.getSize().y, std::numeric_limits<float>::max());
        backBufferTexture.create(window.getSize().x, window.getSize().y);
        escapeMenuBg.setSize(sf::Vector2f(600.f, 500.f));
        escapeMenuBg.setFillColor(sf::Color(20, 20, 20, 220));
        escapeMenuBg.setOutlineColor(sf::Color::White);
        escapeMenuBg.setOutlineThickness(2.f);
        escapeMenuBg.setPosition(
            (window.getSize().x - escapeMenuBg.getSize().x) / 2.f,
            (window.getSize().y - escapeMenuBg.getSize().y) / 2.f
        );

        if (!hudFont.loadFromFile("./bonus/Assets/zappy_font.ttf")) {
            std::cerr << "Failed to load font\n";
            return false;
        }
        hudText.setFont(hudFont);
        hudText.setCharacterSize(16);
        hudText.setFillColor(sf::Color::White);
        hudText.setOutlineColor(sf::Color::Black);
        hudText.setOutlineThickness(1.0f);

        bgMenu.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
        bgMenu.setPosition(0.f, 0.f);
        bgMenu.setFillColor(sf::Color(0, 0, 0, 128));
        buttonNextTrantorian.setSize(sf::Vector2f(100.f, 40.f));
        buttonNextTrantorian.setPosition(120.f, 550.f);
        buttonNextTrantorian.setFillColor(buttonIdleColor);

        totalResources = {0, 0, 0, 0, 0, 0, 0};

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
        resourcesChange = true;
        
        currentTrantorian.clientId = -1;

        currentTile = {0, 0};

        return true;
    }

    inline void drawTriangle(const Vec4& p1, const Vec4& p2, const Vec4& p3, const sf::Color& color) {
        const unsigned int screenW = backBuffer.getSize().x;
        const unsigned int screenH = backBuffer.getSize().y;

        Vec4 v1 = p1, v2 = p2, v3 = p3;
        if (v2.y < v1.y) std::swap(v1, v2);
        if (v3.y < v1.y) std::swap(v1, v3);
        if (v3.y < v2.y) std::swap(v2, v3);

        int minX = std::max(0, int(std::min({ v1.x, v2.x, v3.x })));
        int maxX = std::min(int(screenW - 1), int(std::ceil (std::max({ v1.x, v2.x, v3.x }))));
        int minY = std::max(0, int(v1.y));
        int maxY = std::min(int(screenH - 1), int(std::ceil(v3.y)));

        float area = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
        if (std::abs(area) < 1e-6f) return;

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                float w1 = ((v2.y - v3.y) * (x - v3.x) + (v3.x - v2.x) * (y - v3.y)) / area;
                float w2 = ((v3.y - v1.y) * (x - v3.x) + (v1.x - v3.x) * (y - v3.y)) / area;
                float w3 = 1.0f - w1 - w2;

                if (w1 >= 0 && w2 >= 0 && w3 >= 0) {
                    float zInv = w1 * v1.w + w2 * v2.w + w3 * v3.w;
                    if (zInv == 0.0f) continue;
                    float z = 1.0f / zInv;

                    size_t idx = size_t(y) * screenW + x;
                    if (z < depthBuffer[idx]) {
                        depthBuffer[idx] = z;
                        backBuffer.setPixel(x, y, color);
                    }
                }
            }
        }
    }

    void update(float dt) {
        processInput(dt);
        cooldownAction -= dt;
        if (zToggle) {
            if (currentTile.first < map_size_x - 1)
                currentTile.first += 1;
            zToggle = false;
        }
        if (sToggle) {
            if (currentTile.first > 0)
                currentTile.first -= 1;
            sToggle = false;
        }
        if (qToggle) {
            if (currentTile.second < map_size_y - 1)
                currentTile.second += 1;
            qToggle = false;
        }
        if (dToggle) {
            if (currentTile.second > 0)
                currentTile.second -= 1;
            dToggle = false;
        }
        // Values in valuesForSynchro :
        // int -> client id
        // Vec3 -> body position
        // Vec3 -> body rotation on the y axis
        std::vector<std::tuple<int, Vec3, Vec3>> valuesForSynchro;

        for (auto& e : sceneEntities) {
            _update.moveTrantorian(dt, e, activeMovements);
            _update.rotateTrantorian(dt, e, activeRotations);
            _update.startMoveAfterRotate(activeMovements, activeRotations, pendingMovementsAfterRotation);
            _update.sychroEyes(e, valuesForSynchro);
            _update.incantationRing(dt, e);
            if (e.type == Renderer::PartType::EXPULSION) {
                if (e.orientation == Compass::EAST || e.orientation == Compass::WEST)
                    e.rotation.x += 60.0f * dt;
                else if (e.orientation == Compass::NORTH || e.orientation == Compass::SOUTH)
                    e.rotation.z += 60.0f * dt;
            }

            // if (e.type == PartType::GROUND) {
            //     if (static_cast<int>(e.position.x) == currentTile.first * TILE_SIZE
            //         && static_cast<int>(e.position.z) == currentTile.second * TILE_SIZE) {
            //         e.color = sf::Color::Red;
            //     } else
            //         e.color = sf::Color {65, 65, 65};
            // }
        }
        // erase expulsion after 5 rotations
        for (auto it = Renderer::sceneEntities.begin(); it != Renderer::sceneEntities.end(); ) {
            Renderer::Entity &e = *it;
            if (e.type == Renderer::PartType::EXPULSION && e.rotation.x > static_cast<float>(360 * 5)) {
                it = Renderer::sceneEntities.erase(it);
            } else if (e.type == Renderer::PartType::EXPULSION && e.rotation.z > static_cast<float>(360 * 5)) {
                it = Renderer::sceneEntities.erase(it);
            } else {
                ++it;
            }
        }
        // HUD message à timer
        for (auto it = hudMessages.begin(); it != hudMessages.end();) {
            it->remainingTime -= dt;
            if (it->remainingTime <= 0.0f)
                it = hudMessages.erase(it);
            else
                ++it;
        }
        // Remove old messages
        while (histInstruc.size() > 21)
            histInstruc.pop_front();
    }

    void render(float dt, sf::RenderWindow &window) {
        int w = window.getSize().x;
        int h = window.getSize().y;
        // static bool isButtonClicked = false;
        // static sf::Clock clickClock;
        // sf::Time clickDuration = sf::seconds(1.f);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        //Bottom left button
        if (buttonNextTrantorian.getGlobalBounds().contains(mousePosF)) {
            buttonNextTrantorian.setFillColor(buttonHoverColor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!buttonToggle && !buttonIsPressed) {
                    buttonToggle = true;
                } else
                    buttonToggle = false;
                buttonIsPressed = true;
            } else {
                buttonIsPressed = false;
                buttonToggle = false;
            }
        } else {
            buttonNextTrantorian.setFillColor(buttonIdleColor);
        }
        // Gradient ciel
        for (int y = 0; y < h; ++y) {
            float t = float(y) / float(h);
            sf::Color c(
                static_cast<sf::Uint8>((1 - t) * 60  + t * 120),
                static_cast<sf::Uint8>((1 - t) * 120 + t * 160),
                static_cast<sf::Uint8>((1 - t) * 220 + t * 240)
            );
            for (int x = 0; x < w; ++x)
                backBuffer.setPixel(x, y, c);
        }

        std::fill(depthBuffer.begin(), depthBuffer.end(), std::numeric_limits<float>::max());

        Mat4x4 matProj = Mat4x4::makeProjection(90.0f, float(w) / float(h), 0.1f, 1000.0f);
        Mat4x4 matView = quickInverse(
            pointAt(
                cameraPosition,
                { cameraPosition.x + static_cast<float>(std::sin(cameraYaw   * M_PI / 180.0f)),
                  cameraPosition.y + static_cast<float>(std::sin(cameraPitch * M_PI / 180.0f)),
                  cameraPosition.z + static_cast<float>(std::cos(cameraYaw   * M_PI / 180.0f)) },
                { 0, 1, 0 }
            )
        );

        // direction de la lumiére
        Vec3 lightDir = { 0.8f, 0.8f, 0.8f };
        float l = std::sqrt(lightDir.x*lightDir.x + lightDir.y*lightDir.y + lightDir.z*lightDir.z);
        if (l > 0) lightDir = { lightDir.x/l, lightDir.y/l, lightDir.z/l };

        for (const auto& e : sceneEntities) {
            Mat4x4 matScale = Mat4x4::makeScale(e.scale.x, e.scale.y, e.scale.z);
            Mat4x4 matRotX  = Mat4x4::makeRotationX(e.rotation.x * M_PI / 180.0f);
            Mat4x4 matRotY  = Mat4x4::makeRotationY(e.rotation.y * M_PI / 180.0f);
            Mat4x4 matRotZ  = Mat4x4::makeRotationZ(e.rotation.z * M_PI / 180.0f);
            Mat4x4 matTrans = Mat4x4::makeTranslation(e.position.x, e.position.y, e.position.z);

            Mat4x4 matWorld = multiplyMatrixMatrix(matScale, matRotZ);
            matWorld = multiplyMatrixMatrix(matWorld, matRotY);
            matWorld = multiplyMatrixMatrix(matWorld, matRotX);
            matWorld = multiplyMatrixMatrix(matWorld, matTrans);

            for (const auto& tri : e.mesh.tris) {
                Triangle triWorld, triViewed;
                for (int i = 0; i < 3; ++i) {
                    Vec4 v = { tri.p[i].x, tri.p[i].y, tri.p[i].z, 1.0f };

                    Vec4 vWorld = multiplyMatrixVector(v, matWorld);
                    triWorld.p[i] = { vWorld.x, vWorld.y, vWorld.z };

                    Vec4 vCam = multiplyMatrixVector({ vWorld.x, vWorld.y, vWorld.z, 1.0f }, matView);
                    triViewed.p[i] = { vCam.x, vCam.y, vCam.z };
                }

                //Culling
                Vec3 a = { triViewed.p[1].x - triViewed.p[0].x,
                           triViewed.p[1].y - triViewed.p[0].y,
                           triViewed.p[1].z - triViewed.p[0].z };
                Vec3 b = { triViewed.p[2].x - triViewed.p[0].x,
                           triViewed.p[2].y - triViewed.p[0].y,
                           triViewed.p[2].z - triViewed.p[0].z };
                Vec3 viewNormal = { a.y*b.z - a.z*b.y,
                                    a.z*b.x - a.x*b.z,
                                    a.x*b.y - a.y*b.x };

                if ( viewNormal.x * triViewed.p[0].x +
                     viewNormal.y * triViewed.p[0].y +
                     viewNormal.z * triViewed.p[0].z >= 0.0f )
                    continue;

                //Eclairage Lambert
                Vec3 wn = { a.y*b.z - a.z*b.y,
                            a.z*b.x - a.x*b.z,
                            a.x*b.y - a.y*b.x };
                float nl = std::sqrt(wn.x*wn.x + wn.y*wn.y + wn.z*wn.z);
                if (nl > 0.0f)
                  wn = { wn.x/nl, wn.y/nl, wn.z/nl };

                float dp = std::max(0.15f, - (wn.x*lightDir.x + wn.y*lightDir.y + wn.z*lightDir.z) );
                sf::Color finalColor(
                    static_cast<sf::Uint8>(tri.color.r * dp),
                    static_cast<sf::Uint8>(tri.color.g * dp),
                    static_cast<sf::Uint8>(tri.color.b * dp)
                );

                std::list<Triangle> trisToRaster;
                Triangle clipped[2];
                triViewed.color = finalColor;
                int nClipped = clipAgainstPlane({0,0,0.1f}, {0,0,1}, triViewed, clipped[0], clipped[1]);
                for (int i = 0; i < nClipped; ++i)
                    trisToRaster.push_back(clipped[i]);

                for (auto& t : trisToRaster) {
                    Vec4 proj[3];
                    for (int i = 0; i < 3; ++i) {
                        Vec4 v = { t.p[i].x, t.p[i].y, t.p[i].z, 1.0f };
                        proj[i] = multiplyMatrixVector(v, matProj);
                        if (proj[i].w != 0.0f) {
                            proj[i].w = 1.0f / proj[i].w;
                            proj[i].x *= proj[i].w;
                            proj[i].y *= proj[i].w;
                        }
                        proj[i].x = (proj[i].x + 1.0f) * 0.5f * float(w);
                        proj[i].y = (proj[i].y + 1.0f) * 0.5f * float(h);
                    }
                    drawTriangle(proj[0], proj[1], proj[2], t.color);
                }
            }
        }

        backBufferTexture.update(backBuffer);
        backBufferSprite.setTexture(backBufferTexture, true);
        // window.clear();
        window.draw(backBufferSprite);

        // HUD FPS et messages
        fpsTimer += dt;
        frameCount++;
        if (fpsTimer >= 0.5f) {
            lastFps = int(frameCount / fpsTimer);
            frameCount = 0;
            fpsTimer = 0.0f;
        }
        hudText.setFillColor(sf::Color {255, 255, 255});
        hudText.setString("FPS: " + std::to_string(lastFps));
        hudText.setPosition(5.f, 5.f);


        float y = 30.f;
        for (const auto& m : hudMessages) {
            hudText.setString(m.text);
            hudText.setPosition(5.f, y);
            window.draw(hudText);
            y += 20.f;
        }

        // display menu
        if (tabToggle) {
            bgMenu.setPosition(0.f, 0.f);
            window.draw(bgMenu);
            window.draw(hudText);
            window.draw(buttonNextTrantorian);
            // Calculate only if something changed
            if (resourcesChange) {
                for (int i = 0; i < 7; i++)
                    totalResources[i] = 0;
                // Calculate the total of resources
                for (int i = 0; i < map_size_x; i++) {
                    for (int j = 0; j < map_size_y; j++) {
                        if (_resourcesOnTiles.find(i * map_size_y + j) != _resourcesOnTiles.end()) {
                            const auto& tileResources = _resourcesOnTiles[i * map_size_y + j];
                            for (int resIndex = 0; resIndex < 7; ++resIndex)
                                totalResources[resIndex] += tileResources[resIndex];
                        }
                    }
                }
            }
            resourcesChange = false;
            float y = 10.f;
            for (int i = 0; i < 7; i++) {
                hudText.setString(nameResources[i] + std::to_string(totalResources[i]));
                hudText.setFillColor(colorResources[i]);
                hudText.setPosition(window.getSize().x - 300, y);
                window.draw(hudText);
                y += 25.f;
            }
            y = 200.f;
            for (auto it = histInstruc.rbegin(); it != histInstruc.rend(); ++it) {
                const std::string& text = std::get<0>(*it);
                const sf::Color& color = std::get<1>(*it);

                hudText.setString(text);
                hudText.setFillColor(color);
                hudText.setPosition(window.getSize().x - 300, y);
                window.draw(hudText);
                y += 25.f;
            }
            if (currentTrantorian.clientId == -1) {
                for (auto &e : sceneEntities) {
                    if (e.type == PartType::BODY) {
                        currentTrantorian = e;
                        break;
                    }
                }
            } else if (buttonToggle) {
                bool wasItTheTrantorian = false;
                for (auto &e : sceneEntities) {
                    if (e.clientId == currentTrantorian.clientId)
                        wasItTheTrantorian = true;
                    if (e.type == PartType::BODY && wasItTheTrantorian && e.clientId != currentTrantorian.clientId) {
                        currentTrantorian = e;
                        wasItTheTrantorian = false;
                        break;
                    }
                }
                // if we arrive at the end, take the first entity (with BODY)
                if (wasItTheTrantorian) {
                    for (auto &e : sceneEntities) {
                        if (e.type == PartType::BODY) {
                            currentTrantorian = e;
                            break;
                        }
                    }
                }
            }
            // Actualizes informations
            for (auto &e : sceneEntities) {
                if (e.clientId == currentTrantorian.clientId) {
                    currentTrantorian = e;
                    break;
                }
            }
            // condition just in case there is no Trantorian yet
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
            if (_resourcesOnTiles.find(currentTile.first * map_size_y + currentTile.second) != _resourcesOnTiles.end()) {
                hudText.setFillColor(sf::Color {255, 255, 255});
                float x = window.getSize().x / 2 - 75;
                hudText.setString("Content of the red tile:");
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

        if (escapeMenuToggle) {
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
    }

} // namespace Renderer
