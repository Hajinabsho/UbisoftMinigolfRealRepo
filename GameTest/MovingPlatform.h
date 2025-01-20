#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "HitboxComponent.h"

class MovingPlatform : public Actor
{
	SpriteComponent* sprite;
	HitboxComponent* hitbox;

    Vec2 startPos;
    Vec2 endPos;
    float moveSpeed;

    // Direction variable
    float progress; 
    bool movingToEnd;  

public:
    MovingPlatform(Component* parent_, Camera* camera_);
    virtual ~MovingPlatform();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;



    void SetEndPoints(const Vec2& start, const Vec2& end) {
        startPos = start;
        endPos = end;
        SetPosition(start);
    }
    void SetMoveSpeed(float speed) { moveSpeed = speed; }
};

