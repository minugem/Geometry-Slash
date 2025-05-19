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
    void Fire(float startX, float startY, float targetX, float targetY);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    bool IsActive() const { return m_active; }
    void SetActive(bool active) { m_active = active; }
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    int GetWidth() const;
    int GetHeight() const;

private:
    Sprite* m_pSprite;
    float m_x, m_y;
    float m_dirX, m_dirY;
    float m_speed;
    bool m_active;
};

#endif
