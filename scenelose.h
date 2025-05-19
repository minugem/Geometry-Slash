#pragma once

#include <vector>
#include "scene.h"
#include "sprite.h"
class InputSystem;

class Renderer;

class SceneLose : public Scene
{
public:
    SceneLose();
    ~SceneLose();

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);
    void DebugDraw();
    void SyncCurrentScene(int*, std::vector<Scene*>*);

private:
    Sprite* m_pBackground = nullptr;
    Sprite* m_pLoseScreen = nullptr;
    InputSystem* m_pInputSystem = nullptr;
};
