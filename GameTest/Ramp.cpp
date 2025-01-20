#include "stdafx.h"
#include "Ramp.h"

Ramp::Ramp(Component* parent_, Camera* camera_, float angleInDegrees) : Actor(parent_, camera_)
{
	spriteComponent = nullptr;
	hitbox = nullptr;
    angle = 45.0f;
}

Ramp::~Ramp()
{
	OnDestroy();
}

bool Ramp::OnCreate()
{
    spriteComponent = new SpriteComponent(this);
    spriteComponent->LoadSprite(".\\TestData\\Basic_Top.png", 1, 1);
    spriteComponent->SetScale(0.12f);

    hitbox = new HitboxComponent(this, Vec2(1.0f, 1.0f));
    hitbox->SetActive(true);
    hitbox->SetAngle(angle);

    spriteComponent->SetRotation(angle);

    AddComponent(spriteComponent);
    AddComponent(hitbox);

    return true;
	
}

void Ramp::OnDestroy()
{

}

void Ramp::Update(const float deltaTime_)
{
    hitbox->Update(deltaTime_);
}

void Ramp::Render() const
{
    spriteComponent->Render();
   // hitbox->Render();
}

