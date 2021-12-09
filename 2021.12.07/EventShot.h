#pragma once
#include "ShotBase.h"
class Transform;
class EventShot :
    public ShotBase
{
public:
    EventShot(SceneManager* manager, Transform* parent);
    void Update(void)override;
    float GetSpeed(void)override;
    float GetTimeAlive(void)override;

};

