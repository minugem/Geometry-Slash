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
#include <iostream>
#include "logmanager.h"

SceneGame::SceneGame()
    : m_pCheckerboard(0)
    , m_pPlayer(0) 
    , m_pInputSystem(0) 
    , m_quitRequested(false) 
    , m_pBullet(0)
    , m_pEnemy(0)
    , m_gameTimer(0.0f)
    , m_timerStarted(false)



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
    delete m_pBullet;
	m_pBullet = 0;
    delete m_pControls;
    m_pControls = 0;
    delete m_pEnemy;
    m_pEnemy = 0;
    if (m_pPewSound)
    {
        m_pPewSound->release();
        m_pPewSound = nullptr;
    }


}


bool SceneGame::Initialise(Renderer& renderer)
{

    SDL_ShowCursor(SDL_ENABLE);
    SDL_SetRelativeMouseMode(SDL_FALSE);
    int screenWidth = renderer.GetWidth();
    int screenHeight = renderer.GetHeight();
    m_gameTimer = 0.0f;

    m_pCheckerboard = renderer.CreateSprite("..\\assets\\background.png");
    if (m_pCheckerboard == 0)
    {
        return false;
    }

    m_pEnemy = new Enemy();
    if (!m_pEnemy->Initialise(renderer))
        return false;

    const int maxEnemyBullets = 100000;
    for (int i = 0; i < maxEnemyBullets; ++i)
    {
        EnemyBullet* eb = new EnemyBullet();
        if (!eb->Initialise(renderer))
            return false;
        eb->SetActive(false);
        m_enemyBullets.push_back(eb);
    }


    // Position enemy somewhere (e.g., center-top)
    m_pEnemy->SetPosition((screenWidth - m_pEnemy->GetWidth()) / 2, 100.0f);


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
    
    const int maxBullets = 10;
    for (int i = 0; i < maxBullets; ++i)
    {
        Bullet* bullet = new Bullet();
        if (!bullet->Initialise(renderer))
            return false;
        bullet->SetActive(false);
        m_bullets.push_back(bullet);
    }

    m_bulletCooldown = 0.15f; // 0.15 seconds between shots (decrease for faster fire)
    m_bulletTimer = 0.0f;


    m_pBullet = new Bullet();
    if (!m_pBullet->Initialise(renderer))
    {
        return false;
    }

    m_pControls = renderer.CreateSprite("..\\assets\\controls.png");
    if (m_pControls == 0)
    {
        return false;
    }
    m_controlsAlpha = 0.0f;     // Start fully transparent
    m_controlsTimer = 0.0f;     // Timer for how long it's been shown
    m_showControls = true;      // Show at start


    FMOD::Channel* testChannel = nullptr;
    m_pFmodSystem->playSound(m_pFmodSound1, 0, false, &testChannel);


    //FMOD
    if (FMOD::System_Create(&m_pFmodSystem) != FMOD_OK)
    {
        LogManager::GetInstance().Log("FMOD System failed to create!");
        std::cout << "FMOD System failed to create! (console edition)" << std::endl;
        return false;
    }

    if (m_pFmodSystem->init(512, FMOD_INIT_NORMAL, 0) != FMOD_OK)
    {
        LogManager::GetInstance().Log("FMOD System failed to create!");
        std::cout << "FMOD System failed to create! (console edition)" << std::endl;
        return false;
    }

    //FMOD Test
    m_pFmodSystem->createSound("..\\assets\\pew.wav", FMOD_DEFAULT, 0, &m_pFmodSound1);
    m_pFmodSound1->setMode(FMOD_LOOP_OFF);


    return true;
}


