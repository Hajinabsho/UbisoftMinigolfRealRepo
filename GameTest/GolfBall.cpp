#include "stdafx.h"
#include "GolfBall.h"

GolfBall::GolfBall(Component* parent_) : Actor(parent_)
{

}

GolfBall::~GolfBall()
{
}

bool GolfBall::OnCreate()
{
	spriteComponent = new SpriteComponent(this);
	spriteComponent->LoadSprite(".\\TestData\\golfball.png", 1, 1);
	spriteComponent->SetPosition(500, 500);
	spriteComponent->SetScale(0.5f);  // Adjust scale as needed

	physics = new PhysicsComponent(nullptr);
	physics->SetPosition(PhysicsUtility::ToMeters(Vec2(500, 500)));
	physics->SetVelocity(Vec2(0.0f, 0.0f));
	physics->SetGravity(true);

	hitbox = new HitboxComponent(this, Vec2(1.0f, 1.0f));
	hitbox->SetActive(true);
	hitbox->SetDimensions(Vec2(1.0f, 1.0f));

	AddComponent(spriteComponent);
	AddComponent(physics);
	AddComponent(hitbox);

	return true;
}

void GolfBall::OnDestroy()
{
}

void GolfBall::Update(const float deltaTime_)
{
	SetPosition(physics->GetPosition());
	hitbox->SetCenter(position);
	hitbox->Update(deltaTime_);
	physics->Update(deltaTime_);


}

void GolfBall::Render() const
{
	Vec2 myVec = physics->GetPosition();
	myVec = PhysicsUtility::ToPixels(myVec);
	
	spriteComponent->SetPosition(myVec.x, myVec.y);

	//spriteComponent->SetPosition()
	spriteComponent->Render();
	hitbox->Render();
	
}

void GolfBall::OnCollision(Actor& actor, Actor& otherActor)
{

	std::cout << "GolfBall collided with: " << typeid(otherActor).name() << std::endl;


	Vec2 normal = VectorMath::normalize(GetPosition() - otherActor.GetPosition());
	
	physics->HandleCollision(normal);

}

