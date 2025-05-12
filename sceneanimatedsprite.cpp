#include "sceneanimatedsprite.h"

#include "renderer.h"
#include "animatedsprite.h"

#include "imgui/imgui.h"

#include "vector"
#include "iostream"

SceneAnimatedSprite::SceneAnimatedSprite()
{

}

SceneAnimatedSprite::~SceneAnimatedSprite()
{
	delete m_pStrip1;
	m_pStrip1 = 0;

	for (int count = 0; count < m_pAnimatedSprites.size(); count++)
	{
		delete m_pAnimatedSprites[count];
		m_pAnimatedSprites[count] = 0;
	}
}

bool SceneAnimatedSprite::Initialise(Renderer& renderer)
{
	//Initialise AnimatedSprite object (singular)
	m_pStrip1 = renderer.CreateAnimatedSprite("..\\assets\\anim8strip.png");
	m_pStrip1->SetupFrames(64, 64);
	m_pStrip1->SetFrameDuration(0.5f);
	m_pStrip1->SetLooping(true);
	m_pStrip1->Animate();

	m_pStrip1->SetX(renderer.GetWidth() / 2);
	m_pStrip1->SetY(renderer.GetHeight() / 2);

	//Initialise Animated Sprite object (multiple in vector array)
	m_pAnimatedSprites.push_back(renderer.CreateAnimatedSprite("..\\assets\\anim8strip.png"));
	m_pAnimatedSprites.push_back(renderer.CreateAnimatedSprite("..\\assets\\anim8stripx2sheet.png"));
	m_pAnimatedSprites.push_back(renderer.CreateAnimatedSprite("..\\assets\\explosion.png"));
	for (int count = 0; count < m_pAnimatedSprites.size(); count++)
	{
		m_pAnimatedSprites[count]->SetupFrames(64, 64);
		m_pAnimatedSprites[count]->SetFrameDuration(0.5f);
		m_pAnimatedSprites[count]->SetLooping(true);
		m_pAnimatedSprites[count]->Animate();

		m_pAnimatedSprites[count]->SetX((renderer.GetWidth() / (m_pAnimatedSprites.size()+1)) * (count+1));
		m_pAnimatedSprites[count]->SetY((renderer.GetHeight() / 2) + 128);
	}

	m_pAnimatedSprites[2]->SetFrameDuration(0.1f);

	return true;
}

void SceneAnimatedSprite::Process(float deltaTime)
{
	m_pStrip1->Process(deltaTime);

	for (int count = 0; count < m_pAnimatedSprites.size(); count++)
	{
		m_pAnimatedSprites[count]->Process(deltaTime);
	}
}

void SceneAnimatedSprite::Draw(Renderer& renderer)
{
	m_pStrip1->Draw(renderer);

	for (int count = 0; count < m_pAnimatedSprites.size(); count++)
	{
		m_pAnimatedSprites[count]->Draw(renderer);
	}
}

void SceneAnimatedSprite::DebugDraw()
{
	ImGui::Text("Scene: Animated Sprites");
}

void SceneAnimatedSprite::SyncCurrentScene(int* m_iCurrentScene, std::vector<Scene*>* m_scenes)
{

}