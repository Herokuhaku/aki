#include "EventShot.h"
#include "SpriteAnimator.h"
#include "SceneManager.h"
#include "Camera.h"

EventShot::EventShot(SceneManager* manager, Transform* parent) :ShotBase(manager, parent)
{
}

void EventShot::Update(void)
{
    // ���e���G�t�F�N�g
    mExplosion->Update();

    if (!IsAlive()) {
        return;
    }

    // �ړ�����
    Move();

    VECTOR pos2D = ConvWorldPosToScreenPos(transform_.pos);
    if (pos2D.z <= 0.0f || pos2D.z >= 1.0f) {
        // �ʒu�𒲐�(�J�����ɉf��悤�ɁA���ɉ������Ă݂����ȍ��W)
        VECTOR velocity;
        velocity = VScale(VScale(dir_, -1.0f), 100.f);
        transform_.pos = VAdd(transform_.pos, velocity);
        transform_.Update();
        // �����G�t�F�N�g
        CreateExplosion();
    
        // �J������h�炷
        scenemanager_->GetCamera()->ChangeCameraMode(Camera::MODE::SHAKE);
    }

    transform_.Update();

}

float EventShot::GetSpeed(void)
{
    return 20.0f;
}

float EventShot::GetTimeAlive(void)
{
    return 10.0f;
}
