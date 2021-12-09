#include "EventShot.h"
#include "SpriteAnimator.h"
#include "SceneManager.h"
#include "Camera.h"

EventShot::EventShot(SceneManager* manager, Transform* parent) :ShotBase(manager, parent)
{
}

void EventShot::Update(void)
{
    // 着弾時エフェクト
    mExplosion->Update();

    if (!IsAlive()) {
        return;
    }

    // 移動処理
    Move();

    VECTOR pos2D = ConvWorldPosToScreenPos(transform_.pos);
    if (pos2D.z <= 0.0f || pos2D.z >= 1.0f) {
        // 位置を調整(カメラに映るように、後ろに下がってみたいな座標)
        VECTOR velocity;
        velocity = VScale(VScale(dir_, -1.0f), 100.f);
        transform_.pos = VAdd(transform_.pos, velocity);
        transform_.Update();
        // 爆発エフェクト
        CreateExplosion();
    
        // カメラを揺らす
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
