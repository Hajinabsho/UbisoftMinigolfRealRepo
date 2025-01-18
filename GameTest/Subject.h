#pragma once
#include "Observer.h"
#include <vector>

class Subject
{
private:
	std::vector<Observer*> observers;
	int numObservers;

public:
	void AddObserver(Observer* observer) {
		observers.push_back(observer);
	}
	void RemoveObserver(Observer* observer) {
		auto toRemove = std::find(observers.begin(), observers.end(), observer);
		observers.erase(toRemove);
		observers.shrink_to_fit();
	}

protected:
	void Notify(Actor& actor, Actor& otherActor)
	{
		//for (int i = 0; i < numObservers; i++)
		//{
		//	observers[i]->OnNotify(actor);
		//}

		for (auto* observer : observers)
		{
			observer->OnNotify(actor, otherActor);
		}
	}


};

