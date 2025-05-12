// COMP710 GP Framework
#ifndef SCENEBOUNCINGBALLS_H   
#define SCENEBOUNCINGBALLS_H 

//Libarary includes:
#include "vector"

// Local includes: 
#include "scene.h"

// Forward declarations: 
class Renderer;
class Ball;

// Class declaration:
class SceneBouncingBalls : public Scene
{
	// Member methods: 
public:
	SceneBouncingBalls();
	virtual ~SceneBouncingBalls();

	virtual bool Initialise(Renderer& renderer); 
	virtual void Process(float deltaTime); 
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();

	virtual void SyncCurrentScene(int* m_iCurrentScene, std::vector<Scene*>* m_scenes);

protected:

private:
	SceneBouncingBalls(const SceneBouncingBalls& sceneBouncingBalls);
	SceneBouncingBalls& operator=(const SceneBouncingBalls& sceneBouncingBalls);

	// Member data:
public:

protected:
	Ball* m_pBalls[100];

	int m_iShowCount; 

private:

};

#endif //   SCENEBOUNCINGBALLS_H 
