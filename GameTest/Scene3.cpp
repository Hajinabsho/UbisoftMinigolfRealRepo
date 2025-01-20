#include "stdafx.h"
#include "Scene3.h"

Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	camera = std::make_unique<Camera>();


	background = App::CreateSprite(".\\TestData\\Background.png", 1, 1);
	background->SetPosition(512, 384.0f);

	golfBall = std::make_unique<GolfBall>(nullptr, camera.get());
	golfBall->OnCreate();

	tileMap = std::make_unique<TileMap>(nullptr, camera.get());
	tileMap->SetMapData(MapConfigs::Level4());
	tileMap->OnCreate();



	//rotatingObstacle = std::make_unique<RotatingObstacle>(nullptr, camera.get());
	//rotatingObstacle->OnCreate();


	//hitbox registration
	hitboxSystem.RegisterActor(golfBall.get());
	//hitboxSystem.RegisterActor(rotatingObstacle.get());

	for (auto tile : tileMap->GetTiles())
	{
		if (tile)
		{
			hitboxSystem.RegisterActor(tile);
		}
	}

	hitboxSystem.AddObserver(golfBall->GetComponent<HitboxComponent>());

	//App::PlaySound(".\\TestData\\GolfHitting.wav", false);

}

void Scene3::Update(float deltaTime)
{

	camera->Update(deltaTime);
	golfBall->Update(deltaTime);
	tileMap->Update(deltaTime);

	//rotatingObstacle->Update(deltaTime);

	hitboxSystem.updateActor(*golfBall);
}

void Scene3::Render()
{

	background->Draw();

	tileMap->Render();
	golfBall->Render();
	//rotatingObstacle->Render();

}

void Scene3::Shutdown()
{
	delete background;

}

bool Scene3::IsVictoryConditionMet()
{
	Vec2 ballToHole = golfBall->GetPosition() - tileMap->GetHolePos();  // Vector from hole to ball
	float distanceToHole = VectorMath::mag(ballToHole);  // Actual distance between points
	float ballSpeed = VectorMath::mag(golfBall->GetComponent<PhysicsComponent>()->GetVelocity());


	if (distanceToHole < 0.7f && ballSpeed < 0.5f) {
		golfBall->StartVictoryAnimation(tileMap->GetHolePos());
		return true;
	}
	return false;
}
