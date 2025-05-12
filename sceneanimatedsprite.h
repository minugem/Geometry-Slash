#ifndef SCENEANIMATEDSPRITE_H
#define SCENEANIMATEDSPRITE_H

#include "scene.h"

class Renderer;
class AnimatedSprite;

class SceneAnimatedSprite : public Scene
{
	//Member methods
public:
	SceneAnimatedSprite();
	virtual ~SceneAnimatedSprite();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();

	virtual void SyncCurrentScene(int* m_iCurrentScene, std::vector<Scene*>* m_scenes);

protected:

private:

	//Member data
public:

protected:
	AnimatedSprite* m_pStrip1;
	std::vector<AnimatedSprite*> m_pAnimatedSprites;

private:

};

#endif
