#pragma once
#include "Component.h"
#include "App/SimpleSprite.h"
#include "app\app.h"

//Wrapper class of a Simple Sprite so its coherent as a Actor Component System.
class SpriteComponent : public Component {
private:
    CSimpleSprite* sprite;
    float x, y;
public:
    SpriteComponent(Component* parent_);
    virtual ~SpriteComponent();

    bool LoadSprite(const char* filename, int columns = 1, int rows = 1);


    //Interfaces
    virtual bool OnCreate() override;
    virtual void OnDestroy() override;
    virtual void Update(const float deltaTime_) override;
    virtual void Render() const override;

    // Animation methods
    void CreateAnimation(unsigned int id, float speed, const std::vector<int>& frames);
    void SetAnimation(int id);
    void SetAnimation(int id, bool playFromStart);
    // Frame methods
    void SetFrame(unsigned int frame);

    // Color methods
    void SetColor(float r, float g, float b);

  

    // Getters
    float GetWidth() const;
    float GetHeight() const;
   

    // Transform Methods
    void SetPosition(float x, float y);
    void SetRotation(float angle);
    void SetScale(float scale);
    
    float GetRotation() const;
    float GetScale() const;

   // float GetPosition(float& x, float& y) const;



    CSimpleSprite* GetSprite() const;
    void SetSprite(CSimpleSprite* existingSprite);
};
