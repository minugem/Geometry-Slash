#include "projectile.h"

Projectile::Projectile() : m_speed(400.0f) {}

Projectile::~Projectile() {}

bool Projectile::Initialise(Sprite& sprite, const Vector2& startPos, const Vector2& direction)
{
    m_pSprite = &sprite; // Or clone/copy if needed
    m_position = startPos;
    m_velocity = direction;
    m_velocity.Normalise();
    m_velocity *= m_speed;
    m_bAlive = true;
    return true;
}

void Projectile::Process(float deltaTime)
{
    m_position += m_velocity * deltaTime;
    // Optionally: set m_bAlive = false if off screen
}

void Projectile::Draw(Renderer& renderer)
{
    Entity::Draw(renderer);
}
