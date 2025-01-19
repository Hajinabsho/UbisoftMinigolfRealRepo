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

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
//Since I'm not allow to change Main file, currently main is hardcoded to call game test. I will just use
//Game Test file as a Scene Manager in this case for better structure and creation of multiple Scene
Scene* currentScene = nullptr;


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{

	// Initialize with Scene0
	currentScene = new Scene0();
	currentScene->Init();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	if (currentScene) {
		currentScene->Update(deltaTime);
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	if (currentScene) {
		currentScene->Render();
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