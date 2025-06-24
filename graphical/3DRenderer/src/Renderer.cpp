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
    bool tabToggle = false;
    bool tabWasPressed = false;
    static sf::RectangleShape bgMenu;

    bool initRenderer(sf::RenderWindow &window) {
        // window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        if (!window.isOpen()) return false;

        window.setVerticalSyncEnabled(true);
        backBuffer.create(window.getSize().x, window.getSize().y);
        depthBuffer.assign(window.getSize().x * window.getSize().y, std::numeric_limits<float>::max());
        backBufferTexture.create(window.getSize().x, window.getSize().y);

        if (!hudFont.loadFromFile("./Assets/Roboto/Roboto-VariableFont_wdth,wght.ttf")) {
            std::cerr << "Failed to load font\n";
            return false;
        }
        hudText.setFont(hudFont);
        hudText.setCharacterSize(16);
        hudText.setFillColor(sf::Color::White);
        hudText.setOutlineColor(sf::Color::Black);
        hudText.setOutlineThickness(1.0f);

        bgMenu.setSize(sf::Vector2f(350.f, window.getSize().y));
        bgMenu.setPosition(window.getSize().x - 350.f, 0.f);
        bgMenu.setFillColor(sf::Color(0, 0, 0, 128));
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
    //A function useful for update
    Vec3 rotateY(const Vec3& v, float angleDegrees)
    {
        float angleRad = angleDegrees * (3.14159265f / 180.f);
        float cosA = std::cos(angleRad);
        float sinA = std::sin(angleRad);

        return {
            v.x * cosA - v.z * sinA,
            v.y,
            v.x * sinA + v.z * cosA
        };
    }

    void update(float dt) {
        processInput(dt);
        cooldownAction -= dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            if (!tabWasPressed) {
                tabToggle = !tabToggle;
                tabWasPressed = true;
            }
        } else {
            tabWasPressed = false;
        }

        // Values in valuesForSynchro :
        // int -> client id
        // Vec3 -> body position
        // Vec3 -> body rotation on the y axis
        std::vector<std::tuple<int, Vec3, Vec3>> valuesForSynchro;

        for (auto& e : sceneEntities) {
            Vec3 offset = {0.f, OFFSET_EYES_Y, Renderer::offsetEyesZ[e.level - 1]};
            auto itMove = activeMovements.find(e.clientId);
            if (itMove != activeMovements.end() && itMove->second.active) {
                MovementState& m = itMove->second;
                m.timeElapsed += dt;
                // X axis wrap
                if (e.position.x < -35.f) {
                    e.position.x = (map_size_x - 1) * TILE_SIZE + 35.f + (35.f + e.position.x);
                } else if (e.position.x > (map_size_x - 1) * TILE_SIZE + 35.f) {
                    e.position.x = (map_size_x - 1) * TILE_SIZE - e.position.x;
                }

                // Z axis wrap
                if (e.position.z < -35.f) {
                    e.position.z = (map_size_y - 1) * TILE_SIZE + 35.f + (35.f + e.position.z);
                } else if (e.position.z > (map_size_y - 1) * TILE_SIZE + 35.f) {
                    e.position.z = (map_size_y - 1) * TILE_SIZE - e.position.z;
                }
                while (m.stepsRemaining > 0 && m.timeElapsed >= 0.025f) {
                    m.timeElapsed -= 0.025f;

                    // Appliquer un déplacement de 5.5 dans la bonne direction
                    e.position.x += m.direction.x;
                    e.position.y += m.direction.y;
                    e.position.z += m.direction.z;

                    m.stepsRemaining--;

                    if (m.stepsRemaining == 0)
                        m.active = false;
                }
            }
            auto itRot = activeRotations.find(e.clientId);
            if (itRot != activeRotations.end() && itRot->second.active) {
                RotationState& r = itRot->second;
                r.timeElapsed += dt;
                while (r.stepsRemaining > 0 && r.timeElapsed >= 0.025f) {
                    r.timeElapsed -= 0.025f;
                    if (r.goingRight) {
                        e.rotation.y -= 9.f;
                        r.totalRotated -= 9.f;
                    } else {
                        e.rotation.y += 9.f;
                        r.totalRotated += 9.f;
                    }
                    r.stepsRemaining--;

                    if (r.stepsRemaining == 0) {
                        r.active = false;
                        // Reset if more than 360° or less than 0°
                        if (e.rotation.y >= 360.f)
                            e.rotation.y -= 360.f;
                        else if (e.rotation.y < 0.f)
                            e.rotation.y += 360.f;
                    }
                }
            }
            // Fin de rotation -> on démarre le mouvement
            for (auto it = Renderer::activeRotations.begin(); it != Renderer::activeRotations.end(); ++it) {
                int clientId = it->first;
                if (!it->second.active && pendingMovementsAfterRotation.contains(clientId)) {
                    Renderer::activeMovements[clientId] = pendingMovementsAfterRotation[clientId];
                    pendingMovementsAfterRotation.erase(clientId);
                }
            }
            if (e.type == Renderer::PartType::BODY) {
                valuesForSynchro.emplace_back(e.clientId, e.position, Vec3{0.f, e.rotation.y, 0.f});
            }
            if (e.type == Renderer::PartType::EYES) {
                // Searching for the corresponding body
                auto it = std::find_if(
                    valuesForSynchro.begin(), valuesForSynchro.end(),
                    [&e](const std::tuple<int, Vec3, Vec3>& t) {
                        return std::get<0>(t) == e.clientId;
                    });

                if (it != valuesForSynchro.end()) {
                    Vec3 bodyPos = std::get<1>(*it);
                    float bodyRotY = std::get<2>(*it).y;
                    Vec3 rotatedOffset = rotateY(offset, bodyRotY);
                    e.position = {
                        bodyPos.x + rotatedOffset.x,
                        bodyPos.y + rotatedOffset.y,
                        bodyPos.z + rotatedOffset.z
                    };
                    e.rotation.y = bodyRotY;
                }
            }
            if (e.type == Renderer::PartType::RING) {
                e.rotation.y += 20.0f * dt;
                if (e.rotation.y >= 360.f)
                    e.rotation.y -= 360.f;
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
        while (histInstruc.size() > 20)
            histInstruc.pop_front();
    }

    void render(float dt, sf::RenderWindow &window) {
        int w = window.getSize().x;
        int h = window.getSize().y;

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
        hudText.setString("FPS: " + std::to_string(lastFps));
        hudText.setPosition(5.f, 5.f);
        window.draw(hudText);

        float y = 30.f;
        for (const auto& m : hudMessages) {
            hudText.setString(m.text);
            hudText.setPosition(5.f, y);
            window.draw(hudText);
            y += 20.f;
        }

        if (tabToggle) {
            window.draw(bgMenu);
            float y = 100.f;
            for (auto it = histInstruc.rbegin(); it != histInstruc.rend(); ++it) {
                hudText.setString(*it);
                hudText.setPosition(window.getSize().x - 300, y);
                window.draw(hudText);
                y += 40.f;
            }
        }

        // window.display();
    }

    // bool getIsRunning() {
    //     sf::Event event;

    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             return false;
    //     }
    //     return window && window.isOpen();
    // }

    // void shutdownRenderer() {
    //     if (window) {
    //         window.close();
    //         delete window;
    //         window = nullptr;
    //     }
    // }

} // namespace Renderer
