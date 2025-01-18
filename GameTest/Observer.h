#pragma once
#include "Actor.h"
class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(Actor& actor, Actor& otherActor) = 0;
};

