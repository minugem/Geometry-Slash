// COMP710 GP Framework 2022

#ifndef SCENECHECKERBOARDS_H  
#define SCENECHECKERBOARDS_H 

//Library includes:
#include "vector"

// Local includes: 
#include "scene.h"

// Forward declarations: 
class Renderer;
class Sprite;

// Class declaration:
class SceneCheckerboards : public Scene
{
	// Member methods:
public:
	SceneCheckerboards();
	virtual ~SceneCheckerboards();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime); 
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();

	virtual void SyncCurrentScene(int* m_iCurrentScene, std::vector<Scene*>* m_scenes);

protected:

private:
	SceneCheckerboards(const SceneCheckerboards& sceneCheckerboards); 
	SceneCheckerboards& operator=(const SceneCheckerboards& sceneCheckerboards);


	// Member data: 
public:

protected:
	Sprite* m_pCorners[4]; 
	Sprite* m_pCentre;

	Sprite* m_pWelcomeText;

	float m_angle;
	float m_rotationSpeed;

private:

};

#endif //   SCENECHECKERBOARDS_H 
