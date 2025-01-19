#include "stdafx.h"
#include "Camera.h"
#include "app\app.h"

Camera::Camera()
{
	offset = Vec2(0.0f, 0.0f);
	moveSpeed = 5.0f; 

    targetPos = Vec2(0.0f, 0.0f);
    followSpeed = 0.1f;
    deadZone = 0.5f;
    manualControl = true;
}

Camera::~Camera()
{
    
}

void Camera::Update(float deltaTime)
{
    float deltaSec = deltaTime * 0.001;
    //// Handle WASD input for camera movement
    if (App::IsKeyPressed('S')) 
    {
        offset.y += moveSpeed * deltaSec;
        
    }
    if (App::IsKeyPressed('W')) 
    {
        offset.y -= moveSpeed * deltaSec;
    }
    if (App::IsKeyPressed('D'))
    {
        offset.x -= moveSpeed * deltaSec;
    }
    if (App::IsKeyPressed('A')) 
    {
        offset.x += moveSpeed * deltaSec;
    }


    //Camera auto follow will not be used


}

Vec2 Camera::GetOffset() const
{
	return offset;
}

void Camera::SetOffset(const Vec2& newOffset)
{
    offset = newOffset;
}

void Camera::SetMoveSpeed(float speed)
{
    moveSpeed = speed;
}
