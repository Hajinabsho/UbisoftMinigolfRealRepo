#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(Component* parent_) :Actor(parent_)
{

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

    // Delete all tile actors and their components
    for (auto tile : tiles) {
        // Delete the sprite component
        auto spriteComponent = tile->GetComponent<SpriteComponent>();
        if (spriteComponent) {
            delete spriteComponent;
        }


        // Delete the tile actor itself
        delete tile;
    }

    // Clear the vector that holds the tiles
    tiles.clear();
}

void TileMap::Update(const float deltaTime_)
{
    for (const auto& tile : tiles)
    {
        if (tile) {
            tile->Update(deltaTime_);  // This will call render on all tile components including sprite
            tile->GetComponent<SpriteComponent>()->Update(deltaTime_);
        }
    }

}

void TileMap::Render() const
{
    // Render all tiles
    for (const auto& tile : tiles)
    {
        if (tile) {
            tile->Render();  // This will call render on all tile components including sprite
            tile->GetComponent<SpriteComponent>()->Render();
            tile->GetComponent<HitboxComponent>()->Render();
        }
    }



}

void TileMap::CreateTile(int x, int y, TileType type)
{
    Actor* tile = new Actor(this);
    //tile->SetPosition(x * TILE_SIZE, y * TILE_SIZE);

    float worldX = x * TILE_SIZE;
    float worldY = (MAP_HEIGHT - y - 1) * TILE_SIZE;  // Flip Y coordinate since your grid starts from top
    tile->SetPosition(worldX, worldY);


    // Add sprite component
    SpriteComponent* sprite = new SpriteComponent(tile);

    tile->AddComponent(sprite);

    // Load different sprites based on tile type
    switch (type) {
    case TileType::Ground:
        sprite->LoadSprite(".\\TestData\\Basic_Top.png", 1, 1);
        sprite->SetPosition(worldX, worldY);  // Use calculated position
        sprite->SetScale(0.1f);
        //sprite->SetPosition(400, 600);
        break;
    case TileType::Wall:
        sprite->LoadSprite(".\\TestData\\Basic_Right.png", 1, 1);
        sprite->SetPosition(worldX, worldY);  // Use calculated position
        sprite->SetScale(0.1f);
        //sprite->SetPosition(600, 400);
        break;
    default:
        break;
    }

    // Add hitbox component
    HitboxComponent* hitbox = new HitboxComponent(tile, Vec2(TILE_SIZE, TILE_SIZE), Vec2(0, 0));
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
