#include "stdafx.h"
#include "Scene2.h"

Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	camera = std::make_unique<Camera>();


	background = App::CreateSprite(".\\TestData\\Background.png", 1, 1);
	background->SetPosition(512, 384.0f);

	golfBall = std::make_unique<GolfBall>(nullptr, camera.get());
	golfBall->OnCreate();

	tileMap = std::make_unique<TileMap>(nullptr, camera.get());
	tileMap->SetMapData(MapConfigs::Level3());
	tileMap->OnCreate();




	//hitbox registration
	hitboxSystem.RegisterActor(golfBall.get());

	for (auto tile : tileMap->GetTiles())
	{
		if (tile)
		{
			hitboxSystem.RegisterActor(tile);
		}
	}

	hitboxSystem.AddObserver(golfBall->GetComponent<HitboxComponent>());


}

void Scene2::Update(float deltaTime)
{

	camera->Update(deltaTime);
	golfBall->Update(deltaTime);
	tileMap->Update(deltaTime);


	hitboxSystem.updateActor(*golfBall);
}

void Scene2::Render()
{

	background->Draw();

	tileMap->Render();
	golfBall->Render();

}

void Scene2::Shutdown()
{
	delete background;

}

bool Scene2::IsVictoryConditionMet()
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
