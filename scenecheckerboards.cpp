// COMP710 GP Framework 2025
// This include:
#include "scenecheckerboards.h"

// Local includes:
#include "renderer.h" 
#include "sprite.h"

#include "imgui/imgui.h"

// Library includes:
#include <cassert>

SceneCheckerboards::SceneCheckerboards()
    : m_pCorners{ 0 }
    , m_pCentre(0)
    , m_angle(0.0f)
    , m_rotationSpeed(90.0f)
{

}

SceneCheckerboards::~SceneCheckerboards()
{
    for (int k = 0; k < 4; ++k)
    {
        delete m_pCorners[k];
        m_pCorners[k] = 0;
    }
    delete m_pCentre;
    m_pCentre = 0;
}

bool SceneCheckerboards::Initialise(Renderer& renderer)
{
    const int SCREEN_WIDTH = renderer.GetWidth();
    const int SCREEN_HEIGHT = renderer.GetHeight();

    m_pCentre = renderer.CreateSprite("..\\assets\\board8x8.png");
    m_pCorners[0] = renderer.CreateSprite("..\\assets\\board8x8.png");
    m_pCorners[1] = renderer.CreateSprite("..\\assets\\board8x8.png");
    m_pCorners[2] = renderer.CreateSprite("..\\assets\\board8x8.png");
    m_pCorners[3] = renderer.CreateSprite("..\\assets\\board8x8.png");

    //Custom: scale down
    float squareScale = 0.5f;
    for (int count = 0; count < 4; count++)
    {
        m_pCorners[count]->SetScale(squareScale);
    }
    
    const int BOARD_HALF_WIDTH = m_pCentre->GetWidth() / 2 * squareScale;
    const int BOARD_HALF_HEIGHT = m_pCentre->GetHeight() / 2 * squareScale;

    m_pCentre->SetX(SCREEN_WIDTH / 2);
    m_pCentre->SetY(SCREEN_HEIGHT / 2);

    // Top left white:
    m_pCorners[0]->SetX(BOARD_HALF_WIDTH);
    m_pCorners[0]->SetY(BOARD_HALF_HEIGHT);
    // Top right red:
    m_pCorners[1]->SetX(SCREEN_WIDTH - BOARD_HALF_WIDTH);
    m_pCorners[1]->SetY(BOARD_HALF_HEIGHT);
    m_pCorners[1]->SetGreenTint(0.0f);
    m_pCorners[1]->SetBlueTint(0.0f);
    // Bottom right green:
    m_pCorners[2]->SetX(SCREEN_WIDTH - BOARD_HALF_WIDTH);
    m_pCorners[2]->SetY(SCREEN_HEIGHT - BOARD_HALF_HEIGHT);
    m_pCorners[2]->SetRedTint(0.0f);
    m_pCorners[2]->SetBlueTint(0.0f);
    // bottom left blue
    m_pCorners[3]->SetX(BOARD_HALF_WIDTH);
    m_pCorners[3]->SetY(SCREEN_HEIGHT - BOARD_HALF_HEIGHT);
    m_pCorners[3]->SetRedTint(0.0f);
    m_pCorners[3]->SetGreenTint(0.0f);

    ////Text Testing
    //// Load static text textures into the Texture Manager... 
    //renderer.CreateStaticText("Auckland University of Technology", 50);

    //// Generate sprites that use the static text textures... 
    //m_pWelcomeText = renderer.CreateSprite("Auckland University of Technology");

    //m_pWelcomeText->SetY(SCREEN_HEIGHT / 2);
    //m_pWelcomeText->SetX(SCREEN_WIDTH / 2);
    //m_pWelcomeText->SetGreenTint(1.0f);
    
    //bugs: 1: setalpha doesnt work, 2: initialising any other sprite after CreateStaticText will crash.

    return true;
}

void SceneCheckerboards::Process(float deltaTime)
{
    for (int k = 0; k < 4; ++k)
    {
        m_pCorners[k]->Process(deltaTime);
    }
    m_angle += m_rotationSpeed * deltaTime;
    m_pCentre->SetAngle(m_angle);
    //m_pCentre->Process(deltaTime);

    //m_pWelcomeText->Process(deltaTime);
}

void SceneCheckerboards::Draw(Renderer& renderer)
{
    for (int k = 0; k < 4; ++k)
    {
        m_pCorners[k]->Draw(renderer);
    }

    m_pCentre->Draw(renderer);

    //m_pWelcomeText->Draw(renderer);
}

void SceneCheckerboards::DebugDraw()
{
    ImGui::Text("Scene: Checkerboards");
    ImGui::InputFloat("Rotation speed", &m_rotationSpeed);
    float scale = m_pCentre->GetScale();
    ImGui::SliderFloat("Demo scale", &scale, 0.0f, 2.0f, "%.3f");
    m_pCentre->SetScale(scale);

    int position[2];
    position[0] = m_pCentre->GetX();
    position[1] = m_pCentre->GetY();
    ImGui::InputInt2("Demo position", position);
    m_pCentre->SetX(position[0]);
    m_pCentre->SetY(position[1]);

    float tint[4];
    tint[0] = m_pCentre->GetRedTint();
    tint[1] = m_pCentre->GetGreenTint();
    tint[2] = m_pCentre->GetBlueTint();
    tint[3] = m_pCentre->GetAlpha();
    ImGui::ColorEdit4("Demo tint", tint);
    m_pCentre->SetRedTint(tint[0]);
    m_pCentre->SetGreenTint(tint[1]);
    m_pCentre->SetBlueTint(tint[2]);
    m_pCentre->SetAlpha(tint[3]);
}

void SceneCheckerboards::SyncCurrentScene(int* m_iCurrentScene, std::vector<Scene*>* m_scenes)
{

}