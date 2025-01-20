///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
//Since I'm not allow to change Main file, currently main is hardcoded to call game test. I will just use
//Game Test file as a Scene Manager in this case for better structure and creation of multiple Scene
Scene* currentScene = nullptr;
int currentLevel = 0;
bool isTransitioning;
bool pendingTransition;

bool victoryTriggered = false;
float victoryTimer = 0.0f;
float victoryDelay = 3.0f;
int totalHits = 0;
int totalLevel = 5;

void LoadLevel(int level)
{
	//Delete the current scene
	if (currentScene) {
		currentScene->Shutdown();
		delete currentScene;
		currentScene = nullptr;
	}

	// Load  scene based on level
	switch (level) {
	case 1:
		currentScene = new Scene0();
		break;
	case 2:
		currentScene = new Scene1();
		break;

	case 3:
		currentScene = new Scene2();
		break;

	case 4:
		currentScene = new Scene3();
		break;

	case 5:
		currentScene = new Scene4();
		break;
		
	case 0:
		currentScene = new Scene5();
		break;
	default:
		// Game complete or return to menu

		break;
	}
}


void OnVictory()
{
	if (currentScene->GetGolfBall()) {
		totalHits += currentScene->GetGolfBall()->GetTotalHits();
		
	}
	if (currentLevel < totalLevel) {
		currentLevel++;
	}
	else {
		currentLevel = 0;
	}
	isTransitioning = true;
	LoadLevel(currentLevel);
	currentScene->Init();
	isTransitioning = false;

	//std::cout << "Next Level!: " << currentLevel << '\n';
}

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);  // Redirect stdout to the console
	// Initialize with Scene0
	currentScene = new Scene5();
	currentScene->Init();

	App::PlaySound(".\\TestData\\BackGroundMusic.mp3", true);
	
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{

	//if (pendingTransition) {
	//	currentLevel++;
	//	isTransitioning = true;
	//	LoadLevel(currentLevel);
	//	isTransitioning = false;
	//	pendingTransition = false;
	//	if (currentScene) {
	//		currentScene->Init(); 
	//	}
	//	return;  
	//}

	//if (!isTransitioning && currentScene) {
	//	currentScene->Update(deltaTime);
	//	if (currentScene->IsVictoryConditionMet())
	//	{
	//		// Just set the pending flag
	//		OnVictory();  
	//		return;  
	//	}
	//}









	if (!isTransitioning) {
		if (currentScene) {
			currentScene->Update(deltaTime);
		}


		// Check for victory
		if (!victoryTriggered && currentScene->IsVictoryConditionMet()) {
			
			victoryTriggered = true;
			victoryTimer = 0.0f;
			CSimpleSound::GetInstance().StartSound(".\\TestData\\LevelClear.wav");  
			return;
		}

		// Handle victory delay
		if (victoryTriggered) {
			victoryTimer += deltaTime * 0.001f;  
			if (victoryTimer >= victoryDelay) {
				OnVictory();
				victoryTriggered = false;  
			}
		}
		//if (currentScene->IsVictoryConditionMet())
		//{
		//	OnVictory();
		//}
	}

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	//if (!isTransitioning && !pendingTransition && currentScene) {
	//	currentScene->Render();
	//}

	if (!isTransitioning) {
		if (currentScene) {
			currentScene->Render();

			if (victoryTriggered && currentLevel > 0) {
				App::Print(400, 300, "Level Complete!");
			}
		}
	}
	
	std::string gameTotalHit = "Game Total Hits: " + std::to_string(totalHits);
	App::Print(700, 700, gameTotalHit.c_str());

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	if (currentScene) {
		currentScene->Shutdown();
		delete currentScene;
		currentScene = nullptr;
	}
}


