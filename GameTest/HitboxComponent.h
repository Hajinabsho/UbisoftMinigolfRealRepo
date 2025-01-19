#pragma once
#include "Component.h"
#include "Observer.h"
#include "app/app.h"
#include "PhysicsUtility.h"
#include "VectorMath.h"
#include "PhysicsComponent.h"
#include "cmath"

class HitboxComponent : public Component, public Observer
{
public:
	enum class ColliderType {
		Box,
		Sphere
	};


private:
	Vec2 center;
	Vec2 dimensions; 
	float radius; 
	bool isActive;
	ColliderType colliderType;


	// Private collision check methods
	bool CheckBoxBox(const HitboxComponent* other, const Vec2& myPos, const Vec2& otherPos) const;
	bool CheckSphereSphere(const HitboxComponent* other, const Vec2& myPos, const Vec2& otherPos) const;
	bool CheckSphereBox(const HitboxComponent* sphere, const HitboxComponent* box,
		const Vec2& spherePos, const Vec2& boxPos) const;
	
public:
	HitboxComponent(Component* parent_, const Vec2& dimensions_, const Vec2& center_ = Vec2(0.0f, 0.0f));
	HitboxComponent(Component* parent_, float radius_, const Vec2& center_ = Vec2(0.0f, 0.0f)); //For Sphere


	// Implement Component interface
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void Render() const override;


	bool CheckCollision(const HitboxComponent* other, const Vec2& myPos, const Vec2& otherPos) const;


	// Getters/Setters
	void SetActive(bool active) { isActive = active; }
	bool GetIsActive() const { return isActive; }
	Vec2 GetDimensions() const { return dimensions; }
	void SetDimensions(const Vec2& dim) { dimensions = dim; }
	Vec2 GetCenter() const { return center; }
	void SetCenter(const Vec2& pos) { center = pos; }
	float GetRadius() const { return radius; }
	void SetRadius(float r) { radius = r; }

	// Observer interface
	virtual void OnNotify(Actor& actor, Actor& otherActor) override;


};

