#pragma once
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"

#include "Scene.h"

//enum
//{
//	ANIM_FORWARDS,
//	ANIM_BACKWARDS,
//	ANIM_LEFT,
//	ANIM_RIGHT,
//};


class Scene0 : Scene
{
	CSimpleSprite* testSprite;


public:
	Scene0();
	~Scene0();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Shutdown() override;
};

