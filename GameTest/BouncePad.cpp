#include "stdafx.h"
#include "BouncePad.h"

BouncePad::BouncePad(Component* parent_, Camera* camera_) : Actor(parent_, camera_)
{
	sprite = nullptr;
	hitbox = nullptr;
}

BouncePad::~BouncePad()
{
	OnDestroy();
}



bool BouncePad::OnCreate()
{
	sprite = new SpriteComponent(this);
	sprite->LoadSprite(".\\TestData\\BouncePad.png", 1, 1);
	sprite->SetScale(1.0f);
	hitbox = new HitboxComponent(this, Vec2(0.64f, 0.64f), position);
	hitbox->SetActive(true);

	AddComponent(sprite);
	AddComponent(hitbox);

	return true;
}

void BouncePad::OnDestroy()
{
}

void BouncePad::Update(const float deltaTime_)
{
}

void BouncePad::Render() const
{
	sprite->Render();
	hitbox->Render();
}
