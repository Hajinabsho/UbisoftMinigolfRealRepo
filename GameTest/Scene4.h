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

class Scene4 : public Scene
{
	CSimpleSprite* background;


	std::unique_ptr<TileMap> tileMap;
	std::unique_ptr<GolfBall> golfBall;
	std::unique_ptr<Camera> camera;


	HitboxSystem hitboxSystem;
public:
	Scene4();
	~Scene4();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Shutdown() override;
	bool IsVictoryConditionMet() override;
	GolfBall* GetGolfBall() override { return golfBall.get(); }

};

