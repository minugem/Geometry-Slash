#include "enemy.h"
#include "renderer.h"
#include "sprite.h"

Enemy::Enemy()
    : m_speed(100.0f) // Example speed
{
    // Entity's constructor is called automatically
}

Enemy::~Enemy() {}

bool Enemy::Initialise(Renderer& renderer)
{
    m_pSprite = renderer.CreateSprite("..\\assets\\enemy.png");
    if (!m_pSprite)
        return false;
    m_bAlive = true;
    m_position.Set(400, 100); // Example start position
    return true;
}

void Enemy::Process(float deltaTime)
{
    // Example: Move enemy down the screen
    m_position.y += m_speed * deltaTime;

    // Optionally: Add logic for enemy AI, collision, etc.
}

void Enemy::Draw(Renderer& renderer)
{
    if (m_pSprite && m_bAlive)
    {
        m_pSprite->SetX(static_cast<int>(m_position.x));
        m_pSprite->SetY(static_cast<int>(m_position.y));
        m_pSprite->Draw(renderer);
    }
}
