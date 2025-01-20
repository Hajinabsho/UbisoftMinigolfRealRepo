#include "stdafx.h"
#include "Scene5.h"

Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}

void Scene5::Init()
{
	background = App::CreateSprite(".\\TestData\\Background.png", 1, 1);
	background->SetPosition(512, 384.0f);
;
}

void Scene5::Update(float deltaTime)
{
	flickerTimer += deltaTime * 0.001f;  // Convert to seconds
	if (flickerTimer >= flickRate) {
		showText = !showText;  // Toggle visibility
		flickerTimer = 0.0f;   // Reset timer
	}

	if (App::IsKeyPressed(VK_SPACE) || App::IsKeyPressed(VK_LBUTTON)) {
		startGame = true;
	}


}

void Scene5::Render()
{

	background->Draw();

	if (showText) {
		App::Print(400, 300, "Click to Start!", 1.0f, 1.0f, 1.0f);
	}

}

void Scene5::Shutdown()
{
	delete background;
}

bool Scene5::IsVictoryConditionMet()
{
	if (startGame) {
		return true;
	}
	return false;
}
