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
	physics->SetVelocity(Vec2(1.0f, 1.0f));
	physics->SetGravity(true);

	hitbox = new HitboxComponent(this, 0.5f);
	hitbox->SetActive(true);
	//hitbox->SetDimensions(Vec2(1.0f, 1.0f));

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


	//Dragging Mechanism
	if (abs(VectorMath::mag(position - GetMousePhysicsPosition())) < 0.2f) {
		if (App::IsKeyPressed(VK_LBUTTON))
		{
			if (!isDragging) 
			{
				isDragging = true;
				dragStart = GetMousePhysicsPosition();
				std::cout << "Pressed W" << '\n';

			}

		}

	}
	if (isDragging) 
	{
		// Calculate drag vector and distance while dragging
		Vec2 currentMousePos = GetMousePhysicsPosition();
		Vec2 dragVector = dragStart - currentMousePos;
		float dragDistance = VectorMath::mag(dragVector);

		// Cap the distance to our maximum power
		const float MAX_DRAG_DISTANCE = 2.0f; // Adjust this value to change maximum drag distance
		dragDistance = std::min(dragDistance, MAX_DRAG_DISTANCE);

		// Calculate power (0 to 1)
		float power = dragDistance / MAX_DRAG_DISTANCE;

		std::cout << "Current Power: " << power << '\n';  // Debug output


		if (!App::IsKeyPressed(VK_LBUTTON))
		{
			// Only hit if we have some meaningful drag distance
			if (dragDistance > 0.01f) {
				Vec2 hitDirection = VectorMath::normalize(dragVector);
				float maxHitForce = 10.0f; // Adjust this to change maximum hit force
				physics->HitBall(hitDirection * (power * maxHitForce));
			}

			std::cout << "relased" << '\n';
			isDragging = false;
		}
	}










	if (physics->IsStopped()) 
	{
		if (App::IsKeyPressed('W')) {
			
			std::cout << "Pressed W" << '\n';
		}
		if (App::IsKeyPressed('S')) {
			
			std::cout << "Pressed S" << '\n';
		}
		if (App::IsKeyPressed('A')) {
			
			std::cout << "Pressed A" << '\n';
		}
		if (App::IsKeyPressed('D')) {
		
			std::cout << "Pressed D" << '\n';
		}

	}

	
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

	//std::cout << "GolfBall collided with: " << typeid(otherActor).name() << std::endl;


	//Vec2 normal = VectorMath::normalize(GetPosition() - otherActor.GetPosition());
	//
	//physics->HandleCollision(normal);


	// Calculate collision point and proper normal based on collision geometry
	Vec2 collisionPoint = position; // Or get from your collision system
	Vec2 otherPos = otherActor.GetPosition();

	// For ground/ceiling
	if (abs(collisionPoint.y - otherPos.y) > abs(collisionPoint.x - otherPos.x)) {
		Vec2 normal(0, collisionPoint.y > otherPos.y ? 1.0f : -1.0f);
		physics->HandleCollision(normal);
	}
	// For walls
	else {
		Vec2 normal(collisionPoint.x > otherPos.x ? 1.0f : -1.0f, 0);
		physics->HandleCollision(normal);
	}



}

Vec2 GolfBall::GetMousePhysicsPosition() const
{

	float mouseX, mouseY;
	App::GetMousePos(mouseX, mouseY);
	
	int width = APP_VIRTUAL_WIDTH;
	int height = APP_VIRTUAL_HEIGHT;

	// Check if mouse is within window bounds
	bool isMouseInWindow = (mouseX >= 0 && mouseX < width &&
		mouseY >= 0 && mouseY < height);




	return PhysicsUtility::ToMeters(Vec2(mouseX, mouseY));
}

