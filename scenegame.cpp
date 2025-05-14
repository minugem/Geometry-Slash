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
    , m_pPlayer(0) // Initialize pointer
{
}

SceneGame::~SceneGame()
{
    delete m_pCheckerboard;
    m_pCheckerboard = 0;
    delete m_pPlayer; // Clean up
    m_pPlayer = 0;
}


bool SceneGame::Initialise(Renderer& renderer)
{
    int screenWidth = renderer.GetWidth();
    int screenHeight = renderer.GetHeight();

    m_pCheckerboard = renderer.CreateSprite("..\\assets\\background.png");
    if (m_pCheckerboard == 0)
    {
        return false;
    }

    // Tile background code here...

    // Create and initialize player
    m_pPlayer = new Player();
    if (!m_pPlayer->Initialise(renderer))
    {
        return false;
    }

    // Center the player
    int playerWidth = m_pPlayer->GetX(); // This should be GetWidth()
    int playerHeight = m_pPlayer->GetY(); // This should be GetHeight()
    int centerX = (screenWidth - m_pPlayer->GetWidth()) / 2;
    int centerY = (screenHeight - m_pPlayer->GetHeight()) / 2;
    m_pPlayer->SetX(centerX);
    m_pPlayer->SetY(centerY);

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
        int screenWidth = renderer.GetWidth();
        int screenHeight = renderer.GetHeight();
        int tileWidth = m_pCheckerboard->GetWidth();
        int tileHeight = m_pCheckerboard->GetHeight();

        for (int y = 0; y < screenHeight; y += tileHeight)
        {
            for (int x = 0; x < screenWidth; x += tileWidth)
            {
                m_pCheckerboard->SetX(x);
                m_pCheckerboard->SetY(y);
                m_pCheckerboard->Draw(renderer);
            }
        }
    }

    if (m_pPlayer)
    {
        m_pPlayer->Draw(renderer);
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
