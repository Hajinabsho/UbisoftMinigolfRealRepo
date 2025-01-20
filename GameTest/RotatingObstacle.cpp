#include "stdafx.h"
#include "RotatingObstacle.h"

RotatingObstacle::RotatingObstacle(Component* parent_, Camera* camera_) : Actor(parent_, camera_)
{
	spriteComponent = nullptr;
	hitbox = nullptr;

	rotationSpeed = 1.0f;
	currentAngle = 0.0f;
}

RotatingObstacle::~RotatingObstacle()
{
	OnDestroy();
}

bool RotatingObstacle::OnCreate()
{
    position = Vec2(3, 5);
    spriteComponent = new SpriteComponent(this);
    spriteComponent->LoadSprite(".\\TestData\\ThinRotatingBlock.png", 1, 1);
    spriteComponent->SetPosition(500, 500);
    spriteComponent->SetScale(0.3f);  // Adjust based on your sprite size
    spriteComponent->SetRotation(defaultAngle);

    // Create a rectangular hitbox
    hitbox = new HitboxComponent(this, Vec2(3.5f, 0.3f), position);  // Long and thin
    hitbox->SetActive(true);
    hitbox->SetAngle(defaultAngle);
    


    AddComponent(spriteComponent);
    AddComponent(hitbox);

    return true;
}

void RotatingObstacle::OnDestroy()
{

}

void RotatingObstacle::Update(const float deltaTime_)
{
    if (isSpinning) {
        float deltaSec = deltaTime_ * 0.001f;
        currentAngle += rotationSpeed * deltaSec;
        hitbox->SetAngle(currentAngle);

        if (currentAngle >= 360.0f) {
            currentAngle -= 360.0f;
        }
        spriteComponent->SetRotation(currentAngle);
        
    }

   // hitbox->Update(deltaTime_);

}

void RotatingObstacle::Render() const
{
    spriteComponent->Render();
    hitbox->Render();
}
