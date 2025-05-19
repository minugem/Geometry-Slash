#include "scenelose.h"
#include "renderer.h"
#include "sprite.h"
#include "game.h"
#include "inputsystem.h"
#include "scenegame.h"
SceneLose::SceneLose() {}

SceneLose::~SceneLose()
{
    delete m_pBackground;
    m_pBackground = nullptr;
    delete m_pLoseScreen;
    m_pLoseScreen = nullptr;

}



bool SceneLose::Initialise(Renderer& renderer)
{
    m_pBackground = renderer.CreateSprite("..\\assets\\background.png");
    m_pLoseScreen = renderer.CreateSprite("..\\assets\\losescreen.png");
    m_pInputSystem = new InputSystem();
    m_pInputSystem->Initialise();
    return (m_pBackground != nullptr) && (m_pLoseScreen != nullptr);
}



void SceneLose::Process(float /*deltaTime*/)
{
    if (!m_pInputSystem) return;

    // Quit
    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_Q) == BS_PRESSED)
    {
        Game::GetInstance().Quit();
    }

    // Restart SceneGame
    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_R) == BS_PRESSED)
    {
        // Assuming SceneGame is at index 1 in m_scenes
        int gameSceneIndex = 1;
        auto& scenes = Game::GetInstance().GetScenes();

        delete scenes[gameSceneIndex];
        SceneGame* newSceneGame = new SceneGame();
        newSceneGame->Initialise(*Game::GetInstance().GetRenderer());
        scenes[gameSceneIndex] = newSceneGame;


        // Switch to SceneGame
        Game::GetInstance().m_iCurrentScene = gameSceneIndex;
    }
}

void SceneLose::DebugDraw() {}
void SceneLose::SyncCurrentScene(int*, std::vector<Scene*>*) {}

void SceneLose::Draw(Renderer& renderer)
{
    // Tile the background
    if (m_pBackground)
    {
        int screenWidth = renderer.GetWidth();
        int screenHeight = renderer.GetHeight();
        int tileWidth = m_pBackground->GetWidth();
        int tileHeight = m_pBackground->GetHeight();

        for (int y = 0; y < screenHeight; y += tileHeight)
        {
            for (int x = 0; x < screenWidth; x += tileWidth)
            {
                m_pBackground->SetX(x);
                m_pBackground->SetY(y);
                m_pBackground->Draw(renderer);
            }
        }
    }
    // Draw the lose screen sprite centered (origin is center)
    if (m_pLoseScreen)
    {
        int screenWidth = renderer.GetWidth();
        int screenHeight = renderer.GetHeight();
        int centerX = screenWidth / 2;
        int centerY = screenHeight / 2;
        m_pLoseScreen->SetX(centerX);
        m_pLoseScreen->SetY(centerY);
        m_pLoseScreen->Draw(renderer);
    }
}
