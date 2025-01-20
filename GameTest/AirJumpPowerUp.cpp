#include "stdafx.h"
#include "AirJumpPowerUp.h"

AirJumpPowerUp::AirJumpPowerUp(Component* parent_, Camera* camera_) : Collectible(parent_, camera_)
{

}

AirJumpPowerUp::~AirJumpPowerUp()
{
    OnDestroy();
}

bool AirJumpPowerUp::OnCreate()
{
    position = Vec2(6, 5);
    spriteComponent = new SpriteComponent(this);
    spriteComponent->LoadSprite(".\\TestData\\AirPowerUp.png", 1, 1);
    spriteComponent->SetPosition(800, 1800);
    spriteComponent->SetScale(1.0f);  

    hitbox = new HitboxComponent(this, 0.5f, position);
    hitbox->SetActive(true);

    AddComponent(spriteComponent);
    AddComponent(hitbox);

	return true;
}

void AirJumpPowerUp::OnDestroy()
{

}

void AirJumpPowerUp::Update(const float deltaTime_)
{
    if (isCollected == false) {
        hitbox->Update(deltaTime_);

    }
}

void AirJumpPowerUp::Render() const
{
    if (isCollected == false) {
        spriteComponent->Render();
        hitbox->Render();
    }

}

void AirJumpPowerUp::OnCollect(GolfBall* ball)
{
    if (!isCollected) {
        CSimpleSound::GetInstance().StartSound(".\\TestData\\PowerUp.wav");

        ball->setMaxAirHit(ball->getMaxAirHit() + 1);
        isCollected = true;
        SetActive(false);
    }
    
}


