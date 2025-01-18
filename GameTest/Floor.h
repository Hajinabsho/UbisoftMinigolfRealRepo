#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "HitboxComponent.h"


class Floor : public Actor
{
private:
    SpriteComponent* sprite;
    HitboxComponent* hitbox;

public:
    Floor(Component* parent_);
    ~Floor();

    //Interface functions
    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render()const override;

};

