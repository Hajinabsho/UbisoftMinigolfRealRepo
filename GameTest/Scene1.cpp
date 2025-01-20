#include "stdafx.h"
#include "Scene1.h"

Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	camera = std::make_unique<Camera>();


	background = App::CreateSprite(".\\TestData\\Background.png", 1, 1);
	background->SetPosition(512, 384.0f);

	golfBall = std::make_unique<GolfBall>(nullptr, camera.get());
	golfBall->OnCreate();

	tileMap = std::make_unique<TileMap>(nullptr, camera.get());
	tileMap->SetMapData(MapConfigs::Level2());
	tileMap->OnCreate();



	rotatingObstacle = std::make_unique<RotatingObstacle>(nullptr, camera.get());
	rotatingObstacle->OnCreate();


	//hitbox registration
	hitboxSystem.RegisterActor(golfBall.get());
	hitboxSystem.RegisterActor(rotatingObstacle.get());

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

void Scene1::Update(float deltaTime)
{
	
	camera->Update(deltaTime);
	golfBall->Update(deltaTime);
	tileMap->Update(deltaTime);
	
	rotatingObstacle->Update(deltaTime);

	hitboxSystem.updateActor(*golfBall);
}

void Scene1::Render()
{

	background->Draw();

	tileMap->Render();
	golfBall->Render();
	rotatingObstacle->Render();

}

void Scene1::Shutdown()
{
	delete background;

}

bool Scene1::IsVictoryConditionMet()
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
