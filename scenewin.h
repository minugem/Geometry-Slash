#pragma once

#include <string>
#include <vector>
#include "scene.h"
#include "sprite.h"

class Renderer;

class SceneWin : public Scene
{
public:
    SceneWin();
    ~SceneWin();

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);
    void DebugDraw();
    void SyncCurrentScene(int*, std::vector<Scene*>*);

private:
    Sprite* m_pBackground = nullptr;
    Sprite* m_pWinScreen = nullptr;

};
