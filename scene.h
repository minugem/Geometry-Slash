// COMP710 GP Framework 2025 
#ifndef   __SCENE_H_
#define   __SCENE_H_

//Library includes:
#include <vector>

// Forward declarations:
class Renderer;

// Class declaration: 
class Scene
{
	// Member methods: 
public:
	Scene();
	virtual ~Scene();

	virtual bool Initialise(Renderer& renderer) = 0;
	virtual void Process(float deltaTime) = 0;
	virtual void Draw(Renderer& renderer) = 0;

	virtual void DebugDraw() = 0;

	virtual void SyncCurrentScene(int* m_iCurrentScene, std::vector<Scene*>* m_scenes) = 0;

protected:

private:
	Scene(const Scene& scene);
	Scene& operator=(const Scene& scene);

	// Member data: 
public:

protected:
	int* m_iCurrentSceneRef;
	std::vector<Scene*>* m_scenesRef;

private:

};
#endif // !__SCENE_
