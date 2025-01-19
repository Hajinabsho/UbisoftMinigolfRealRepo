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

	// Air resistance (0.98 = slight resistance, 0.8 = heavy resistance)
	linearDamping = 0.98f;    
	bounceFactor = 0.7f;        
	gravityScale = 0.5f;      
	minimumVelocity = 0.1f;
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
	float deltaTimeSeconds = deltaTime_ * 0.001f;
	//velocity.print();

	//Gonna try more Arcade approach 
	// Only process physics if the ball is moving
	
	if (isGrounded) {

		// If velocity is below minimum threshold, stop the ball
		if (VectorMath::mag(Vec2(velocity)) < minimumVelocity && isGrounded)
		{
			velocity = Vec2(0.0f, 0.0f);
			
		}
		useGravity = false;
		
	}
	//if velocity is fast enough
	else if (VectorMath::mag(velocity) > minimumVelocity || !isGrounded)
	{
		// Apply gravity if enabled (as a direct velocity change)
		if (useGravity && !isGrounded)
		{
			velocity.y += (gravity * gravitySign) * gravityScale * deltaTimeSeconds;
			
		}
		//if(useGravity && VectorMath::mag(velocity) > minimumVelocity)
		//{
		//	useGravity = false;

		//}
		// Update position based on velocity
		position = position + (velocity * deltaTimeSeconds);

		// Apply linear damping (air resistance)
		velocity = velocity * pow(linearDamping, deltaTimeSeconds);
	}



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

	// Only bounce if we're moving into the surface
	if (velAlongNormal < 0)
	{
		// Calculate reflection vector: v' = v - 2(v·n)n
		Vec2 reflectedVel = velocity - (normal * (2.0f * velAlongNormal));

		// Apply bounciness and ensure we don't exceed max velocity
		velocity = reflectedVel * bounceFactor;

		// Cap velocity if it exceeds maximum
		float currentVel = VectorMath::mag(velocity);
		if (currentVel > maxVel)
		{
			velocity = VectorMath::normalize(velocity) * maxVel;
		}
		// If velocity is below minimum threshold, stop the ball
		if (VectorMath::mag(Vec2(velocity)) < minimumVelocity && !isGrounded)
		{
			isGrounded = true;
			useGravity = false;
			
		}
	}
	else 
	{

	}
}

Vec2 PhysicsComponent::CalculateCollisionNormal(const PhysicsUtility::CollisionInfo& info)
{
	return VectorMath::normalize(info.myCenter - info.otherCenter);
}

void PhysicsComponent::ClearGrounded()
{
	isGrounded = false;
	groundNormal = Vec2(0, 1);
}

void PhysicsComponent::HitBall(const Vec2& hitForce)
{
	velocity = hitForce;
	useGravity = true;
	isGrounded = false;
}