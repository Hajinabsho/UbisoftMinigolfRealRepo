#pragma once
#include "Component.h"
#include "vector"
#include "iostream"

class Actor : public Component
{
private:
	std::vector<Component*> components;

	// Transform data. Didn't create transform component as the scope of the project won't have any actor without position info
	float posX, posY;
	float rotation;    // in radians
	float scale;

public:
	//Must have Parent
	Actor() = delete;
	Actor(Component* parent_);
	virtual ~Actor();


	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void Render()const override;

	void AddComponent(Component* component_);
	void RemoveComponent(Component* component_);
	void ListComponents()const;

	// Transform methods
	void SetPosition(float x_, float y_) { posX = x_; posY = y_; }
	void GetPosition(float& x_, float& y_) const { x_ = posX; y_ = posY; }
	void SetRotation(float rotation_) { rotation = rotation_; }
	float GetRotation() const { return rotation; }
	void SetScale(float scale_) { scale = scale_; }
	float GetScale() const { return scale; }




	//Need Template for a get component function
	template <typename T>
	T* GetComponent() {
		for (auto c : components) {
			// Use dynamic_cast for safe type compatibility
			if (auto result = dynamic_cast<T*>(c)) {
				return result;
			}
		}
		return nullptr;
	}
};

