#pragma once
#include "VectorMath.h"


//This class will act as an offset to move rendering of allll other Actors in the scene. 
//Since the competition rule forbid using OpenGL Translatef and stuff.
//Unfortuantely anything rendering will be coupled with Camera :(
class Camera
{
private:
	//Physics Space for both
	Vec2 offset;
	float moveSpeed;

	//tracking variables
	Vec2 targetPos;
	float followSpeed;
	float deadZone;
	bool manualControl;

public:
	Camera();
	~Camera();

	void Update(float deltaTime);
	Vec2 GetOffset() const;
	void SetOffset(const Vec2& newOffset);
	void SetMoveSpeed(float speed);

	//tracking function
	void SetTarget(const Vec2& target) { targetPos = target; }


};

