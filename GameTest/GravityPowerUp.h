#pragma once
#include "Collectible.h"
#include "PhysicsUtility.h"

class GravityPowerUp : public Collectible
{
private:
    SpriteComponent* spriteComponent;
    HitboxComponent* hitbox;

    bool isOnCoolDown = false;
    float cooldownTimer = 0.0f;
    float coolDownDuration = 3.0f;

public:
    GravityPowerUp(Component* parent_, Camera* camera_);
    virtual ~GravityPowerUp();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;


    void OnCollect(GolfBall* ball) override;
    
    void ReLoadSprite();
    
    void PlayGravitySound(float sign_);
};

