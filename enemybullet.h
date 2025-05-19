#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

class Renderer;
class Sprite;

class EnemyBullet
{
public:
    EnemyBullet();
    ~EnemyBullet();

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    void SetPosition(float x, float y);
    void SetTarget(float targetX, float targetY, float speed);
    bool IsActive() const;
    void SetActive(bool active);

    float GetX() const;
    float GetY() const;
    int GetWidth() const;
    int GetHeight() const;

private:
    Sprite* m_pSprite;
    float m_x, m_y;
    float m_dx, m_dy;
    float m_speed;
    bool m_active;
};

#endif // ENEMYBULLET_H
