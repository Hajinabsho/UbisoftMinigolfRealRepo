#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "HitboxComponent.h"

class Ramp : public Actor
{
private:
    SpriteComponent* spriteComponent;
    HitboxComponent* hitbox;
    float angle;  // Store the ramp angle


public:
    Ramp(Component* parent_, Camera* camera_, float angleInDegrees = 45.0f);
    virtual ~Ramp();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;
};

