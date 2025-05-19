#include "player.h"
#include "renderer.h"
#include "sprite.h"
#include <cassert>

Player::Player()
    : m_pSprite(0)
    , m_x(0)
    , m_y(0)
    , m_angle(0.0f)
    , m_health(100)  // Initialize health to 100 or any default value
{
}

Player::~Player()
{
    delete m_pSprite;
    m_pSprite = 0;
}

bool Player::Initialise(Renderer& renderer)
{
    m_pSprite = renderer.CreateSprite("..\\assets\\player.png");
    if (m_pSprite == 0)
    {
        return false;
    }
    m_pSprite->SetX(m_x);
    m_pSprite->SetY(m_y);
    return true;
}

void Player::Process(float /*deltaTime*/)
{
    // Add movement or logic here if needed
}

void Player::Draw(Renderer& renderer)
{
    if (m_pSprite)
    {
        m_pSprite->SetX(m_x);
        m_pSprite->SetY(m_y);
        m_pSprite->Draw(renderer);
        m_pSprite->SetAngle(m_angle);
    }
}

void Player::SetX(float x)
{
    m_x = x;
}

void Player::SetY(float y)
{
    m_y = y;
}

float Player::GetX() const
{
    return m_x;
}

float Player::GetY() const
{
    return m_y;
}

int Player::GetWidth() const
{
    return m_pSprite ? m_pSprite->GetWidth() : 0;
}

int Player::GetHeight() const
{
    return m_pSprite ? m_pSprite->GetHeight() : 0;
}

void Player::SetAngle(float angle)
{
    m_angle = angle;
}

float Player::GetAngle() const
{
    return m_angle;
}

// Health methods
void Player::SetHealth(int health)
{
    m_health = health;
}

int Player::GetHealth() const
{
    return m_health;
}
