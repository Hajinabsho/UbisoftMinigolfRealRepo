#include "stdafx.h"
#include "Actor.h"


Actor::Actor(Component* parent_) :Component(parent_)
{
	posX = 0.0f;
	posY = 0.0f;
	rotation = 0.0f;
	scale = 1.0f;
}

Actor::~Actor() {}

bool Actor::OnCreate() { return true; }

void Actor::OnDestroy() {}

void Actor::Update(const float deltaTime_) {}

void Actor::Render() const {}

void Actor::AddComponent(Component* component_) {
	components.push_back(component_);
}

void Actor::RemoveComponent(Component* component_)
{
	std::vector<Component*>::iterator it = std::find(components.begin(), components.end(), component_);
	if (it != components.end()) {
		delete* it;
		components.erase(it);
	}
}

//Loop through the component vector and print out list of component
void Actor::ListComponents() const {
	for (auto c : components) {
		std::cout << typeid(*c).name() << std::endl;
	}
}