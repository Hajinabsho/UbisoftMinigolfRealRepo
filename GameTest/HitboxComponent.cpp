#include "stdafx.h"
#include "HitboxComponent.h"


bool HitboxComponent::CheckBoxBox(const HitboxComponent* other, const Vec2& myPos, const Vec2& otherPos) const
{
    ////AABB
    ////Compare min and max bound of x and y of two boxes and check overlap
    Vec2 myMin = myPos + center - dimensions * 0.5f;
    Vec2 myMax = myPos + center + dimensions * 0.5f;
    Vec2 otherMin = otherPos + other->center - other->dimensions * 0.5f;
    Vec2 otherMax = otherPos + other->center + other->dimensions * 0.5f;

    return (myMin.x <= otherMax.x && myMax.x >= otherMin.x &&
    myMin.y <= otherMax.y && myMax.y >= otherMin.y);

}

bool HitboxComponent::CheckSphereSphere(const HitboxComponent* other, const Vec2& myPos, const Vec2& otherPos) const
{
    //Circle are easier, compare the distance between centers with the sum of their Radius
    Vec2 diff = (myPos + center) - (otherPos + other->center);
    float distance = VectorMath::mag(diff);
    return distance < (radius + other->radius);

}

bool HitboxComponent::CheckSphereBox(const HitboxComponent* sphere, const HitboxComponent* box, const Vec2& spherePos, const Vec2& boxPos) const
{
    //Spehre and Box
    //Find closest point from the box to the circle and compare with the radius
    
    Vec2 boxCenter = boxPos + box->center;
    Vec2 circleCenter = spherePos + sphere->center;

    // Transform circle's center into box's local space (undo rotation)
    float cosa = cos(-box->angle);  // Negative angle to undo rotation
    float sina = sin(-box->angle);

    // Translate circle to origin relative to box center
    Vec2 localCirclePos;
    localCirclePos.x = cosa * (circleCenter.x - boxCenter.x) - sina * (circleCenter.y - boxCenter.y);
    localCirclePos.y = sina * (circleCenter.x - boxCenter.x) + cosa * (circleCenter.y - boxCenter.y);

    // Find closest point in box space (now aligned with axes)
    Vec2 closest;
    closest.x = localCirclePos.x;
    if (localCirclePos.x < -box->dimensions.x / 2) {
        closest.x = -box->dimensions.x / 2;
    }
    else if (localCirclePos.x > box->dimensions.x / 2) {
        closest.x = box->dimensions.x / 2;
    }

    closest.y = localCirclePos.y;
    if (localCirclePos.y < -box->dimensions.y / 2) {
        closest.y = -box->dimensions.y / 2;
    }
    else if (localCirclePos.y > box->dimensions.y / 2) {
        closest.y = box->dimensions.y / 2;
    }

    // Get distance in local space
    Vec2 diff = localCirclePos - closest;

    // No need to transform back to world space for distance comparison
    return VectorMath::mag(diff) < sphere->radius;
}

HitboxComponent::HitboxComponent(Component* parent_, const Vec2& dimensions_, const Vec2& center_) : Component(parent_)
{
	center = center_;
	dimensions = dimensions_;
	isActive = true;
    radius = 0.0f;
    colliderType = ColliderType::Box;
}

