#include "bullet.h"
#include "renderer.h"
#include "sprite.h"

Bullet::Bullet()
    : m_pSprite(0), m_x(0), m_y(0), m_speed(600.0f), m_active(false)
{
}

Bullet::~Bullet()
{
    delete m_pSprite;
}

bool Bullet::Initialise(Renderer& renderer)
{
    m_pSprite = renderer.CreateSprite("..\\assets\\playerbullet.png");
    return m_pSprite != 0;
}

void Bullet::SetPosition(float x, float y)
{
    m_x = x;
    m_y = y;
}

float Bullet::GetY() const
{
    return m_y;
}

float Bullet::GetX() const
{
    return m_x;
}

void Bullet::Process(float deltaTime)
{
    if (m_active)
    {
        m_y -= m_speed * deltaTime;
        // Deactivate if it goes off the screen (assuming 0 is the top)
        if (m_y + m_pSprite->GetHeight() < 0)
            m_active = false;
    }
}

void Bullet::Draw(Renderer& renderer)
{
    if (m_active && m_pSprite)
    {
        m_pSprite->SetX(m_x);
        m_pSprite->SetY(m_y);
        m_pSprite->Draw(renderer);
    }
}

int Bullet::GetWidth() const
{
    return m_pSprite ? m_pSprite->GetWidth() : 0;
}

int Bullet::GetHeight() const
{
    return m_pSprite ? m_pSprite->GetHeight() : 0;
}
