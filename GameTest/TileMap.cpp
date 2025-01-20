#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(Component* parent_) :Actor(parent_)
{

}

TileMap::TileMap(Component* parent_, Camera* camera_) :Actor(parent_, camera_)
{
    camera = camera_;
}

TileMap::~TileMap()
{
    OnDestroy();
}

bool TileMap::OnCreate()
{

    // Load shared sprites once
    groundSprite = new SpriteComponent(this);
    wallSprite = new SpriteComponent(this);

    groundSprite->LoadSprite(".\\TestData\\Basic_Top.png", 1, 1);
    wallSprite->LoadSprite(".\\TestData\\Basic_Right.png", 1, 1);

    groundSprite->SetPosition(400, 600);
    wallSprite->SetPosition(600, 400);


    // Create tile actors based on the map data
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (static_cast<TileType>(mapData[y][x]) != TileType::Empty) {
                CreateTile(x, y, static_cast<TileType>(mapData[y][x]));
            }
        }
    }
    return true;
}

void TileMap::OnDestroy()
{
    delete groundSprite;
    delete wallSprite;

    for (auto tile : tiles) {
        if (tile) {
            delete tile;
        }
    }
 

    // Clear the vector that holds the tiles
    tiles.clear();
}

void TileMap::Update(const float deltaTime_)
{
    for (const auto& tile : tiles)
    {
        if (tile && tile->IsActive()) {
            tile->Update(deltaTime_);  // This will call render on all tile components including sprite
            tile->GetComponent<SpriteComponent>()->Update(deltaTime_);
            //tile->GetComponent<HitboxComponent>()->Update(deltaTime_);
        }
    }

}

void TileMap::Render() const
{
    // Render all tiles
    for (const auto& tile : tiles)
    {
        if (tile && tile->IsActive()) {
            tile->Render();  // This will call render on all tile components including sprite
            tile->GetComponent<SpriteComponent>()->Render();

            if (tile->GetComponent<HitboxComponent>()) {
                tile->GetComponent<HitboxComponent>()->Render();
            }
            
        }
    }



}

void TileMap::CreateTile(int x, int y, TileType type)
{
     
    Actor* tile = new Actor(this, camera);
    //tile->SetPosition(x * TILE_SIZE, y * TILE_SIZE);

    float worldX = x * TILE_SIZE;
    float worldY = (MAP_HEIGHT - y - 1) * TILE_SIZE;  // Flip Y coordinate since your grid starts from top
    tile->SetPosition(PhysicsUtility::ToMeters(Vec2(worldX, worldY)));
 
    

    // Add sprite component
    SpriteComponent* sprite = new SpriteComponent(tile);

    tile->AddComponent(sprite);

    // Load different sprites based on tile type
    //I would use flyweight pattern and reuse the texture info if I could alter the Sprite class 
    switch (type) {
    case TileType::Ground:
        sprite->LoadSprite(".\\TestData\\Basic_Top.png", 1, 1);
        sprite->SetPosition(worldX, worldY);  // Use calculated position
        sprite->SetScale(0.12f);
        //sprite->SetPosition(400, 600);
        break;
    case TileType::Wall:
        sprite->LoadSprite(".\\TestData\\Basic_Right.png", 1, 1);
        sprite->SetPosition(worldX, worldY);  // Use calculated position
        sprite->SetScale(0.12f);
        //sprite->SetPosition(600, 400);
        break;

    case TileType::Hole:
        sprite->LoadSprite(".\\TestData\\hole.png", 1, 1);
        sprite->SetPosition(worldX, worldY);
        sprite->SetScale(1.0f);
        tiles.push_back(tile);
        holePos = PhysicsUtility::ToMeters(Vec2(worldX, worldY));

        return;
        break;

    case TileType::Flag:
        sprite->LoadSprite(".\\TestData\\Flag.png", 1, 1);
        sprite->SetPosition(worldX, worldY);
        sprite->SetScale(1.0f);
        tiles.push_back(tile);
        return;
        break;

    case TileType::AirPowerUp: 
    {
        delete tile;
        AirJumpPowerUp* airPowerUp = new AirJumpPowerUp(nullptr, camera);
        airPowerUp->OnCreate();
        airPowerUp->SetPosition(PhysicsUtility::ToMeters(Vec2(worldX, worldY)));
        airPowerUp->GetComponent<HitboxComponent>()->SetCenter(airPowerUp->GetPosition());
        tiles.push_back(airPowerUp);
        return;
    }
    break;
    case TileType::GravityBox:
    {
        delete tile;
        GravityPowerUp* gravityPowerUp = new GravityPowerUp(nullptr, camera);
        gravityPowerUp->OnCreate();
        gravityPowerUp->SetPosition(PhysicsUtility::ToMeters(Vec2(worldX, worldY)));
        gravityPowerUp->GetComponent<HitboxComponent>()->SetCenter(gravityPowerUp->GetPosition());
        tiles.push_back(gravityPowerUp);
        return;
    }
    break;

    case TileType::RampTile:
    {
        delete tile;
        RotatingObstacle* ramp = new RotatingObstacle(nullptr, camera);
        ramp->OnCreate();
        ramp->SetPosition(PhysicsUtility::ToMeters(Vec2(worldX, worldY)));
        ramp->SetRotationSpeed(0.0f);  // Make it static
        ramp->SetDefaultAngle(45.0f);// Set initial angle for the ramp
        ramp->SetIsSpinning(false);

        tiles.push_back(ramp);
    
        
        return;
    }
    break;
    case TileType::MovingPlatformTile:
    {
        delete tile;
        MovingPlatform* movingPlatform = new MovingPlatform(nullptr, camera);
        movingPlatform->OnCreate();
        movingPlatform->SetPosition(PhysicsUtility::ToMeters(Vec2(worldX, worldY)));
        movingPlatform->GetComponent<HitboxComponent>()->SetCenter(movingPlatform->GetPosition());
        tiles.push_back(movingPlatform);

        return;
    }


    break;

    default:
        break;
    }

    // Add hitbox component
    Vec2 myVec = PhysicsUtility::ToMeters(Vec2(TILE_SIZE + 13, TILE_SIZE + 13));
    HitboxComponent* hitbox = new HitboxComponent(tile, myVec, Vec2(tile->GetPosition()));
    tile->AddComponent(hitbox);

    tiles.push_back(tile);

}

TileType TileMap::GetTileAt(int x, int y) const
{
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        return static_cast<TileType>(mapData[y][x]);
    }
    return TileType::Empty;
    
}

void TileMap::WorldToGrid(const Vec2& worldPos, int& gridX, int& gridY) const
{
    gridX = static_cast<int>(worldPos.x / TILE_SIZE);
    gridY = static_cast<int>(worldPos.y / TILE_SIZE);
}
