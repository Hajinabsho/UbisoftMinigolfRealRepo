#pragma once
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"

#include "Scene.h"
#include "TileMap.h"
#include "memory.h"
#include "SpriteComponent.h"
#include "Floor.h"
#include "GolfBall.h"
#include "HitboxSystem.h"
#include "Camera.h"
#include "MapConfig.h"
#include "AirJumpPowerUp.h"
#include "RotatingObstacle.h"

class Scene2 : public Scene
{
	CSimpleSprite* background;
	//SpriteComponent* mySprite;
	//Floor* myGround;

	std::unique_ptr<TileMap> tileMap;
	std::unique_ptr<GolfBall> golfBall;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<RotatingObstacle> rotatingObstacle;


	HitboxSystem hitboxSystem;
public:
	Scene2();
	~Scene2();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Shutdown() override;
	bool IsVictoryConditionMet() override;
	GolfBall* GetGolfBall() override { return golfBall.get(); }

};

