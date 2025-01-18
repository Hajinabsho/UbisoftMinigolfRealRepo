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
    //center.print();

}

void HitboxComponent::Render() const
{

    if (!isActive) return;

    // Get the parent actor's position
    Vec2 pos(0, 0);
    if (Actor* actor = static_cast<Actor*>(parent)) {
        pos = PhysicsUtility::ToPixels(actor->GetPosition());
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

    if (!isActive || !other || !other->isActive)
    {
        return false;
    }

    // Calculate AABB min and max for this hitbox
    Vec2 minA = myPos + center - dimensions * 0.5f;
    Vec2 maxA = myPos + center + dimensions * 0.5f;

    // Calculate AABB min and max for the other hitbox
    Vec2 minB = otherPos + other->center - other->dimensions * 0.5f;
    Vec2 maxB = otherPos + other->center + other->dimensions * 0.5f;

    // AABB overlap check in 2D (no z-axis)
    return (minA.x <= maxB.x && maxA.x >= minB.x) &&  // Overlap in x-axis
        (minA.y <= maxB.y && maxA.y >= minB.y);    // Overlap in y-axis
}

void HitboxComponent::OnNotify(Actor& actor, Actor& otherActor)
{

    actor.OnCollision(actor , otherActor);

}


