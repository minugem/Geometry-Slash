#include "player.h"
#include "renderer.h"
#include "sprite.h"
#include <cassert>

Player::Player()
    : m_pSprite(0)
    , m_x(0)
    , m_y(0)
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
    }
}

void Player::SetX(int x)
{
    m_x = x;
}

void Player::SetY(int y)
{
    m_y = y;
}

int Player::GetX() const
{
    return m_x;
}

int Player::GetY() const
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