HitboxComponent::HitboxComponent(Component* parent_, float radius_, const Vec2& center_) : Component(parent_)
{
    center = center_;
    dimensions = Vec2(0.0f,0.0f);
    isActive = true;
    radius = radius_;
    colliderType = ColliderType::Sphere;
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
        Vec2 worldPos = actor->GetPosition();

        // Apply camera offset if it exists
        if (actor->GetCamera()) {
            worldPos = worldPos + actor->GetCamera()->GetOffset();
        }

        pos = PhysicsUtility::ToPixels(worldPos);
    }

    if (angle == 0) {
        Vec2 pixelDimensions = PhysicsUtility::ToPixels(dimensions);

        // Calculate corner positions
        float left = pos.x - pixelDimensions.x / 2;
        float right = pos.x + pixelDimensions.x / 2;
        float top = pos.y + pixelDimensions.y / 2;
        float bottom = pos.y - pixelDimensions.y / 2;

        // Draw the hitbox as a rectangle using lines. Red Color
        App::DrawLine(left, top, right, top, 1.0f, 0.0f, 0.0f);      // Top line
        App::DrawLine(right, top, right, bottom, 1.0f, 0.0f, 0.0f);  // Right line
        App::DrawLine(right, bottom, left, bottom, 1.0f, 0.0f, 0.0f); // Bottom line
        App::DrawLine(left, bottom, left, top, 1.0f, 0.0f, 0.0f);    // Left line
    }
    //For Rotated hitbox
    else {
        Vec2 pixelDimensions = PhysicsUtility::ToPixels(dimensions);

        Vec2 corners[4];
        float halfWidth = pixelDimensions.x * 0.5f;
        float halfHeight = pixelDimensions.y * 0.5f;
        float cosa = cos(angle);
        float sina = sin(angle);

        // Calculate four corners
        corners[0] = Vec2(pos.x + (-halfWidth * cosa - -halfHeight * sina),
            pos.y + (-halfWidth * sina + -halfHeight * cosa));
        corners[1] = Vec2(pos.x + (halfWidth * cosa - -halfHeight * sina),
            pos.y + (halfWidth * sina + -halfHeight * cosa));
        corners[2] = Vec2(pos.x + (halfWidth * cosa - halfHeight * sina),
            pos.y + (halfWidth * sina + halfHeight * cosa));
        corners[3] = Vec2(pos.x + (-halfWidth * cosa - halfHeight * sina),
            pos.y + (-halfWidth * sina + halfHeight * cosa));



        // Draw lines between corners
        App::DrawLine(corners[0].x, corners[0].y, corners[1].x, corners[1].y, 1.0f, 0.0f, 0.0f);
        App::DrawLine(corners[1].x, corners[1].y, corners[2].x, corners[2].y, 1.0f, 0.0f, 0.0f);
        App::DrawLine(corners[2].x, corners[2].y, corners[3].x, corners[3].y, 1.0f, 0.0f, 0.0f);
        App::DrawLine(corners[3].x, corners[3].y, corners[0].x, corners[0].y, 1.0f, 0.0f, 0.0f);
    }




    //if (!isActive) return;

    //// Get the parent actor's position
    //Vec2 pos(0, 0);
    //if (Actor* actor = static_cast<Actor*>(parent)) {
    //    pos = PhysicsUtility::ToPixels(actor->GetPosition());
    //}
    //
    ////pos.print();
    //Vec2 pixelDimensions(dimensions.x, dimensions.y);

    //pixelDimensions = PhysicsUtility::ToPixels(pixelDimensions);

    ////// Calculate corner positions
    ////float left = pos.x + center.x - dimensions.x / 2;
    ////float right = pos.x + center.x + dimensions.x / 2;
    ////float top = pos.y + center.y + dimensions.y / 2;
    ////float bottom = pos.y + center.y - dimensions.y / 2;

    //// Calculate corner positions
    //float left = pos.x  - pixelDimensions.x / 2;
    //float right = pos.x  + pixelDimensions.x / 2;
    //float top = pos.y  + pixelDimensions.y / 2;
    //float bottom = pos.y  - pixelDimensions.y / 2;

    //// Draw the hitbox as a rectangle using lines
    //// Draw in red color for better visibility
    //App::DrawLine(left, top, right, top, 1.0f, 0.0f, 0.0f);      // Top line
    //App::DrawLine(right, top, right, bottom, 1.0f, 0.0f, 0.0f);  // Right line
    //App::DrawLine(right, bottom, left, bottom, 1.0f, 0.0f, 0.0f); // Bottom line
    //App::DrawLine(left, bottom, left, top, 1.0f, 0.0f, 0.0f);    // Left line


}

bool HitboxComponent::CheckCollision(const HitboxComponent* other, const Vec2& myPos, const Vec2& otherPos) const
{

    //if (!isActive || !other || !other->isActive)
    //{
    //    return false;
    //}

    //// Calculate AABB min and max for this hitbox
    //Vec2 minA = myPos + center - dimensions * 0.5f;
    //Vec2 maxA = myPos + center + dimensions * 0.5f;

    //// Calculate AABB min and max for the other hitbox
    //Vec2 minB = otherPos + other->center - other->dimensions * 0.5f;
    //Vec2 maxB = otherPos + other->center + other->dimensions * 0.5f;

    //// AABB overlap check in 2D (no z-axis)
    //return (minA.x <= maxB.x && maxA.x >= minB.x) &&  // Overlap in x-axis
    //    (minA.y <= maxB.y && maxA.y >= minB.y);    // Overlap in y-axis
    
    //Now I'm gonna have to check for both sphere and box
    if (colliderType == ColliderType::Box && other->colliderType == ColliderType::Box) {
        return CheckBoxBox(other, myPos, otherPos);
    }
    else if (colliderType == ColliderType::Sphere && other->colliderType == ColliderType::Sphere) {
        return CheckSphereSphere(other, myPos, otherPos);
    }
    else if (colliderType == ColliderType::Sphere) {
        return CheckSphereBox(this, other, myPos, otherPos);
    }
    else {
        return CheckSphereBox(other, this, otherPos, myPos);
    }
}

void HitboxComponent::OnNotify(Actor& actor, Actor& otherActor)
{

    actor.OnCollision(actor , otherActor);

}


