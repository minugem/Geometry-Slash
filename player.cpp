#include "player.h"
#include "renderer.h"
#include "sprite.h"
#include <cassert>

Player::Player()
    : m_pSprite(0)
    , m_pBgSprite(0)
    , m_x(0)
    , m_y(0)
    , m_angle(0.0f)
    , m_health(3)
    , m_hitTimer(0.0f)
{
}

Player::~Player()
{
    delete m_pSprite;
    m_pSprite = 0;
    delete m_pBgSprite;
    m_pBgSprite = 0;
}


bool Player::Initialise(Renderer& renderer)
{
    m_pBgSprite = renderer.CreateSprite("..\\assets\\player.png");
    m_pSprite = renderer.CreateSprite("..\\assets\\hitbox.png");
    if (m_pSprite == 0 || m_pBgSprite == 0)
    {
        return false;
    }
    m_pSprite->SetX(m_x);
    m_pSprite->SetY(m_y);
    m_pBgSprite->SetX(m_x);
    m_pBgSprite->SetY(m_y);
    return true;
}


void Player::Process(float deltaTime)
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


void Player::Draw(Renderer& renderer)
{
    if (m_pBgSprite)
    {
        m_pBgSprite->SetX(m_x);
        m_pBgSprite->SetY(m_y - 5);  
        m_pBgSprite->SetAngle(m_angle);
        m_pBgSprite->Draw(renderer);
    }
    if (m_pSprite)
    {
        m_pSprite->SetX(m_x);
        m_pSprite->SetY(m_y);
        m_pSprite->SetAngle(m_angle);
        m_pSprite->Draw(renderer);
    }
}


void Player::TakeDamage(int amount)
{
    m_health -= amount;
    m_hitTimer = 0.1f; // Flash duration
    if (m_pSprite) {
        m_pSprite->SetRedTint(1.0f);
        m_pSprite->SetGreenTint(0.0f);
        m_pSprite->SetBlueTint(0.0f);
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

