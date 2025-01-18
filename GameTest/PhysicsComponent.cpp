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
	gravity = 9.81f; //For Cartoon effect
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
	// Convert milliseconds to seconds but actually made it 10th time more slower
	float deltaTimeSeconds = deltaTime_ * 0.0001f;

	// Apply gravity if enabled
	if (useGravity) {
		Vec2 gravityForce(0.0f, -gravity * mass);  // Negative Y for downward force
		ApplyForce(gravityForce);
	}

	position = position + velocity * deltaTimeSeconds + accel * (0.5f * deltaTimeSeconds * deltaTimeSeconds);
	velocity = velocity + accel * deltaTimeSeconds;




	

	// Acceleration damping
	//if (VectorMath::mag(accel) > 0.0f) {
	//	float accelDampingFactor = 0.55f;
	//	accel = accel * accelDampingFactor;

	//	if (VectorMath::mag(accel) < 0.01f) {
	//		accel = Vec2(0.0f, 0.0f);
	//	}
	//}
}

void PhysicsComponent::Render() const
{
}

void PhysicsComponent::ApplyForce(const Vec2& force_)
{
	accel = force_ / mass;

	if (VectorMath::mag(accel) > maxAccel) {
		accel = VectorMath::normalize(accel) * maxAccel;
	}
}

void PhysicsComponent::ApplyAngularForce(float torque)
{
	angular = torque / momentOfInertia;
}

void PhysicsComponent::HandleCollision(const Vec2& normal)
{
	// Calculate velocity along the normal using dot product
	float velAlongNormal = VectorMath::dot(velocity, normal);

	velocity = velAlongNormal * 
	// Only reflect if we're moving into the surface
	//if (velAlongNormal < 0) {
	//	
	//	Vec2 reflectedVel = velocity - (normal * (2.0f * velAlongNormal));

	//	velocity = reflectedVel * bounceFactor;

	//	// Reset acceleration on collision to prevent sticking
	//	//accel = Vec2(0.0f, 0.0f);
	//}
}

Vec2 PhysicsComponent::CalculateCollisionNormal(const PhysicsUtility::CollisionInfo& info)
{
	return VectorMath::normalize(info.myCenter - info.otherCenter);
}
