#include "stdafx.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "app\app.h"

SpriteComponent::SpriteComponent(Component* parent_) :
    Component(parent_),
    sprite(nullptr) {
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
    if (!sprite) return;

    // Update sprite transform from parent actor
    if (Actor* actor = dynamic_cast<Actor*>(parent)) {
        float x, y;
        actor->GetPosition(x, y);
        sprite->SetPosition(x, y);
        sprite->SetAngle(actor->GetRotation());
        sprite->SetScale(actor->GetScale());
    }

    sprite->Update(deltaTime_);
}

void SpriteComponent::Render() const {
    if (sprite) {
        sprite->Draw();
    }
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

float SpriteComponent::GetHeight() const {
    return sprite ? sprite->GetHeight() : 0.0f;
}

CSimpleSprite* SpriteComponent::GetSprite() const {
    return sprite;
}