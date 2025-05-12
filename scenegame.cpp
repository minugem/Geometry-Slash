// COMP710 GP Framework 2025

// This include:
#include "scenegame.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"

// Library includes:
#include <cassert>

SceneGame::SceneGame()
    : m_pCheckerboard(0)
{
}

SceneGame::~SceneGame()
{
    delete m_pCheckerboard;
    m_pCheckerboard = 0;
}

bool SceneGame::Initialise(Renderer& renderer)
{
    int screenWidth = renderer.GetWidth();
    int screenHeight = renderer.GetHeight();

    m_pCheckerboard = renderer.CreateSprite("..\\assets\\board8x8.png");
    if (m_pCheckerboard == 0)
    {
        return false;
    }

    // Center the checkerboard
    m_pCheckerboard->SetX(screenWidth / 2);
    m_pCheckerboard->SetY(screenHeight / 2);

    // Optionally scale to fit the screen (remove or adjust as needed)
    // float scale = std::min(
    //     static_cast<float>(screenWidth) / m_pCheckerboard->GetWidth(),
    //     static_cast<float>(screenHeight) / m_pCheckerboard->GetHeight()
    // );
    // m_pCheckerboard->SetScale(scale);

    return true;
}

void SceneGame::Process(float /*deltaTime*/)
{
    // Static background: nothing to update
}

void SceneGame::Draw(Renderer& renderer)
{
    if (m_pCheckerboard)
    {
        m_pCheckerboard->Draw(renderer);
    }
}

void SceneGame::DebugDraw()
{
    // No debug controls for static background
}

void SceneGame::SyncCurrentScene(int* /*m_iCurrentScene*/, std::vector<Scene*>* /*m_scenes*/)
{
    // No scene switching logic for this simple scene
}
