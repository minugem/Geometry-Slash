#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"

class Projectile : public Entity
{
public:
    Projectile();
    ~Projectile();

    bool Initialise(Sprite& sprite, const Vector2& startPos, const Vector2& direction);
    void Process(float deltaTime) override;
    void Draw(Renderer& renderer) override;

private:
    float m_speed;
};

#endif
