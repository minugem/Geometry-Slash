#ifndef BULLET_H
#define BULLET_H

class Renderer;
class Sprite;

class Bullet
{
public:
    Bullet();
    ~Bullet();
    int GetWidth() const;
    int GetHeight() const;

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    void SetPosition(float x, float y);
    float GetY() const;
    float GetX() const;
    bool IsActive() const { return m_active; }
    void SetActive(bool active) { m_active = active; }

private:
    Sprite* m_pSprite;
    float m_x;
    float m_y;
    float m_speed;
    bool m_active;
};

#endif // BULLET_H
