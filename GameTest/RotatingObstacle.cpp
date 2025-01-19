#include "stdafx.h"
#include "RotatingObstacle.h"

RotatingObstacle::RotatingObstacle(Component* parent_, Camera* camera_) : Actor(parent_, camera_)
{
	spriteComponent = nullptr;
	hitbox = nullptr;
}

RotatingObstacle::~RotatingObstacle()
{

}

bool RotatingObstacle::OnCreate()
{

	return false;
}

void RotatingObstacle::OnDestroy()
{

}

void RotatingObstacle::Update(const float deltaTime_)
{

}
