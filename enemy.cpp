#include "enemy.h"
#include "renderer.h"
#include "sprite.h"

Enemy::Enemy()
    : m_pSprite(0), m_x(0), m_y(0), m_health(200), m_hitTimer(0.0f)
{
}

Enemy::~Enemy()
{
    delete m_pSprite;
}

bool Enemy::Initialise(Renderer& renderer)
{
    m_pSprite = renderer.CreateSprite("..\\assets\\enemy.png");
    return m_pSprite != 0;
}

void Enemy::Process(float deltaTime)
{
    if (m_hitTimer > 0.0f) {
        m_hitTimer -= deltaTime;
        if (m_hitTimer <= 0.0f && m_pSprite) {
            m_pSprite->SetRedTint(1.0f);
            m_pSprite->SetGreenTint(1.0f);
            m_pSprite->SetBlueTint(1.0f);
        }
    }
}

void Enemy::Draw(Renderer& renderer)
{
    if (m_pSprite && m_health > 0)
    {
        m_pSprite->SetX(m_x);
        m_pSprite->SetY(m_y);
        m_pSprite->Draw(renderer);
    }
}

void Enemy::SetPosition(float x, float y)
{
    m_x = x;
    m_y = y;
}

void Enemy::TakeDamage(int amount)
{
    m_health -= amount;
    m_hitTimer = 0.1f;
    if (m_pSprite) {
        m_pSprite->SetRedTint(1.0f);
        m_pSprite->SetGreenTint(0.0f);
        m_pSprite->SetBlueTint(0.0f);
    }
}

float Enemy::GetX() const { return m_x; }
float Enemy::GetY() const { return m_y; }
int Enemy::GetWidth() const { return m_pSprite ? m_pSprite->GetWidth() : 0; }
int Enemy::GetHeight() const { return m_pSprite ? m_pSprite->GetHeight() : 0; }
int Enemy::GetHealth() const { return m_health; }
