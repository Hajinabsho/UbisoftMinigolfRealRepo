#include "stdafx.h"
#include "GravityPowerUp.h"
#include "App/SimpleSound.h"

GravityPowerUp::GravityPowerUp(Component* parent_, Camera* camera_) : Collectible(parent_, camera_)
{
	spriteComponent = nullptr;
	hitbox = nullptr;
}

GravityPowerUp::~GravityPowerUp()
{
	OnDestroy();
}

bool GravityPowerUp::OnCreate()
{

    spriteComponent = new SpriteComponent(this);
    spriteComponent->LoadSprite(".\\TestData\\GravityPowerUp.png", 1, 1);
    spriteComponent->SetScale(1.0f);  // Adjust as needed

    hitbox = new HitboxComponent(this, 0.5f, position);
    hitbox->SetActive(true);

    AddComponent(spriteComponent);
    AddComponent(hitbox);

    return true;

}

void GravityPowerUp::OnDestroy()
{

}

void GravityPowerUp::Update(const float deltaTime_)
{
    if (isCollected == false) {
        hitbox->Update(deltaTime_);

    }

    if (isOnCoolDown) {
        cooldownTimer += deltaTime_ * 0.001f;  // Convert to seconds
        if (cooldownTimer >= coolDownDuration) {
            isOnCoolDown = false;
            cooldownTimer = 0.0f;
            ReLoadSprite();
        }
    }

}

void GravityPowerUp::Render() const
{
    if (isCollected == false) {
        spriteComponent->Render();
        hitbox->Render();
    }


}

void GravityPowerUp::OnCollect(GolfBall* ball)
{
    if (!isOnCoolDown) {
        ball->GetComponent<PhysicsComponent>()->SetGravitySign(ball->GetComponent<PhysicsComponent>()->GetGravitySign() * -1);
        isOnCoolDown = true;
        cooldownTimer = 0.0f;
        spriteComponent->LoadSprite(".\\TestData\\GravityPowerUpCD.png", 1, 1);
        PlayGravitySound(ball->GetComponent<PhysicsComponent>()->GetGravitySign());

    }


}

void GravityPowerUp::ReLoadSprite()
{
    spriteComponent->LoadSprite(".\\TestData\\GravityPowerUp.png", 1, 1);
}

void GravityPowerUp::PlayGravitySound(float sign_)
{
    //Normal gravity
    if (sign_ < 0) {
        CSimpleSound::GetInstance().StartSound(".\\TestData\\GravityOff.wav");

    }
    //reverse gravity
    else {
        CSimpleSound::GetInstance().StartSound(".\\TestData\\GravityOn.wav");

    }
}

