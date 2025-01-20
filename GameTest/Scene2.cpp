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

void Scene2::Update(float deltaTime)
{

	camera->Update(deltaTime);
	golfBall->Update(deltaTime);
	tileMap->Update(deltaTime);

	//rotatingObstacle->Update(deltaTime);

	hitboxSystem.updateActor(*golfBall);
}

void Scene2::Render()
{

	background->Draw();

	tileMap->Render();
	golfBall->Render();
	//rotatingObstacle->Render();

}

void Scene2::Shutdown()
{
	delete background;

}

bool Scene2::IsVictoryConditionMet()
{
	if (fabs(VectorMath::mag(golfBall->GetPosition()) - VectorMath::mag(tileMap->GetHolePos())) < 0.01f) {
		std::cout << "Ball in the Hole!";
		return false;
	}
	else {
		return false;
	}
	return false;
}
