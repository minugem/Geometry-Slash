#ifndef PLAYER_H
#define PLAYER_H

// Forward declarations
class Renderer;
class Sprite;

class Player
{
public:
    Player();
    ~Player();

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);
    void TakeDamage(int amount);
    void SetX(float x);
    void SetY(float y);
    float GetX() const;
    float GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    void SetAngle(float angle);
    float GetAngle() const;

    // Health related methods
    void SetHealth(int health);
    int GetHealth() const;

protected:
private:
    Player(const Player& other);
    Player& operator=(const Player& other);
    float m_x;
    float m_y;
    float m_angle;
    float m_hitTimer; 
    int m_health; 

    Sprite* m_pSprite;       
    Sprite* m_pBgSprite;    
};

#endif // PLAYER_H
