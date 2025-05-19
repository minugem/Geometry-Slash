// COMP710 GP Framework 
#ifndef GAME_H 
#define GAME_H 

//Libarary includes:
#include <vector>
#include "fmod.hpp"

// Forward declarations: 
class Renderer;
class Sprite;

class Scene;

class InputSystem;

class Game
{
	// Member methods: 
public:
	static Game& GetInstance();
	static void DestroyInstance();

	void ToggleDebugWindow();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

protected:
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	void DebugDraw();

	void ProcessFrameCounting(float deltaTime);

private:
	Game();
	~Game();
	Game(const Game& game);
	Game& operator=(const Game& game);

	// Member data: 
public:
	FMOD::System* m_pFmodSystem;
	FMOD::Sound* m_pFmodSound1;
	FMOD_RESULT result;


protected:
	static Game* sm_pInstance;
	Renderer* m_pRenderer;
	Sprite* m_pCheckerboard;

	std::vector<Scene*> m_scenes;
	int m_iCurrentScene;

	InputSystem* m_pInputSystem;
	
	bool m_bShowDebugWindow;
	


	_int64 m_iLastTime;
	float m_fExecutionTime;
	float m_fElapsedSeconds;
	int m_iFrameCount;
	int m_iFPS;

	//Detect buttons
	int m_iLeftPressed;
	int m_iLeftMousePressed;

#ifdef USE_LAG 
	float m_fLag;
	int m_iUpdateCount;
#endif // USE_LAG

	bool m_bLooping;

private:

};

#endif