#pragma once
#include "Component.h"
#include "VectorMath.h"
#include "PhysicsUtility.h"

/// <summary>
/// This will be in charge of object's physics movement. Especially for the player.
/// Will try to make it flexible so that certain objects will be not accel base
/// </summary>
class PhysicsComponent: public Component
{
private:
    Vec2 position;
    Vec2 velocity;
    Vec2 accel;
    float mass;
    float radius;
    float orientation;    // In radians
    float rotation;      // Angular velocity in radians/second
    float angular;       // Angular acceleration in radians/second^2
    float momentOfInertia;
    float maxAccel;
    float maxVel;
    bool useGravity;
    float gravity;

    //Arcady
    float bounceFactor;
    float linearDamping = 0.98f;    // Air resistance (0.98 = slight resistance, 0.8 = heavy resistance)
    float gravityScale = 0.5f;
    float minimumVelocity = 0.01f;

    // Ground parameters
    bool isGrounded = false;
    float groundFriction = 0.95f;   
    Vec2 groundNormal = Vec2(0, 1); 


public:
    PhysicsComponent(Component* parent_);
    virtual ~PhysicsComponent();

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(const float deltaTime_) override;
    void Render() const override;



    void ApplyForce(const Vec2& force_);
    void ApplyAngularForce(float torque);

    //I'm gonna calculate the normal dir of the collision and then apply velocity or force to the self object
    void HandleCollision(const Vec2& normal);
    Vec2 CalculateCollisionNormal(const PhysicsUtility::CollisionInfo& info);

    void ClearGrounded();

    //I know I'm throw modulairty out of the window but I spent too much time. on physics and feeling of the game
    //Todo: Make it modular
    void HitBall(const Vec2& hitForce);

    //Check if the ball is stopped
    bool PhysicsComponent::IsStopped() const
    {
        return isGrounded && VectorMath::mag(velocity) <= minimumVelocity;
    }




    // Getters and setters
    void SetPosition(const Vec2& pos) { position = pos; }
    Vec2 GetPosition() const { return position; }
    void SetVelocity(const Vec2& vel) { velocity = vel; }
    Vec2 GetVelocity() const { return velocity; }
    void SetMass(float m) { mass = m; }
    float GetMass() const { return mass; }
    void SetRadius(float r) {
        radius = r;
        // For a disc, moment of inertia = (1/2) * mass * radius^2
        momentOfInertia = 0.5f * mass * radius * radius;
    }
    float GetRadius() const { return radius; }
    void SetGravity(bool use, float value = 9.81f) {
        useGravity = use;
        gravity = value;
    }
    float GetOrientation() const { return orientation; }
    void SetOrientation(float angle) { orientation = angle; }
    float GetAngularVelocity() const { return rotation; }


};

