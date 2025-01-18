#pragma once
#include "HitboxComponent.h"
#include "Actor.h"
#include "Subject.h"

class HitboxSystem : public Subject
{
	std::vector<Observer*> observers;
	std::vector<Actor*> actorsToCheck;


public:
	//virtual void OnNotify(const Actor& actor) override;

	//loopthrough all other actors to see if any other actor is colliding
	void updateActor(Actor& currentActor);


	// Add actor to collision checking list
	void RegisterActor(Actor* actor)
	{
		if (actor)
		{
			actorsToCheck.push_back(actor);
		}
	}

};


