#include "scenesplashaut.h"

#include "renderer.h"
#include "sprite.h"

#include "imgui/imgui.h"

#include "iostream"
#include "vector"

#include "inputsystem.h"

SceneSplashAut::SceneSplashAut()
{
	m_alphaValue = 2.0f;
	m_iCurrentLogo = 0;
}

SceneSplashAut::~SceneSplashAut()
{
	delete m_pAutLogo;
	m_pAutLogo = 0;

	delete m_pInputSystem;
	m_pInputSystem = 0;

	for (int count = 0; count < m_pSplashLogos.size(); count++)
	{
		delete m_pSplashLogos[count];
		m_pSplashLogos[count] = 0;
	}
}

bool SceneSplashAut::Initialise(Renderer& renderer)
{
	//Legacy thing
	/*m_pAutLogo = renderer.CreateSprite("..\\assets\\autlogo.png");
	m_pAutLogo->SetScale(0.1f);
	m_pAutLogo->SetX(renderer.GetWidth()/2);
	m_pAutLogo->SetY(renderer.GetHeight()/2);*/

	//New thing
	m_pSplashLogos.push_back(renderer.CreateSprite("..\\assets\\autlogo.png"));
	m_pSplashLogos[0]->SetScale(0.1f);
	m_pSplashLogos[0]->SetX(renderer.GetWidth() / 2);
	m_pSplashLogos[0]->SetY(renderer.GetHeight() / 2);

	m_pSplashLogos.push_back(renderer.CreateSprite("..\\assets\\FMOD Logo White - Black Background.png"));
	m_pSplashLogos[1]->SetScale(0.75f);
	m_pSplashLogos[1]->SetX(renderer.GetWidth() / 2);
	m_pSplashLogos[1]->SetY(renderer.GetHeight() / 2);

	//Input System stuff
	m_pInputSystem = new InputSystem();
	m_pInputSystem->Initialise();

	//Using box2d for physics

	return true;
}

void SceneSplashAut::Process(float deltaTime)
{
	//Legacy thing
	/*m_alphaValue -= 0.5f * deltaTime;
	m_pAutLogo->SetAlpha(m_alphaValue);*/

	//ButtonState spaceKeyState = (m_pInputSystem->GetKeyState(SDL_SCANCODE_SPACE));
	//if (spaceKeyState == BS_PRESSED)
	//{
	//	m_alphaValue = -0.5f;
	//}

	//if (m_alphaValue <= -0.5f)
	//{
	//	//*m_iCurrentSceneRef = 0;
	//	this->~SceneSplashAut();
	//	m_scenesRef->erase(m_scenesRef->begin());
	//}

	//New thing
	m_alphaValue -= 1.0f * deltaTime;
	m_pSplashLogos[m_iCurrentLogo]->SetAlpha(m_alphaValue);

	ButtonState spaceKeyState = (m_pInputSystem->GetKeyState(SDL_SCANCODE_SPACE));
	if (spaceKeyState == BS_PRESSED)
	{
		if (!m_iSpaceKeyPressed)
		{
			m_alphaValue = -0.5f;
			m_iSpaceKeyPressed = 1;
		}
	}
	else
	{
		if (m_iSpaceKeyPressed)
		{
			m_iSpaceKeyPressed = 0;
		}
	}

	if (m_alphaValue <= -0.5f)
	{
		if (m_iCurrentLogo < m_pSplashLogos.size() - 1)
		{
			m_iCurrentLogo++;
			m_alphaValue = 2.0f;
		}
		else
		{
			//m_iCurrentSceneRef = 0;
			this->~SceneSplashAut();
			m_scenesRef->erase(m_scenesRef->begin());
		}
	}


}

void SceneSplashAut::Draw(Renderer& renderer)
{
	//Legacy thing
	//m_pAutLogo->Draw(renderer);

	//New thing
	m_pSplashLogos[m_iCurrentLogo]->Draw(renderer);
}

void SceneSplashAut::DebugDraw()
{
	ImGui::Text("Scene: AUT Splash Screen");
}
	
void SceneSplashAut::SyncCurrentScene(int* m_iCurrentScene, std::vector<Scene*>* m_scenes)
{
	m_iCurrentSceneRef = m_iCurrentScene;
	m_scenesRef = m_scenes;

	/*std::cout << m_iCurrentScene << std::endl;
	std::cout << m_iCurrentSceneRef << std::endl;*/

	//std::cout << m_scenes << std::endl << m_scenesRef << std::endl;
}