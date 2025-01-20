#pragma once
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"

#include "Scene.h"


class Scene5 : public Scene
{
	//std::unique_ptr<GolfBall> golfBall;
	bool startGame = false;

	float flickerTimer = 0.0f;
	bool showText = true;
	float flickRate = 0.5f;  // Toggle every 0.5 seconds

	std::unique_ptr<GolfBall> golfBall;


	CSimpleSprite* background;

public:
	Scene5();
	~Scene5();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Shutdown() override;
	bool IsVictoryConditionMet() override;
	GolfBall* GetGolfBall() override { return golfBall.get(); }

};

