#include "stdafx.h"
#include "DisappearingPlatform.h"
#include "GolfBall.h"
#include "App/SimpleSound.h"

DisappearingPlatform::DisappearingPlatform(Component* parent_, Camera* camera_) : Actor(parent_, camera_)
{
	sprite = nullptr;
	hitbox = nullptr;
}

DisappearingPlatform::~DisappearingPlatform()
{
}

bool DisappearingPlatform::OnCreate()
{
    sprite = new SpriteComponent(this);
    sprite->LoadSprite(".\\TestData\\ice.png", 1, 1);
    sprite->SetScale(0.4f);  
    hitbox = new HitboxComponent(this, Vec2(0.64f, 0.64f), position);
    hitbox->SetActive(true);

    AddComponent(sprite);
    AddComponent(hitbox);

	return true;
}

void DisappearingPlatform::OnDestroy()
{
}

void DisappearingPlatform::Update(const float deltaTime_)
{
    float dt = deltaTime_ * 0.001f;  

    if (isDisappearing) {
        disappearTimer += dt;
        if (disappearTimer >= timeTillDisappear) {
            // Just disable components instead of the whole actor
            sprite->SetVisible(false);
            hitbox->SetActive(false);
            isDisappearing = false;
            reappearTimer = 0.0f;
            
        }
    }
    else if (!hitbox->GetIsActive()) {  // Check component state instead of actor
        reappearTimer += dt;
        if (reappearTimer >= timeTIllReappear) {
            sprite->SetVisible(true);
            hitbox->SetActive(true);
            
        }
    }

}

void DisappearingPlatform::Render() const
{
    
        sprite->Render();
        //hitbox->Render();
    

}

void DisappearingPlatform::OnCollision(Actor& actor, Actor& otherActor)
{

}


void DisappearingPlatform::StartDisappearing()
{
	if (!isDisappearing) {
		isDisappearing = true;
		disappearTimer = 0.0f;
        CSimpleSound::GetInstance().StartSound(".\\TestData\\blockExplosion.mp3");
        
	}

}
