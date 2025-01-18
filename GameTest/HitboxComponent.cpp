#include "stdafx.h"
#include "HitboxComponent.h"


HitboxComponent::HitboxComponent(Component* parent_, const Vec2& dimensions_, const Vec2& center_) : Component(parent_)
{
	center = center_;
	dimensions = dimensions_;
	isActive = true;
}

bool HitboxComponent::OnCreate()
{
	
	return true;
}

void HitboxComponent::OnDestroy()
{
}

void HitboxComponent::Update(const float deltaTime_)
{
}

void HitboxComponent::Render() const
{
    if (!isActive) return;

    // Get the parent actor's position
    Vec2 pos(0, 0);
    if (Actor* actor = static_cast<Actor*>(parent)) {
        pos = actor->GetPosition();
    }
    
    // Calculate corner positions
    float left = pos.x + center.x - dimensions.x / 2;
    float right = pos.x + center.x + dimensions.x / 2;
    float top = pos.y + center.y + dimensions.y / 2;
    float bottom = pos.y + center.y - dimensions.y / 2;

    // Draw the hitbox as a rectangle using lines
    // Draw in red color for better visibility
    App::DrawLine(left, top, right, top, 1.0f, 0.0f, 0.0f);      // Top line
    App::DrawLine(right, top, right, bottom, 1.0f, 0.0f, 0.0f);  // Right line
    App::DrawLine(right, bottom, left, bottom, 1.0f, 0.0f, 0.0f); // Bottom line
    App::DrawLine(left, bottom, left, top, 1.0f, 0.0f, 0.0f);    // Left line

    // Optionally, draw the center point
    float centerSize = 2.0f;
    float centerX = pos.x + center.x;
    float centerY = pos.y + center.y;
    App::DrawLine(centerX - centerSize, centerY, centerX + centerSize, centerY, 0.0f, 1.0f, 0.0f);  // Horizontal
    App::DrawLine(centerX, centerY - centerSize, centerX, centerY + centerSize, 0.0f, 1.0f, 0.0f);  // Vertical
}

bool HitboxComponent::CheckCollision(const HitboxComponent* other, const Vec2& myPos, const Vec2& otherPos) const
{
    //if isActive is false, or other is null or other isActive is false return false
    if (!isActive || !other || !other->GetIsActive()) return false;

    // Calculate actual positions including center offsets
    float myLeft = myPos.x + center.x - dimensions.x / 2;
    float myRight = myPos.x + center.x + dimensions.x / 2;
    float myTop = myPos.y + center.y + dimensions.y / 2;
    float myBottom = myPos.y + center.y - dimensions.y / 2;

    float otherLeft = otherPos.x + other->center.x - other->dimensions.x / 2;
    float otherRight = otherPos.x + other->center.x + other->dimensions.x / 2;
    float otherTop = otherPos.y + other->center.y + other->dimensions.y / 2;
    float otherBottom = otherPos.y + other->center.y - other->dimensions.y / 2;


	return !(myRight < otherLeft ||
        myLeft > otherRight ||
        myBottom > otherTop ||
        myTop < otherBottom);
}

void HitboxComponent::OnNotify(Actor& actor)
{
    std::cout << "Colliding!!" << '\n';
}


