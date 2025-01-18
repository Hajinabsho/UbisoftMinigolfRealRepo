#pragma once
#include "Actor.h"
#include "SpriteComponent.h"


class GolfBall : public Actor
{
private:
    SpriteComponent* spriteComponent;
    bool isMoving;
    float radius;


public:
    GolfBall(Component* parent_);
    virtual ~GolfBall();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;


};

