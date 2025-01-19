#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "HitboxComponent.h"
#include "GolfBall.h"


class Collectible : public Actor
{
protected:
    bool isCollected = false;

public:
    Collectible(Component* parent_, Camera* camera_ = nullptr);

    virtual void OnCollect(GolfBall* ball) = 0;  // Pure virtual function
    bool IsCollected() const { return isCollected; }

    

};

