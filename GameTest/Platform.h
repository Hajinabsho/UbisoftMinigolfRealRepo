#pragma once
#include "Actor.h"

class Platform : public Actor
{
public:
	Platform(Component* parent_);
	~Platform();


	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void Render()const override;

	void SetPoints(float x1, float y1, float x2, float y2);
	void SetFriction(float f) { friction = f; }
	float GetFriction() const { return friction; }

	// Check if a point is colliding with this platform
	bool CheckCollision(float x, float y, float radius) const;

	// Get normal vector of the platform (useful for bounce)
	void GetNormal(float& nx, float& ny) const;




private:
	float startX, startY;
	float endX, endY;
	float friction;

};

