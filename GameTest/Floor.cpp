#include "stdafx.h"
#include "Floor.h"

Floor::Floor(Component* parent_) : Actor(parent_)
{

}


Floor::~Floor()
{
	OnDestroy();
}

bool Floor::OnCreate()
{
	sprite = new SpriteComponent(this);
	sprite->LoadSprite(".\\TestData\\Basic_Top.png", 1, 1);
	sprite->SetPosition(400, 300);
	AddComponent(sprite);

	


	return false;
}

void Floor::OnDestroy()
{

}

void Floor::Update(const float deltaTime_)
{
	sprite->Update(deltaTime_);
}

void Floor::Render() const
{
	sprite->Render();
}
