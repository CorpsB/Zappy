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

    bool Renderer::initRenderer(sf::RenderWindow &window, std::shared_ptr<EntityClass> entity) {
        this->_entity = entity;
        if (!window.isOpen())
            return false;

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
        _hud.init(hudFont);
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

    inline void Renderer::drawTriangle(const Vec4& p1, const Vec4& p2, const Vec4& p3, const sf::Color& color) {
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

    void Renderer::update(float dt, sf::RenderWindow &window) {
        if (window.hasFocus()) {
            _camera.cameraMovement(dt);
            cooldownAction -= dt;
            _inputhandler.switchInput(tabToggle, tabWasPressed, sf::Keyboard::Tab);
            _inputhandler.switchInput(escapeMenuToggle, escapeWasPressed, sf::Keyboard::Escape);
            _inputhandler.switchInput(zToggle, zWasPressed, sf::Keyboard::Z);
            _inputhandler.switchInput(sToggle, sWasPressed, sf::Keyboard::S);
            _inputhandler.switchInput(qToggle, qWasPressed, sf::Keyboard::Q);
            _inputhandler.switchInput(dToggle, dWasPressed, sf::Keyboard::D);
            _update.changeSelectedTile(zToggle, sToggle, qToggle, dToggle, currentTile, map_size_x, map_size_y);
        }
        std::vector<std::tuple<int, Vec3, Vec3>> valuesForSynchro;

        for (auto& e : _entity.get()->getSceneEntities()) {
            _update.moveTrantorian(dt, e, activeMovements, map_size_x, map_size_y);
            _update.rotateTrantorian(dt, e, activeRotations);
            _update.startMoveAfterRotate(activeMovements, activeRotations, pendingMovementsAfterRotation);
            _update.sychroEyes(e, valuesForSynchro);
            _update.incantationRing(dt, e);
            if (e.type == PartType::EXPULSION) {
                if (e.orientation == Compass::EAST || e.orientation == Compass::WEST)
                    e.rotation.x += 60.0f * dt;
                else if (e.orientation == Compass::NORTH || e.orientation == Compass::SOUTH)
                    e.rotation.z += 60.0f * dt;
            }
        }
        for (auto it = _entity.get()->getSceneEntities().begin(); it != _entity.get()->getSceneEntities().end(); ) {
            Entity &e = *it;
            if (e.type == PartType::EXPULSION && e.rotation.x > static_cast<float>(360 * 5)) {
                it = _entity.get()->getSceneEntities().erase(it);
            } else if (e.type == PartType::EXPULSION && e.rotation.z > static_cast<float>(360 * 5)) {
                it = _entity.get()->getSceneEntities().erase(it);
            } else {
                ++it;
            }
        }
        while (histInstruc.size() > 21)
            histInstruc.pop_front();
    }

    void Renderer::render(float dt, sf::RenderWindow &window) {
        int w = window.getSize().x;
        int h = window.getSize().y;
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
        Mat4x4 matView = _camera.quickInverse(
            _camera.pointAt(
                _camera.getPosition(),
                { _camera.getPosition().x + static_cast<float>(std::sin(_camera.getYaw()   * M_PI / 180.0f)),
                  _camera.getPosition().y + static_cast<float>(std::sin(_camera.getPitch() * M_PI / 180.0f)),
                  _camera.getPosition().z + static_cast<float>(std::cos(_camera.getYaw()   * M_PI / 180.0f)) },
                { 0, 1, 0 }
            )
        );

        // direction de la lumiére
        Vec3 lightDir = { 0.8f, 0.8f, 0.8f };
        float l = std::sqrt(lightDir.x*lightDir.x + lightDir.y*lightDir.y + lightDir.z*lightDir.z);
        if (l > 0) lightDir = { lightDir.x/l, lightDir.y/l, lightDir.z/l };

        for (const auto& e : _entity.get()->getSceneEntities()) {
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
                int nClipped = _clipper.clipAgainstPlane({0,0,0.1f}, {0,0,1}, triViewed, clipped[0], clipped[1]);
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
        _hud.displayFps(lastFps, window);

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
            _hud.displayTotalResources(totalResources, window);
            _hud.displayHistInstruc(histInstruc, window);
            if (currentTrantorian.clientId == -1) {
                for (auto &e : _entity.get()->getSceneEntities()) {
                    if (e.type == PartType::BODY) {
                        currentTrantorian = e;
                        break;
                    }
                }
            } else if (buttonToggle) {
                bool wasItTheTrantorian = false;
                for (auto &e : _entity.get()->getSceneEntities()) {
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
                    for (auto &e : _entity.get()->getSceneEntities()) {
                        if (e.type == PartType::BODY) {
                            currentTrantorian = e;
                            break;
                        }
                    }
                }
            }
            // Actualizes informations
            for (auto &e : _entity.get()->getSceneEntities()) {
                if (e.clientId == currentTrantorian.clientId) {
                    currentTrantorian = e;
                    break;
                }
            }
            // condition just in case there is no Trantorian yet
            _hud.displayInfoTrantorian(currentTrantorian, window);
            _hud.displayInfoTile(_resourcesOnTiles, currentTile, map_size_y, window);
        }

        if (escapeMenuToggle) {
            _hud.displayMenu(escapeMenuBg, window);
        }
    }

    std::unordered_map<int, MovementState> Renderer::getActiveMovements() const
    {
        return this->activeMovements;
    }

    std::unordered_map<int, RotationState> Renderer::getActiveRotations() const
    {
        return this->activeRotations;
    }

    std::unordered_map<int, MovementState> Renderer::getPendingMovements() const
    {
        return this->pendingMovementsAfterRotation;
    }

    int Renderer::getMapSizeX() const
    {
        return this->map_size_x;
    }

    int Renderer::getMapSizeY() const
    {
        return this->map_size_y;
    }

    std::unordered_map<int, std::array<int, 7>> Renderer::getResourcesOnTiles() const
    {
        return this->_resourcesOnTiles;
    }

    bool Renderer::getResourcesChange() const
    {
        return this->resourcesChange;
    }

    void Renderer::setActiveMovements(std::unordered_map<int, MovementState> activemovements)
    {
        this->activeMovements = activemovements;
    }

    void Renderer::setActiveRotations(std::unordered_map<int, RotationState> activerotations)
    {
        this->activeRotations = activerotations;
    }

    void Renderer::setPendingMovements(std::unordered_map<int, MovementState> pendingmovements)
    {
        this->pendingMovementsAfterRotation = pendingmovements;
    }

    void Renderer::setMapSizeX(int mapsizex)
    {
        this->map_size_x = mapsizex;
    }

    void Renderer::setMapSizeY(int mapsizey)
    {
        this->map_size_y = mapsizey;
    }

    void Renderer::setResourcesOnTiles(std::unordered_map<int, std::array<int, 7>> resourcesontiles)
    {
        this->_resourcesOnTiles = resourcesontiles;
    }

    void Renderer::setResourcesChange(bool resourceschange)
    {
        this->resourcesChange = resourceschange;
    }

    void Renderer::addToActiveMovements(int index, MovementState move)
    {
        this->activeMovements[index] = move;
    }

    void Renderer::addToActiveRotations(int index, RotationState rotation)
    {
        this->activeRotations[index] = rotation;
    }

    void Renderer::addToPendingMovements(int index, MovementState move)
    {
        this->pendingMovementsAfterRotation[index] = move;
    }

    void Renderer::addToResourcesOnTiles(int index, std::array<int, 7> resources)
    {
        this->_resourcesOnTiles[index] = resources;
    }

    void Renderer::addToHistInstruc(std::string instruc, sf::Color color)
    {
        this->histInstruc.emplace_back(instruc, color);
    }

} // namespace Renderer
