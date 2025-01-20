#include "stdafx.h"
#include "Scene0.h"


Scene0::Scene0()
{
}

Scene0::~Scene0()
{
}

void Scene0::Init()
{
	camera = std::make_unique<Camera>();


	background = App::CreateSprite(".\\TestData\\Background.png", 1, 1);
	background->SetPosition(512, 384.0f);

	golfBall = std::make_unique<GolfBall>(nullptr, camera.get());
	golfBall->OnCreate();

	tileMap = std::make_unique<TileMap>(nullptr, camera.get());
	tileMap->SetMapData(MapConfigs::Level1());
	//tileMap = std::make_unique<TileMap>(nullptr);
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

	//hitboxSystem.RegisterActor(tileMap->getTiles)



}

void Scene0::Update(float deltaTime)
{    
	camera->Update(deltaTime);
	golfBall->Update(deltaTime);
	tileMap->Update(deltaTime);

	hitboxSystem.updateActor(*golfBall);

	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite->Update(deltaTime);
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{


		//tileMap->GetTileAt(0, 0);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{

	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{

	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{

	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
	}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	//{
	//	App::PlaySound(".\\TestData\\Test.wav", true);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	//{
	//	App::StopSound(".\\TestData\\Test.wav");
	//}
}

void Scene0::Render()
{
	

	background->Draw();
	
	tileMap->Render();
	golfBall->Render();

	
	//App::Print(100, 100, "Sample Text");

}

void Scene0::Shutdown()
{
	//------------------------------------------------------------------------
// Example Sprite Code....
	//delete testSprite;
	delete background;
	//delete camera;
	//------------------------------------------------------------------------
}

bool Scene0::IsVictoryConditionMet()
{

	Vec2 ballToHole = golfBall->GetPosition() - tileMap->GetHolePos();  // Vector from hole to ball
	float distanceToHole = VectorMath::mag(ballToHole);  // Actual distance between points
	float ballSpeed = VectorMath::mag(golfBall->GetComponent<PhysicsComponent>()->GetVelocity());


	if (distanceToHole < 1.0f && ballSpeed < 1.0f) {
		golfBall->StartVictoryAnimation(tileMap->GetHolePos());
		return true;
	}
	return false;

	//Vec2 ballToHole = golfBall->GetPosition() - tileMap->GetHolePos();
	//float distanceToHole = fabs(VectorMath::mag(golfBall->GetPosition()) - VectorMath::mag(tileMap->GetHolePos()));
	//float ballSpeed = VectorMath::mag(golfBall->GetComponent<PhysicsComponent>()->GetVelocity());
	////
	//if (distanceToHole < 0.05f && ballSpeed < 1.0f) {  // Adjust these thresholds as needed
	//	golfBall->StartVictoryAnimation(tileMap->GetHolePos());
	//	return true;
	//}
	//return false;

	
	//if (fabs(VectorMath::mag(golfBall->GetPosition()) - VectorMath::mag(tileMap->GetHolePos())) < 0.01f && VectorMath::mag(golfBall->GetComponent<PhysicsComponent>()->GetVelocity()) < 1.0f) {
	//	//std::cout << "Ball in the Hole!";
	//	return true;
	//}
	//else {
	//	return false;
	//}
}
