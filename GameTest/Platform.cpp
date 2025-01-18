#include "stdafx.h"
#include "Platform.h"

Platform::Platform(Component* parent_) :Actor(parent_)
{
	startX = 0;
	startY = 0;
	endX = 0;
	endY = 0;
	friction = 0.5f;
}

Platform::~Platform()
{
}

bool Platform::OnCreate()
{
	return false;
}

void Platform::OnDestroy()
{
}

void Platform::Update(const float deltaTime_)
{
}

void Platform::GetNormal(float& nx, float& ny) const
{
}

void Platform::Render() const
{
}

void Platform::SetPoints(float x1, float y1, float x2, float y2)
{
}

bool Platform::CheckCollision(float x, float y, float radius) const
{
	return false;
}
