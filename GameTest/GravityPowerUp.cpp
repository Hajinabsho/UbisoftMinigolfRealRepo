#include "stdafx.h"
#include "GravityPowerUp.h"

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
        std::cout << "OnCollectPowerup Called!";
        ball->GetComponent<PhysicsComponent>()->SetGravitySign(ball->GetComponent<PhysicsComponent>()->GetGravitySign() * -1);
        isOnCoolDown = true;
        cooldownTimer = 0.0f;
        spriteComponent->LoadSprite(".\\TestData\\GravityPowerUpCD.png", 1, 1);

    }


}

void GravityPowerUp::ReLoadSprite()
{
    spriteComponent->LoadSprite(".\\TestData\\GravityPowerUp.png", 1, 1);
}

