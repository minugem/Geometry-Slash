#include "enemybullet.h"
#include "renderer.h"
#include "sprite.h"
#include <cmath>

EnemyBullet::EnemyBullet()
    : m_pSprite(0), m_x(0), m_y(0), m_dirX(0), m_dirY(0), m_speed(300.0f), m_active(false)
{
}

EnemyBullet::~EnemyBullet()
{
    delete m_pSprite;
}

bool EnemyBullet::Initialise(Renderer& renderer)
{
    m_pSprite = renderer.CreateSprite("..\\assets\\enemybullet.png");
    return m_pSprite != 0;
}

void EnemyBullet::Fire(float startX, float startY, float targetX, float targetY)
{
    m_x = startX;
    m_y = startY;
    float dx = targetX - startX;
    float dy = targetY - startY;
    float len = sqrtf(dx * dx + dy * dy);
    if (len > 0)
    {
        m_dirX = dx / len;
        m_dirY = dy / len;
    }
    m_active = true;
}

void EnemyBullet::Process(float deltaTime)
{
    if (m_active)
    {
        m_x += m_dirX * m_speed * deltaTime;
        m_y += m_dirY * m_speed * deltaTime;
        // Deactivate if off screen (adjust bounds as needed)
        if (m_x < -100 || m_x > 2000 || m_y < -100 || m_y > 2000)
            m_active = false;
    }
}

void EnemyBullet::Draw(Renderer& renderer)
{
    if (m_active && m_pSprite)
    {
        m_pSprite->SetX(static_cast<int>(m_x));
        m_pSprite->SetY(static_cast<int>(m_y));
        m_pSprite->Draw(renderer);
    }
}

int EnemyBullet::GetWidth() const { return m_pSprite ? m_pSprite->GetWidth() : 0; }
int EnemyBullet::GetHeight() const { return m_pSprite ? m_pSprite->GetHeight() : 0; }
