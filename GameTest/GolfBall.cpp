#include "stdafx.h"
#include "GolfBall.h"

GolfBall::GolfBall(Component* parent_) : Actor(parent_)
{

}

GolfBall::~GolfBall()
{
}

bool GolfBall::OnCreate()
{
	spriteComponent = new SpriteComponent(this);
	spriteComponent->LoadSprite(".\\TestData\\golfball.png", 1, 1);
	spriteComponent->SetPosition(500, 500);
	spriteComponent->SetScale(0.5f);  // Adjust scale as needed



	AddComponent(spriteComponent);

	return true;
}

void GolfBall::OnDestroy()
{
}

void GolfBall::Update(const float deltaTime_)
{

}

void GolfBall::Render() const
{
	spriteComponent->Render();
}

