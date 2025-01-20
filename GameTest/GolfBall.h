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
    int maxAirHits = 1;

    //For Respawn System
    Vec2 spawnPoint;
    float outOfBoundsY = 15.0f;

    //score
    int totalHits;

    //Bounce Sound Timer
    float bounceSoundTimer = 0.0f;
    float bounceSoundCoolDown = 0.1f;
    bool canPlayBounceSound = true;

    
    bool isGameStarted = false;


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

    int getMaxAirHit() { return maxAirHits; }
    void setMaxAirHit(int airHit_) { maxAirHits = airHit_; }

    void BallStrike(const Vec2& hitforce_);

    void StartGame() { isGameStarted = true; }


};

