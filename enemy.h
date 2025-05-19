#ifndef ENEMY_H
#define ENEMY_H

class Renderer;
class Sprite;

class Enemy
{
public:
    Enemy();
    ~Enemy();

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    void SetPosition(float x, float y);
    float GetX() const;
    float GetY() const;
    int GetWidth() const;
    int GetHeight() const;

    void TakeDamage(int amount);
    int GetHealth() const;

private:
    Sprite* m_pSprite;
    float m_x;
    float m_y;
    int m_health;
    float m_hitTimer; 
};

#endif // ENEMY_H
