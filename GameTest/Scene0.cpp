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

	golfBall = std::make_unique<GolfBall>(nullptr);
	golfBall->OnCreate();

	tileMap = std::make_unique<TileMap>(nullptr);
	tileMap->OnCreate();

	floor = std::make_unique<Floor>(nullptr);
	floor->OnCreate();

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


	//------------------------------------------------------------------------
// Example Sprite Code....
	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	testSprite->SetPosition(400.0f, 400.0f);
	const float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	testSprite->SetScale(1.0f);
	//------------------------------------------------------------------------


	background = App::CreateSprite(".\\TestData\\Background.png", 1, 1);
	background->SetPosition(512, 384.0f);

	//mySprite->LoadSprite(".\\TestData\\Basic_Top.png", 1, 1);



	//for (int y = 0; y < tileMap->GetHeight(); y++) {
	//	for (int x = 0; x < tileMap->GetWidth(); x++) {
	//		TileType tile = tileMap->GetTileAt(x, y); // Get tile data
	//		std::string tileTypeStr = (tile == TileType::Empty) ? "E" :
	//			(tile == TileType::Ground) ? "G" : "W"; // Use shorter representations for clarity

	//		// Output to console using std::cout, print in grid format
	//		std::cout << tileTypeStr << " ";  // Add a space between tiles for readability
	//	}
	//	std::cout << std::endl;  // After each row, print a newline to start a new line
	//}
}

void Scene0::Update(float deltaTime)
{    
	
	golfBall->Update(deltaTime);
	//floor->Update(deltaTime);
	tileMap->Update(deltaTime);

	hitboxSystem.updateActor(*golfBall);

	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite->Update(deltaTime);
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		std::cout << "hello" << '\n';
		testSprite->SetAnimation(ANIM_RIGHT);
		float x, y;
		testSprite->GetPosition(x, y);
		x += 1.0f;
		testSprite->SetPosition(x, y);

		//tileMap->GetTileAt(0, 0);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_LEFT);
		float x, y;
		testSprite->GetPosition(x, y);
		x -= 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_FORWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y += 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_BACKWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y -= 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		testSprite->SetScale(testSprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		testSprite->SetScale(testSprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		testSprite->SetAnimation(-1);
	}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav", true);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{
		App::StopSound(".\\TestData\\Test.wav");
	}
}

void Scene0::Render()
{
	//floor->Render();
	

	background->Draw();
	golfBall->Render();
	tileMap->Render();
	//------------------------------------------------------------------------
// Example Sprite Code....
	//testSprite->Draw();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(100, 100, "Sample Text");

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	//static float a = 0.0f;
	//const float r = 1.0f;
	//float g = 1.0f;
	//float b = 1.0f;
	//a += 0.1f;
	//for (int i = 0; i < 20; i++)
	//{

	//	const float sx = 200 + sinf(a + i * 0.1f) * 60.0f;
	//	const float sy = 200 + cosf(a + i * 0.1f) * 60.0f;
	//	const float ex = 700 - sinf(a + i * 0.1f) * 60.0f;
	//	const float ey = 700 - cosf(a + i * 0.1f) * 60.0f;
	//	g = (float)i / 20.0f;
	//	b = (float)i / 20.0f;
	//	App::DrawLine(sx, sy, ex, ey, r, g, b);
	//}
}

void Scene0::Shutdown()
{
	//------------------------------------------------------------------------
// Example Sprite Code....
	delete testSprite;
	//------------------------------------------------------------------------
}
