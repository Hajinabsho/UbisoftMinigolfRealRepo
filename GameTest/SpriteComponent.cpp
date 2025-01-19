#include "stdafx.h"
#include "SpriteComponent.h"
#include "Actor.h"


SpriteComponent::SpriteComponent(Component* parent_) : Component(parent_)
{
    sprite = nullptr;

}

SpriteComponent::~SpriteComponent() {
    OnDestroy();
}

bool SpriteComponent::LoadSprite(const char* filename, int columns, int rows) {
    if (sprite) {
        delete sprite;
    }
    sprite = App::CreateSprite(filename, columns, rows);
   

    return sprite != nullptr;
}

bool SpriteComponent::OnCreate() {


    return true;
}

void SpriteComponent::OnDestroy() {
    if (sprite) {
        delete sprite;
        sprite = nullptr;
    }
}

void SpriteComponent::Update(const float deltaTime_) {

    if (sprite) {
        sprite->Update(deltaTime_);
    }


    //if (!sprite) return;

    //// Update sprite transform from parent actor
    //if (Actor* actor = dynamic_cast<Actor*>(parent)) {
    //    Vec2 position = actor->GetPosition();
    //    sprite->SetPosition(position.x, position.y);
    //    sprite->SetAngle(actor->GetRotation());
    //    sprite->SetScale(actor->GetScale());
    //}
    //else {
    //    std::cout << "Actor Cast Faield Sprite Component" << '\n';
    //}

}

void SpriteComponent::Render() const 
{
    //now that I added Camera I need to offset the rendering pixle position of all object based on the camera
    Vec2 renderPos;
    if (Actor* actor = static_cast<Actor*>(parent)) 
    {
        //Physics position of the parent Actor
        Vec2 worldPos = actor->GetPosition(); 
        //if Camera exist, add the offset both are physics space
        if (actor->GetCamera()) {
            worldPos = worldPos + actor->GetCamera()->GetOffset();
            renderPos = PhysicsUtility::ToPixels(worldPos);
            sprite->SetPosition(renderPos.x, renderPos.y);
        }

        if (sprite)
        {
            sprite->Draw();
        }
        return;
    }

    if (sprite) 
    {
        sprite->Draw();
    }
    //sprite->Draw();
 
    //Old Code without Camera
    //if (sprite) {
    //    sprite->Draw();
    //}

}

void SpriteComponent::CreateAnimation(unsigned int id, float speed, const std::vector<int>& frames) {
    if (sprite) {
        sprite->CreateAnimation(id, speed, frames);
    }
}

void SpriteComponent::SetAnimation(int id) {
    if (sprite) {
        sprite->SetAnimation(id);
    }
}

void SpriteComponent::SetAnimation(int id, bool playFromStart) {
    if (sprite) {
        sprite->SetAnimation(id, playFromStart);
    }
}

void SpriteComponent::SetColor(float r, float g, float b) {
    if (sprite) {
        sprite->SetColor(r, g, b);
    }
}

void SpriteComponent::SetFrame(unsigned int frame) {
    if (sprite) {
        sprite->SetFrame(frame);
    }
}

float SpriteComponent::GetWidth() const {
    return sprite ? sprite->GetWidth() : 0.0f;
}

void SpriteComponent::SetPosition(float x, float y)
{
    if (sprite) {
        sprite->SetPosition(x, y);
    }
}

void SpriteComponent::SetRotation(float angle)
{
    if (sprite) {
        sprite->SetAngle(angle);
    }
}

void SpriteComponent::SetScale(float scale)
{
    if (sprite) {
        sprite->SetScale(scale);
    }
}

float SpriteComponent::GetHeight() const {
    return sprite ? sprite->GetHeight() : 0.0f;
}

float SpriteComponent::GetRotation() const
{
    return sprite->GetAngle();
}

float SpriteComponent::GetScale() const
{
    return sprite->GetScale();
}

//void SpriteComponent::GetPosition(float& x, float& y) const
//{
//    sprite->GetPosition(x, y);
//}

CSimpleSprite* SpriteComponent::GetSprite() const {
    return sprite;
}

void SpriteComponent::SetSprite(CSimpleSprite* existingSprite)
{
    if (sprite != nullptr && sprite != existingSprite) 
    {
          delete sprite;  // Delete old sprite if it exists and is different
    }
    sprite = existingSprite;  // Point to the existing sprite
}
