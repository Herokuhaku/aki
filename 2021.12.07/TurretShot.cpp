#include "TurretShot.h"
#include "Transform.h"
#include "SpriteAnimator.h"
#include "SceneManager.h"
#include "Camera.h"
TurretShot::TurretShot(SceneManager* manager, Transform* parent) :ShotBase(manager, parent)
{
}

void TurretShot::Init(VECTOR vec)
{
    vec_ = vec;
    time_ = 0.0f;
}

void TurretShot::Update(void)
{
    time_ += scenemanager_->GetDeltaTime();
    if (time_ > LIFE_TIME) {
        mIsAlive = false;
    }
    // ���e���G�t�F�N�g
    mExplosion->Update();
    if (!IsAlive()) {
        return;
    }

    // �ړ�����
    Move();

    transform_.Update();
}

float TurretShot::GetSpeed(void)
{
    return 20.0f;
}

float TurretShot::GetTimeAlive(void)
{
    return 10.0f;
}
