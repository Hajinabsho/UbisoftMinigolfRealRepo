#include "stdafx.h"
#include "HitboxSystem.h"
#include "iostream"

void HitboxSystem::updateActor(Actor& currentActor)
{
   
    auto currentHitbox = currentActor.GetComponent<HitboxComponent>();
    if (!currentHitbox || !currentHitbox->GetIsActive()) return;

    // Check against all registered actors
    for (Actor* otherActor : actorsToCheck) {
        // Don't check against self
        if (otherActor == &currentActor) continue;

        auto otherHitbox = otherActor->GetComponent<HitboxComponent>();
        if (!otherHitbox || !otherHitbox->GetIsActive()) continue;

        // Get positions for collision check
        Vec2 currentPos = currentActor.GetPosition();
       // currentPos.print();

        Vec2 otherPos = otherActor->GetPosition();
        //std::cout << "other Actor ";
        //otherPos.print();

        //std::cout << "my location: " , currentPos.print();

        // Check collision
        if (currentHitbox->CheckCollision(otherHitbox, currentPos, otherPos)) {
            // Collision detected! Notify the HitboxComponents
            Notify(currentActor, *otherActor);  // Notify about currentActor collision

            //Notify(*otherActor);   // Notify about otherActor collision Now that I think of only Golfball might require physics so comment out the other actor
        }

    }
}
