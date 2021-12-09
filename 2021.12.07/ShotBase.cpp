#include "GameCommon.h"
#include "AsoUtility.h"
#include "Quaternion.h"
#include "SceneManager.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "Resource.h"
#include "SpriteAnimator.h"
#include "ShotBase.h"

ShotBase::ShotBase(SceneManager* manager, Transform* parent)
{

	// 初期化系
	scenemanager_ = manager;
	mTransformParent = parent;
	mExplosion = new SpriteAnimator(
		manager, ResourceManager::SRC::SHOT_EXPLOSION, 20.0f, 8.0f);

	mIsAlive = false;

	// もし変動させたければ専用Getterを
	mCollisionRadius = 10.0f;

	// モデル制御の基本情報
	ResourceManager* rem = scenemanager_->GetResource();
	transform_.modelId = rem->LoadModelDuplicate(ResourceManager::SRC::SHOT_MODEL);
	float scale = 0.2f;
	transform_.scl = { scale, scale, scale };
	transform_.pos = mTransformParent->pos;
	transform_.quaRot = Quaternion();
	transform_.quaRotLocal = Quaternion::Euler(AsoUtility::Deg2RadF(90.0f), 0.0f, 0.0f);
	transform_.Update();

}

void ShotBase::Create(VECTOR birthPos, VECTOR dir)
{

	// 再利用可能なようにする

	// 指定方向に弾を飛ばす
	dir_ = dir;

	transform_.pos = birthPos;
	transform_.quaRot = Quaternion::LookRotation(dir_);

	// 生存系初期化
	mIsAlive = true;
	mStepAlive = GetTimeAlive();

}

void ShotBase::Update(void)
{

	// 着弾時のエフェクト
	mExplosion->Update();

	if (!CheckAlive())
	{
		return;
	}

	// 移動処理
	Move();

	// モデル制御の基本情報更新
	transform_.Update();

}

bool ShotBase::CheckAlive(void)
{

	// 生存時間
	mStepAlive -= scenemanager_->GetDeltaTime();
	if (mStepAlive < 0.0f)
	{
		mIsAlive = false;
	}

	return mIsAlive;

}

void ShotBase::Move(void)
{

	// 移動
	VECTOR velocity = VScale(dir_, GetSpeed());
	transform_.pos = VAdd(transform_.pos, velocity);

}

void ShotBase::Draw(void)
{

	mExplosion->Draw();

	if (!mIsAlive)
	{
		return;
	}

	MV1DrawModel(transform_.modelId);

}

void ShotBase::Release(void)
{
	mExplosion->Release();
	delete mExplosion;
	//MV1DeleteModel(mTransform.modelId);
}

float ShotBase::GetSpeed(void)
{
	return DEFAULT_SPEED;
}

float ShotBase::GetTimeAlive(void)
{
	return DEFAULT_TIME_ALIVE;
}

bool ShotBase::IsAlive(void)
{
	return mIsAlive;
}

void ShotBase::CreateExplosion(void)
{
	mIsAlive = false;
	mExplosion->Create(transform_.pos);
}

VECTOR ShotBase::GetPos(void)
{
	return transform_.pos;
}

float ShotBase::GetCollisionRadius(void)
{
	return mCollisionRadius;
}
