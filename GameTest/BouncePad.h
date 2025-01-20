#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include "HitboxComponent.h"

class BouncePad : public Actor {
private:
    SpriteComponent* sprite;
    HitboxComponent* hitbox;
    float bounceForce = 3.0f;  // Adjust this value for bounce strength

public:
    BouncePad(Component* parent_, Camera* camera_);
    virtual ~BouncePad();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;

    float GetBounceForce() const { return bounceForce; }
    void SetBounceForce(float force) { bounceForce = force; }
};

