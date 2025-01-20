#include "stdafx.h"
#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(Component* parent_, Camera* camera_):  Actor(parent_, camera_)
{
	sprite = nullptr;
	hitbox = nullptr;

	moveSpeed = 1.0f;
	progress = 0.0f;
	movingToEnd = true;
}

MovingPlatform::~MovingPlatform()
{
	OnDestroy();

}

bool MovingPlatform::OnCreate()
{
	position = Vec2(6, 5);
	sprite = new SpriteComponent(this);
	sprite->LoadSprite(".\\TestData\\ThinRotatingBlock.png", 1, 1);
	sprite->SetScale(0.3f);

	hitbox = new HitboxComponent(this, Vec2(3.0f, 0.3f));
	hitbox->SetActive(true);

	AddComponent(sprite);
	AddComponent(hitbox);

	return true;
}

void MovingPlatform::OnDestroy()
{
}

void MovingPlatform::Update(const float deltaTime_)
{
	float deltaSec = deltaTime_ * 0.001f;


//	// Update progress based on direction
//	if (movingToEnd) {
//		progress += moveSpeed * deltaSec;
//		if (progress >= 1.0f) {
//			progress = 1.0f;
//			movingToEnd = false;
//		}
//	}
//	else {
//		progress -= moveSpeed * deltaSec;
//		if (progress <= 0.0f) {
//			progress = 0.0f;
//			movingToEnd = true;
//		}
//	}
//
//	// Interpolate position 
//	Vec2 newPos = startPos + (endPos - startPos) * progress;
//	SetPosition(newPos);
}


void MovingPlatform::Render() const
{
	sprite->Render();
	hitbox->Render();

}