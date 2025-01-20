#pragma once
#include "Collectible.h"
#include "App/SimpleSound.h"
class AirJumpPowerUp : public Collectible
{
private:
    SpriteComponent* spriteComponent;
    HitboxComponent* hitbox;

public:
    AirJumpPowerUp(Component* parent_, Camera* camera_);
    virtual ~AirJumpPowerUp();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;

    void OnCollect(GolfBall* ball) override;
    
};


