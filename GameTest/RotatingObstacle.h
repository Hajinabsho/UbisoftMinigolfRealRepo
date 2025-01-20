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
	float defaultAngle = 45.0f;
	bool isSpinning = true;

public:
	RotatingObstacle(Component* parent_, Camera* camera_);
	virtual ~RotatingObstacle();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void Render() const override;

	void SetDefaultAngle(float angle_) { defaultAngle = angle_; }
	void SetIsSpinning(bool spin_) { isSpinning = spin_; }
	void SetRotationSpeed(float speed) { rotationSpeed = speed; }
};

