#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsUtility.h"
#include "HitboxComponent.h"

class GolfBall : public Actor
{
private:
    SpriteComponent* spriteComponent;
    PhysicsComponent* physics;
    HitboxComponent* hitbox;

    bool isMoving;
    float radius;


public:
    GolfBall(Component* parent_);
    virtual ~GolfBall();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;


    virtual void OnCollision(Actor& actor, Actor& otherActor) override;
};

