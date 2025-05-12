#ifndef SCENESPLASHAUT_H
#define SCENESPLASHAUT_H

#include "scene.h"

#include "vector"

class Renderer;
class Sprite;

class InputSystem;

class SceneSplashAut : public Scene
{
	//Member methheads
public:
	SceneSplashAut();
	virtual ~SceneSplashAut();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();

	virtual void SyncCurrentScene(int* m_iCurrentScene, std::vector<Scene*>* m_scenes);

protected:

private:

	//Member dater
public:

protected:
	Sprite* m_pAutLogo;
	std::vector<Sprite*> m_pSplashLogos;

	InputSystem* m_pInputSystem;
	int m_iSpaceKeyPressed;

	int m_iCurrentLogo;

	float m_alphaValue;

private:

};

#endif