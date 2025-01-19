#include "stdafx.h"
#include "GolfBall.h"

GolfBall::GolfBall(Component* parent_) : Actor(parent_)
{

}

GolfBall::GolfBall(Component* parent_, Camera* camera_) : Actor(parent_, camera_)
{
	camera = camera_;
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
	physics->SetPosition(PhysicsUtility::ToMeters(Vec2(200, 450)));
	physics->SetVelocity(Vec2(0.0f, 1.0f));
	physics->SetGravity(true);

	hitbox = new HitboxComponent(this, 0.5f);
	hitbox->SetActive(true);
	//hitbox->SetDimensions(Vec2(1.0f, 1.0f));

	AddComponent(spriteComponent);
	AddComponent(physics);
	AddComponent(hitbox);

	spawnPoint = PhysicsUtility::ToMeters(Vec2(200, 450));

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

	

	// Check for out of bounds
	if (position.y < outOfBoundsY) {
		Respawn();
		return;
	}


	if (physics->IsStopped()) {
		airHits = 0;
	}
	

	if (physics->IsStopped() || airHits < maxAirHits)
	{
		//if (physics->IsStopped() || airHits < maxAirHits) {
			//Dragging Mechanism
			if (abs(VectorMath::mag(position - GetMousePhysicsPosition())) < 0.2f) {
				if (App::IsKeyPressed(VK_LBUTTON))
				{
					if (!isDragging)
					{
						isDragging = true;
						dragStart = GetMousePhysicsPosition();
						//std::cout << "Pressed W" << '\n';
						std::cout << "Mouse On";

					}

				}

			}
			//Drag Release
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

				//std::cout << "Current Power: " << power << '\n';  // Debug output

				// Calculate line positions for rendering
				lineStart = PhysicsUtility::ToPixels(position);
				Vec2 dragDir = VectorMath::normalize(dragVector);
				float lineLength = power * maxLineLength;
				lineEnd = lineStart - (dragDir * lineLength);
				//

				// Draw the line
				if (camera) {
					// Both line endpoints need to be offset by the same amount
					Vec2 cameraOffset = PhysicsUtility::ToPixels(camera->GetOffset());
					lineStart = lineStart + cameraOffset;
					lineEnd = lineEnd + cameraOffset;
				}

				if (!App::IsKeyPressed(VK_LBUTTON))
				{
					// Only hit if we have some meaningful drag distance
					if (dragDistance > 0.01f) {
						Vec2 hitDirection = VectorMath::normalize(dragVector);
						//HitForce = 10.0f; // Adjust this to change maximum hit force
						physics->HitBall(hitDirection * (power * hitForce));
						totalHits++;
						if (!physics->IsStopped()) {
							airHits++;
						}
					}

					//std::cout << "relased" << '\n';
					isDragging = false;

				}
			}
		//}
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
	
	if (isDragging) {
		
		RenderDragLine();
	}
	std::string hitText = "Total Hits: " + std::to_string(totalHits);
	App::Print(100, 100, hitText.c_str());

}

void GolfBall::OnCollision(Actor& actor, Actor& otherActor)
{
	
	//To find collision response first calculate the normal. 
	// To do soGet Position of Two actor, and check if the collision is happening
	//vertically or horizontally. Then pass that normal to handle collision. But
	//the normal calculated here is not an accurate value but very rough version but will be enough
	//For this game lol
	Vec2 collisionPoint = position;
	Vec2 otherPos = otherActor.GetPosition();

	// Calculate the differences in x and y positions
	float yDiff = abs(collisionPoint.y - otherPos.y);
	float xDiff = abs(collisionPoint.x - otherPos.x);

	Vec2 normal;

	// Check if vertical collision (ground/ceiling)
	if (yDiff > xDiff) {
		
		normal.x = 0;
		if (collisionPoint.y > otherPos.y) {
			normal.y = 1.0f;  
		}
		else {
			normal.y = -1.0f; 
		}
	}
	// Horizontal collision (walls)
	else {
		
		normal.y = 0;
		if (collisionPoint.x > otherPos.x) {
			normal.x = 1.0f;  
		}
		else {
			normal.x = -1.0f; 
		}
	}

	physics->HandleCollision(normal);


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

	Vec2 physicsPos = PhysicsUtility::ToMeters(Vec2(mouseX, mouseY));

	// If we have a camera, subtract its offset to get the true world position
	if (camera) {
		physicsPos = physicsPos - camera->GetOffset();
	}

	return physicsPos;




	//Pre Camera Offset codes
	//float mouseX, mouseY;
	//App::GetMousePos(mouseX, mouseY);
	//
	//int width = APP_VIRTUAL_WIDTH;
	//int height = APP_VIRTUAL_HEIGHT;

	//// Check if mouse is within window bounds
	//bool isMouseInWindow = (mouseX >= 0 && mouseX < width &&
	//	mouseY >= 0 && mouseY < height);


	//return PhysicsUtility::ToMeters(Vec2(mouseX, mouseY));
}

void GolfBall::RenderDragLine() const
{
	App::DrawLine(lineStart.x, lineStart.y, lineEnd.x, lineEnd.y);
}

void GolfBall::Respawn()
{
	// Reset position to spawn point
	SetPosition(spawnPoint);
	physics->SetPosition(spawnPoint);
	physics->SetVelocity(Vec2(0.0f, 0.0f));
	isDragging = false;
	airHits = 0;
}

