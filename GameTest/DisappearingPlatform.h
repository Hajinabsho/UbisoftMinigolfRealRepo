#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "HitboxComponent.h"

class DisappearingPlatform : public Actor
{
private:
    SpriteComponent* sprite;
    HitboxComponent* hitbox;


    bool isDisappearing = false;
    float disappearTimer = 0.0f;
    float reappearTimer = 0.0f;

    float timeTillDisappear = 0.2f;
    float timeTIllReappear = 10.0f;

public:
    DisappearingPlatform(Component* parent_, Camera* camera_);
    virtual ~DisappearingPlatform();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;

    void OnCollision(Actor& actor, Actor& otherActor) override;

    void StartDisappearing();
};

