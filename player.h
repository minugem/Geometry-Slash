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

    void SetX(float x);
    void SetY(float y);
    float GetX() const;
    float GetY() const;
    int GetWidth() const;
    int GetHeight() const;


protected:
private:
    Player(const Player& other);
    Player& operator=(const Player& other);

    Sprite* m_pSprite;
    float m_x;
    float m_y;
};

#endif // PLAYER_H
