// COMP710 GP Framework 2025

#ifndef SCENEGAME_H
#define SCENEGAME_H
class InputSystem;

// Library includes:
#include <vector>

// Local includes:
#include "scene.h"
#include "bullet.h"
#include "player.h"  
#include <vector>


// Forward declarations:
class Renderer;
class Sprite;

// Class declaration:
class SceneGame : public Scene
{
public:
    SceneGame();
    virtual ~SceneGame();

    virtual bool Initialise(Renderer& renderer);
    virtual void Process(float deltaTime);
    virtual void Draw(Renderer& renderer);

    virtual void DebugDraw();
    virtual void SyncCurrentScene(int* m_iCurrentScene, std::vector<Scene*>* m_scenes);

protected:
    bool m_quitRequested;

private:
    SceneGame(const SceneGame& other);
    SceneGame& operator=(const SceneGame& other);
    InputSystem* m_pInputSystem; 
    Sprite* m_pCheckerboard;
    Player* m_pPlayer;
    bool QuitRequested() const { return m_quitRequested; }
    Bullet* m_pBullet;
    std::vector<Bullet*> m_bullets;
    float m_bulletCooldown;
    float m_bulletTimer;
};



#endif // SCENEGAME_H
