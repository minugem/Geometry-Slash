// COMP710 GP Framework 2022

// This include: 
#include "game.h"

// Library includes: 
#include "renderer.h" 
#include "logmanager.h"
#include "sprite.h"

#include "scenesplashaut.h"

#include "scenegame.h"


#include "imgui/imgui_impl_sdl2.h"

#include "inputsystem.h"

//#include "fmod.hpp"

#include <iostream>

// Static Members:
Game* Game::sm_pInstance = 0;

Game& Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	return (*sm_pInstance);
}

void Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game() : m_pRenderer(0), m_bLooping(true)
{

}

Game::~Game()
{
	delete m_pRenderer;
	m_pRenderer = 0;

	m_pFmodSystem->release();
}

void Game::Quit()
{
	m_bLooping = false;
}

bool Game::Initialise()
{

	FMOD::Channel* testChannel = nullptr;
	m_pFmodSystem->playSound(m_pFmodSound1, 0, false, &testChannel);

	int bbWidth = 1080;
	int bbHeight = 720;

	m_pRenderer = new Renderer();
	if (!m_pRenderer->Initialise(true, bbWidth, bbHeight))
	{
		LogManager::GetInstance().Log("Renderer failed to initialise!");
		return false;
	}

	bbWidth = m_pRenderer->GetWidth();
	bbHeight = m_pRenderer->GetHeight();

	m_iLastTime = SDL_GetPerformanceCounter();

	m_pRenderer->SetClearColour(0, 0, 0);

	//m_pCheckerboard = m_pRenderer->CreateSprite("..\\assets\\board8x8.png");
	
	//Scene implementation
	Scene* pScene = 0;

	pScene = new SceneSplashAut();
	pScene->Initialise(*m_pRenderer);
	pScene->SyncCurrentScene(&m_iCurrentScene, &m_scenes);
	m_scenes.push_back(pScene);

	pScene = new SceneGame();
	pScene->Initialise(*m_pRenderer);
	m_scenes.push_back(pScene);


	//Initial Scene
	m_iCurrentScene = 0;

	//Input System stuff
	m_pInputSystem = new InputSystem();
	m_pInputSystem->Initialise();

	//Show debug?
	m_bShowDebugWindow = true;

	//FMOD
	if (FMOD::System_Create(&m_pFmodSystem) != FMOD_OK)
	{
		LogManager::GetInstance().Log("FMOD System failed to create!");
		std::cout << "FMOD System failed to create! (console edition)" << std::endl;
		return false;
	}
	
	if (m_pFmodSystem->init(512, FMOD_INIT_NORMAL, 0) != FMOD_OK)
	{
		LogManager::GetInstance().Log("FMOD System failed to create!");
		std::cout << "FMOD System failed to create! (console edition)" << std::endl;
		return false;
	}

	//FMOD Test
	m_pFmodSystem->createSound("..\\assets\\swish.wav", FMOD_DEFAULT, 0, &m_pFmodSound1);
	m_pFmodSound1->setMode(FMOD_LOOP_OFF);

	m_pFmodSystem->playSound(m_pFmodSound1, 0, false, 0);

	return true;
}

bool Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	// TODO: Process input here!
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		//IMGUI start
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplSDL2_ProcessEvent(&event);
		//IMGUI end
		
		//continue;
	}

	if (m_bLooping)
	{
		Uint64 current = SDL_GetPerformanceCounter();
		float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

		m_iLastTime = current;

		m_fExecutionTime += deltaTime;

		Process(deltaTime);

#ifdef USE_LAG
		m_fLag += deltaTime;

		int innerLag = 0;

		while (m_fLag >= stepSize)
		{
			Process(stepSize);

			m_fLag -= stepSize;

			++m_iUpdateCount;
			++innerLag;
		}
#endif //USE_LAG

		Draw(*m_pRenderer);
	}

	return m_bLooping;
}

void Game::Process(float deltaTime)
{
	ProcessFrameCounting(deltaTime);

	// TODO: Add game objects to process here!
	//m_pCheckerboard->Process(deltaTime);

	//Testing Key Input
	ButtonState graveKeyState = (m_pInputSystem->GetKeyState(SDL_SCANCODE_GRAVE));
	if (graveKeyState == BS_PRESSED)
	{
		if (!m_iLeftPressed)
		{
			m_iLeftPressed = 1;
			m_bShowDebugWindow = !m_bShowDebugWindow;
			LogManager::GetInstance().Log("Grave key pressed.");
			
		}
	}
	else if (graveKeyState == 0)
	{
		if (m_iLeftPressed)
		{
			m_iLeftPressed = 0;
			LogManager::GetInstance().Log("Grave key released.");
		}
	}

	//Testing Mouse Input
	m_pInputSystem->ProcessInput();
	int result = m_pInputSystem->GetMouseButtonState(SDL_BUTTON_LEFT);
	//std::cout << result << std::endl;
	if (result == BS_PRESSED)
	{
		if (!m_iLeftMousePressed)
		{
			m_iLeftMousePressed = 1;
			LogManager::GetInstance().Log("Left mouse button pressed.");
		}
	}
	else if (result == 0)
	{
		if (m_iLeftMousePressed)
		{
			m_iLeftMousePressed = 0;
			LogManager::GetInstance().Log("Left mouse button released.");

		}
	}


	//Scene Checkerboard thing
	m_scenes[m_iCurrentScene]->Process(deltaTime);

	//FMOD stuff
	m_pFmodSystem->update();
}

void Game::Draw(Renderer& renderer)
{
	++m_iFrameCount;

	renderer.Clear();

	// TODO: Add game objects to draw here!
	//m_pCheckerboard->Draw(renderer);

	//Scene Checkerboard thing
	m_scenes[m_iCurrentScene]->Draw(renderer);

	//IMGUI stuff
	DebugDraw();

	renderer.Present();
}

void Game::ProcessFrameCounting(float deltaTime)
{
	// Count total simulation time elapsed: 
	m_fElapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_fElapsedSeconds > 1.0f)
	{
		m_fElapsedSeconds -= 1.0f; 
		m_iFPS = m_iFrameCount;
		m_iFrameCount = 0;
	}
}

void Game::DebugDraw()
{
	if (m_bShowDebugWindow)
	{
		bool open = true;
		ImGui::Begin("Debug Window", &open, ImGuiWindowFlags_MenuBar);
		ImGui::Text("COMP710 GP Framework (%s)", "2022, S2");

		if (ImGui::Button("Quit"))
		{
			Quit();
		}

		ImGui::SliderInt("Active scene", &m_iCurrentScene, 0, m_scenes.size() - 1, "%d");
		m_scenes[m_iCurrentScene]->DebugDraw();

		ImGui::End();
	}
}

void Game::ToggleDebugWindow()
{
	m_bShowDebugWindow = !m_bShowDebugWindow;

	m_pInputSystem->ShowMouseCursor(m_bShowDebugWindow);
}