#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsUtility.h"
#include "HitboxComponent.h"
#include "app\app.h"


class GolfBall : public Actor
{
private:
    SpriteComponent* spriteComponent;
    PhysicsComponent* physics;
    HitboxComponent* hitbox;

    bool isMoving;
    bool canHit;

    //Striking ball Mechanic
    float hitForce = 5.0f;
    float radius;

    bool isDragging;
    Vec2 dragStart;
    float maxDragDistance = 100.0f;
    
    //For trajectory rendering
    Vec2 lineStart;
    Vec2 lineEnd;
    float maxLineLength = 200.0f;

public:
    GolfBall(Component* parent_);
    virtual ~GolfBall();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;

    virtual void OnCollision(Actor& actor, Actor& otherActor) override;


    //GolfBall's class
    Vec2 GetMousePhysicsPosition() const;
    void RenderDragLine() const; 

};

