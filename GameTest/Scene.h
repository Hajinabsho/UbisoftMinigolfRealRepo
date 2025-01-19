#pragma once

///////////////////////////////////////////////////////////////////////////////
//Need something Better than GameTest haha But since I can't alter Main File (based on the email response),
// I will use gameTest scene as a Scene manager
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Shutdown() = 0;
    virtual bool IsVictoryConditionMet() = 0;
};
