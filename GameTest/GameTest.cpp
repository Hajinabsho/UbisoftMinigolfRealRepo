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

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
//Since I'm not allow to change Main file, currently main is hardcoded to call game test. I will just use
//Game Test file as a Scene Manager in this case for better structure and creation of multiple Scene
Scene* currentScene = nullptr;
int currentLevel = 1;
bool isTransitioning;
bool pendingTransition;

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
		currentScene = new Scene1();
		break;
	case 2:
		currentScene = new Scene1();
		break;

	default:
		// Game complete or return to menu

		break;
	}
}


void OnVictory()
{
	//pendingTransition = true;

	currentLevel++;
	isTransitioning = true;
	LoadLevel(currentLevel);
	currentScene->Init();
	isTransitioning = false;

	std::cout << "Next Level!: " << currentLevel << '\n';
}

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);  // Redirect stdout to the console
	// Initialize with Scene0
	currentScene = new Scene1();
	currentScene->Init();
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


		if (currentScene->IsVictoryConditionMet())
		{
			OnVictory();
		}
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
		}
	}

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


