#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity
{
public:
    Enemy();
    ~Enemy();

    bool Initialise(Renderer& renderer) override;
    void Process(float deltaTime) override;
    void Draw(Renderer& renderer) override;

    // You can add more enemy-specific methods or variables here
    // e.g., movement pattern, health, etc.

private:
    float m_speed;
    // Add other enemy-specific members here
};

#endif // ENEMY_H
