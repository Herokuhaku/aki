#pragma once
#include "ShotBase.h"
class TurretShot :
    public ShotBase
{
public:
    static constexpr float LIFE_TIME = 20.0f;
    TurretShot(SceneManager* manager, Transform* parent);
    void Init(VECTOR vec);
    void Update(void)override;
    float GetSpeed(void)override;
    float GetTimeAlive(void)override;
    void SetAliveFalse(void) { mIsAlive = false; };
private:
    VECTOR vec_;
    float time_;
};

