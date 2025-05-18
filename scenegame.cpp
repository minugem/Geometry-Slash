// COMP710 GP Framework 2025

// This include:
#include "scenegame.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inputsystem.h"
#include "game.h" 

// Library includes:
#include <cassert>

SceneGame::SceneGame()
    : m_pCheckerboard(0)
    , m_pPlayer(0) 
    , m_pInputSystem(0) 
    , m_quitRequested(false) // Initialize

{
}

SceneGame::~SceneGame()
{
    delete m_pCheckerboard;
    m_pCheckerboard = 0;
    delete m_pPlayer; // Clean up
    m_pPlayer = 0;
    delete m_pInputSystem; // Clean up
    m_pInputSystem = 0;
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

    m_pInputSystem = new InputSystem();
    m_pInputSystem->Initialise();

    return true;
}


void SceneGame::Process(float deltaTime)
{
    // Quit on Q key press
    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_Q) == BS_PRESSED)
    {
        Game::GetInstance().Quit();
        return; // Optionally return early
    }

    float moveSpeed = 250.0f;
    float dx = 0.0f, dy = 0.0f;

    // WASD movement
    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_W) == BS_PRESSED)
        dy -= moveSpeed * deltaTime;
    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_S) == BS_PRESSED)
        dy += moveSpeed * deltaTime;
    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_A) == BS_PRESSED)
        dx -= moveSpeed * deltaTime;
    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_D) == BS_PRESSED)
        dx += moveSpeed * deltaTime;

    if (m_pPlayer)
    {
        m_pPlayer->SetX(m_pPlayer->GetX() + dx);
        m_pPlayer->SetY(m_pPlayer->GetY() + dy);

        m_pPlayer->Process(deltaTime);
    }
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
