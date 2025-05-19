#include "enemybullet.h"
#include "renderer.h"
#include "sprite.h"
#include <cmath>

EnemyBullet::EnemyBullet()
    : m_pSprite(0), m_x(0), m_y(0), m_dx(0), m_dy(0), m_speed(0), m_active(false)
{
}

EnemyBullet::~EnemyBullet()
{
    delete m_pSprite;
    m_pSprite = 0;
}

bool EnemyBullet::Initialise(Renderer& renderer)
{
    m_pSprite = renderer.CreateSprite("..\\assets\\enemybullet.png");
    return m_pSprite != 0;
}

void EnemyBullet::SetPosition(float x, float y)
{
    m_x = x;
    m_y = y;
}

void EnemyBullet::SetTarget(float targetX, float targetY, float speed)
{
    float dirX = targetX - m_x;
    float dirY = targetY - m_y;
    float length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length != 0)
    {
        m_dx = dirX / length;
        m_dy = dirY / length;
    }
    else
    {
        m_dx = 0;
        m_dy = 0;
    }
    m_speed = speed;
}

void EnemyBullet::Process(float deltaTime)
{
    if (m_active)
    {
        m_x += m_dx * m_speed * deltaTime;
        m_y += m_dy * m_speed * deltaTime;
        // Optionally, deactivate if off-screen
    }
}

void EnemyBullet::Draw(Renderer& renderer)
{
    if (m_active && m_pSprite)
    {
        m_pSprite->SetX(m_x);
        m_pSprite->SetY(m_y);
        m_pSprite->Draw(renderer);
    }
}

bool EnemyBullet::IsActive() const { return m_active; }
void EnemyBullet::SetActive(bool active) { m_active = active; }
float EnemyBullet::GetX() const { return m_x; }
float EnemyBullet::GetY() const { return m_y; }
int EnemyBullet::GetWidth() const { return m_pSprite ? m_pSprite->GetWidth() : 0; }
int EnemyBullet::GetHeight() const { return m_pSprite ? m_pSprite->GetHeight() : 0; }
