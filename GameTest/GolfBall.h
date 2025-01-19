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
    float hitForce = 7.0f;
    float radius;

    bool isDragging;
    Vec2 dragStart;
    float maxDragDistance = 100.0f;
    
    //For trajectory rendering
    Vec2 lineStart;
    Vec2 lineEnd;
    float maxLineLength = 200.0f;

    //Implmenting double hit
    int airHits = 0;
    int maxAirHits = 3;

    //For Respawn System
    Vec2 spawnPoint;
    float outOfBoundsY = -5.0f;

    //score
    int totalHits;

public:
    GolfBall(Component* parent_);
    GolfBall(Component* parent_, Camera* camera_);
    virtual ~GolfBall();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;

    virtual void OnCollision(Actor& actor, Actor& otherActor) override;


    //GolfBall's class
    Vec2 GetMousePhysicsPosition() const;
    void RenderDragLine() const; 
    void SetSpawnPoint(const Vec2& point) { spawnPoint = point; }
    int GetTotalHits() const { return totalHits; }
    void Respawn();


};

