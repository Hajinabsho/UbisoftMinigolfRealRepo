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
enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};


class Scene0 : public Scene
{
	CSimpleSprite* testSprite;
	CSimpleSprite* background;
	//SpriteComponent* mySprite;
	//Floor* myGround;

	std::unique_ptr<TileMap> tileMap;
	std::unique_ptr<GolfBall> golfBall;
	std::unique_ptr<Camera> camera;

	HitboxSystem hitboxSystem;
public:
	Scene0();
	~Scene0();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Shutdown() override;
	bool IsVictoryConditionMet() override;
};