void SceneGame::Process(float deltaTime)
{

    float spawnX = m_pEnemy->GetX() ;
    float spawnY = m_pEnemy->GetY() ;
    float targetX = m_pPlayer->GetX();
    float targetY = m_pPlayer->GetY();
    int randomInt = rand() % 1080;
    float randomFloat = ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f;

    float prevGameTimer = m_gameTimer;

    // Advance timer
    if (m_timerStarted)
    {
        m_gameTimer += deltaTime;
    }


    // Enemy Projectiles
    if (prevGameTimer < 1.0f && m_gameTimer >= 1.0f)
    {
        SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 2.0f && m_gameTimer >= 2.0f)
    {
        SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 3.0f && m_gameTimer >= 3.0f)
    {
        SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 3.5f && m_gameTimer >= 3.5f)
    {
        SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 4.0f && m_gameTimer >= 4.0f)
    {
        SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 4.5f && m_gameTimer >= 4.5f)
    {
        SpawnEnemyBullet(0, 0, targetX, targetY, 300.0f);
        SpawnEnemyBullet(1080, 0, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 5.0f && m_gameTimer >= 5.0f)
    {
        SpawnEnemyBullet(0, 720, targetX, targetY, 300.0f);
        SpawnEnemyBullet(1080, 720, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 6.0f && m_gameTimer >= 6.0f)
    {
        SpawnEnemyBullet(540, 0, targetX, targetY, 300.0f);
        SpawnEnemyBullet(540, 720, targetX, targetY, 300.0f);
        SpawnEnemyBullet(0, 360, targetX, targetY, 300.0f);
        SpawnEnemyBullet(1080, 360, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 7.0f && m_gameTimer >= 7.0f)
    {
        SpawnEnemyBullet(540, 0, targetX, targetY, 300.0f);
        SpawnEnemyBullet(540, 720, targetX, targetY, 300.0f);
        SpawnEnemyBullet(0, 360, targetX, targetY, 300.0f);
        SpawnEnemyBullet(1080, 360, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 7.5f && m_gameTimer >= 7.5f)
    {
        SpawnEnemyBullet(0, 720, targetX, targetY, 300.0f);
        SpawnEnemyBullet(1080, 720, targetX, targetY, 300.0f);
        SpawnEnemyBullet(0, 0, targetX, targetY, 300.0f);
        SpawnEnemyBullet(1080, 0, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 8.0f && m_gameTimer >= 8.0f)
    {
        SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, 300.0f);
    }

    if (prevGameTimer < 8.5f && m_gameTimer >= 8.5f)
    {
        SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, 350.0f);
    }

    if (prevGameTimer < 9.0f && m_gameTimer >= 9.0f)
    {
        SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, 400.0f);
    }

    if (prevGameTimer < 9.5f && m_gameTimer >= 9.5f)
    {
        SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, 450.0f);
    }

    if (prevGameTimer < 10.0f && m_gameTimer >= 10.0f)
    {
        SpawnEnemyBullet(rand() % 1080, spawnY, targetX, targetY, 450.0f);
    }

    if (prevGameTimer < 10.5f && m_gameTimer >= 10.5f)
    {
        SpawnEnemyBullet(rand() % 1080, spawnY, targetX, targetY, 450.0f);
    }

    if (prevGameTimer < 11.0f && m_gameTimer >= 11.0f)
    {
        SpawnEnemyBullet(rand() % 1080, spawnY, targetX, targetY, 450.0f);
    }

    if (prevGameTimer < 11.5f && m_gameTimer >= 11.5f)
    {
        SpawnEnemyBullet(rand() % 1080, spawnY, targetX, targetY, 450.0f);
    }

    if (prevGameTimer < 12.0f && m_gameTimer >= 12.0f)
    {
        SpawnEnemyBullet(rand() % 1080, spawnY, targetX, targetY, 450.0f);
    }

	if (prevGameTimer < 12.5f && m_gameTimer >= 12.5f)
	{
		SpawnEnemyBullet(rand() % 1080, spawnY, targetX, targetY, 450.0f);
	}

	if (prevGameTimer < 13.0f && m_gameTimer >= 13.0f)
	{
		SpawnEnemyBullet(rand() % 1080, spawnY, targetX, targetY, 450.0f);
	}

    if (prevGameTimer < 13.5f && m_gameTimer >= 13.5f)
    {
        SpawnEnemyBullet(rand() % 1080, spawnY, targetX, targetY, 450.0f);

    }
        if (prevGameTimer < 13.5f && m_gameTimer >= 13.5f)
        {
            SpawnEnemyBullet(rand() % 1080, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
        }

        if (prevGameTimer < 13.5f && m_gameTimer >= 13.5f)
        {
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
        }

        if (prevGameTimer < 13.5f && m_gameTimer >= 13.5f)
        {
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
        }

        if (prevGameTimer < 15.0f && m_gameTimer >= 15.0f)
        {
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX)* (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX)* (500.0f - 100.0f) + 100.0f);

        }

        if (prevGameTimer < 16.5f && m_gameTimer >= 16.5f)
        {
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX)* (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX)* (500.0f - 100.0f) + 100.0f);
        }

        if (prevGameTimer < 18.0f && m_gameTimer >= 18.0f)
        {
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
            SpawnEnemyBullet(spawnX, spawnY, targetX, targetY, ((float)rand() / RAND_MAX) * (500.0f - 100.0f) + 100.0f);
        }

        if (prevGameTimer < 20.0f && m_gameTimer >= 20.0f)
        {
            SpawnEnemyBullet(targetX+300, targetY+300, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX+300, targetY-300, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX-300, targetY+300, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX-300, targetY-300, targetX, targetY, 300.0f);
        }

        if (prevGameTimer < 22.0f && m_gameTimer >= 22.0f)
        {
            SpawnEnemyBullet(targetX + 300, targetY + 300, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX + 300, targetY - 300, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX - 300, targetY + 300, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX - 300, targetY - 300, targetX, targetY, 300.0f);
        }

        if (prevGameTimer < 24.0f && m_gameTimer >= 24.0f)
        {
            SpawnEnemyBullet(targetX + 300, targetY + 300, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX + 300, targetY - 300, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX - 300, targetY + 300, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX - 300, targetY - 300, targetX, targetY, 300.0f);
        }

        if (prevGameTimer < 26.0f && m_gameTimer >= 26.0f)
        {
            SpawnEnemyBullet(targetX + 400, targetY, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX - 400, targetY, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX, targetY + 400, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX, targetY - 400, targetX, targetY, 300.0f);
        }

        if (prevGameTimer < 28.0f && m_gameTimer >= 28.0f)
        {
            SpawnEnemyBullet(targetX + 400, targetY, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX - 400, targetY, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX, targetY + 400, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX, targetY - 400, targetX, targetY, 300.0f);
        }

        if (prevGameTimer < 30.0f && m_gameTimer >= 30.0f)
        {
            SpawnEnemyBullet(targetX + 400, targetY, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX - 400, targetY, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX, targetY + 400, targetX, targetY, 300.0f);
            SpawnEnemyBullet(targetX, targetY - 400, targetX, targetY, 300.0f);
        }

        if (prevGameTimer < 31.0f && m_gameTimer >= 31.0f)
        {
			prevGameTimer = 0.0f;
			m_gameTimer = 0.0f;
        }

    




    float moveSpeed = 250.0f;
    float dx = 0.0f, dy = 0.0f;
    float rotateSpeed = 180.0f; // degrees per second
    m_pPlayer->SetAngle(0.0f);


    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_A) == BS_PRESSED)
    {
        m_pPlayer->SetAngle(-15.0f);
    }

    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_D) == BS_PRESSED)
    {
        m_pPlayer->SetAngle(15.0f);
    }


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

    m_bulletTimer -= deltaTime;

    if (m_pInputSystem->GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED && m_bulletTimer <= 0.0f)
    {


        m_pFmodSystem->playSound(m_pFmodSound1, 0, false, 0);
        // Find an inactive bullet
        for (auto bullet : m_bullets)
        {
            if (!bullet->IsActive())
            {
                float bulletX = m_pPlayer->GetX() + (m_pPlayer->GetWidth() - bullet->GetWidth()) / 2;
                float bulletY = m_pPlayer->GetY() - bullet->GetHeight();
                bullet->SetPosition(bulletX, bulletY);
                bullet->SetActive(true);
                m_bulletTimer = m_bulletCooldown; // Reset cooldown
                break; // Only fire one bullet per press
            }

        }
    }

    // Update all bullets
    for (auto bullet : m_bullets)
    {
        if (bullet->IsActive())
            bullet->Process(deltaTime);
    }

    if (m_pEnemy)
        m_pEnemy->Process(deltaTime);


    // Simple AABB collision
    if (m_pEnemy && m_pEnemy->GetHealth() > 0)
    {
        for (auto bullet : m_bullets)
        {
            if (bullet->IsActive())
            {
                float bx = bullet->GetX();
                float by = bullet->GetY();
                int bw = bullet->GetWidth();
                int bh = bullet->GetHeight();

                float ex = m_pEnemy->GetX();
                float ey = m_pEnemy->GetY();
                int ew = m_pEnemy->GetWidth();
                int eh = m_pEnemy->GetHeight();

                // Axis-Aligned Bounding Box (AABB) collision
                if (bx < ex + ew && bx + bw > ex &&
                    by < ey + eh && by + bh > ey)
                {
                    bullet->SetActive(false); // Bullet disappears
                    m_pEnemy->TakeDamage(1);  // Enemy loses 1 health
                    break; // Only one bullet can hit at a time
                }
            }
        }
    }

    if (m_pEnemy && m_pEnemy->GetHealth() <= 0)
    {
        // Deactivate all enemy bullets
        for (auto eb : m_enemyBullets)
        {
            eb->SetActive(false);
        }

        // Stop the timer
        m_timerStarted = false;

        // Switch to win scene (assuming it's at index 2)
        Game::GetInstance().m_iCurrentScene = 1;
    }





    if (m_showControls && m_pControls)
    {
        const float fadeInTime = 1.0f;    // seconds to fade in
        const float holdTime = 5.0f;      // seconds to stay fully visible
        const float fadeOutTime = 1.0f;   // seconds to fade out
        const float totalTime = fadeInTime + holdTime + fadeOutTime;

        m_controlsTimer += deltaTime;

        if (m_controlsTimer < fadeInTime)
        {
            // Fade in
            m_controlsAlpha = m_controlsTimer / fadeInTime;
        }
        else if (m_controlsTimer < fadeInTime + holdTime)
        {
            // Hold
            m_controlsAlpha = 1.0f;
        }
        else if (m_controlsTimer < totalTime)
        {
            // Fade out
            float t = (m_controlsTimer - fadeInTime - holdTime) / fadeOutTime;
            m_controlsAlpha = 1.0f - t;
        }
        else
        {
            // Done
            m_controlsAlpha = 0.0f;
            m_showControls = false;
            if (!m_timerStarted)
            {
                m_timerStarted = true;
                m_gameTimer = 0.0f; 
            }
        }
    }

    for (auto eb : m_enemyBullets)
    {
        if (eb->IsActive())
            eb->Process(deltaTime);
    }

    if (m_pPlayer && m_pPlayer->GetHealth() > 0)
    {
        float px = m_pPlayer->GetX();
        float py = m_pPlayer->GetY();
        int pw = m_pPlayer->GetWidth();
        int ph = m_pPlayer->GetHeight();

        for (auto eb : m_enemyBullets)
        {
            if (eb->IsActive())
            {
                float bx = eb->GetX();
                float by = eb->GetY();
                int bw = eb->GetWidth();
                int bh = eb->GetHeight();

                // Axis-Aligned Bounding Box (AABB) collision
                if (bx < px + pw && bx + bw > px &&
                    by < py + ph && by + bh > py)
                {
                    eb->SetActive(false); // Bullet disappears
                    m_pPlayer->TakeDamage(1); // Player loses 1 health and flashes red
                    break; // Only one bullet can hit at a time
                }
            }
        }
    }

    if (m_pPlayer && m_pPlayer->GetHealth() <= 0)
    {
        // Deactivate all enemy bullets
        for (auto eb : m_enemyBullets)
        {
            eb->SetActive(false);
        }

        // Stop the timer
        m_timerStarted = false;

        // Switch to lose scene (assuming it's at index 3)
        Game::GetInstance().m_iCurrentScene = 2;
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

    if (m_pPlayer && m_pPlayer->GetHealth() > 0)
    {
        m_pPlayer->Draw(renderer);

    }


    for (auto bullet : m_bullets)
    {
        if (bullet->IsActive())
            bullet->Draw(renderer);
    }

    if (m_showControls && m_pControls)
    {
        // Center the controls sprite
        int screenWidth = renderer.GetWidth();
        int screenHeight = renderer.GetHeight();
        int controlsWidth = m_pControls->GetWidth();
        int controlsHeight = m_pControls->GetHeight();
        int controlsX = (screenWidth - controlsWidth) / 2;
        int controlsY = (screenHeight - controlsHeight) / 2;

        m_pControls->SetX(controlsX);
        m_pControls->SetY(controlsY);
        m_pControls->SetAlpha(m_controlsAlpha);  // Set transparency (0 = invisible, 1 = opaque)
        m_pControls->Draw(renderer);
    }

    if (m_pEnemy && m_pEnemy->GetHealth() > 0)
    {
        m_pEnemy->Draw(renderer);
    }

    for (auto eb : m_enemyBullets)
    {
        if (eb->IsActive())
            eb->Draw(renderer);
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

void SceneGame::SpawnEnemyBullet(float spawnX, float spawnY, float targetX, float targetY, float speed)
{
    for (auto eb : m_enemyBullets)
    {
        if (!eb->IsActive())
        {
            eb->SetPosition(spawnX, spawnY);
            eb->SetTarget(targetX, targetY, speed);
            eb->SetActive(true);
            break;
        }
    }
}
