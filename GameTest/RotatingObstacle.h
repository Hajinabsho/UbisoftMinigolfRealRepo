#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "HitboxComponent.h"

class RotatingObstacle : public Actor
{
private:
	SpriteComponent* spriteComponent;
	HitboxComponent* hitbox;
	//Degree
	float rotationSpeed;  
	float currentAngle;


public:
	RotatingObstacle(Component* parent_, Camera* camera_);
	virtual ~RotatingObstacle();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void SetRotationSpeed(float speed) { rotationSpeed = speed; }
};

