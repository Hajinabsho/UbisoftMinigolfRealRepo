#include "stdafx.h"
#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(Component* parent_) : Component(parent_)
{
	velocity = Vec2(0, 0);
	accel = Vec2(0, 0);
	mass = 1.0f;
	radius = 0.05f;
	orientation = 0.0f;
	rotation = 0.0f;
	angular = 0.0f;
	momentOfInertia = 1.0f;
	maxAccel = 10.0f;
	maxVel = 5.0f;
	useGravity = false;
	gravity = 9.81f;
}

PhysicsComponent::~PhysicsComponent()
{
}

bool PhysicsComponent::OnCreate()
{
	return false;
}

void PhysicsComponent::OnDestroy()
{
}

void PhysicsComponent::Update(const float deltaTime_)
{
	// Convert milliseconds to seconds
	float deltaTimeSeconds = deltaTime_ * 0.001f;

	// Apply gravity if enabled
	if (useGravity) {
		Vec2 gravityForce(0.0f, -gravity * mass);  // Negative Y for downward force
		ApplyForce(gravityForce);
	}

	position = position + velocity * deltaTimeSeconds + accel * (0.5f * deltaTimeSeconds * deltaTimeSeconds);
	velocity = velocity + accel * deltaTimeSeconds;


}

void PhysicsComponent::Render() const
{
}

void PhysicsComponent::ApplyForce(const Vec2& force_)
{
}

void PhysicsComponent::ApplyAngularForce(float torque)
{
}
