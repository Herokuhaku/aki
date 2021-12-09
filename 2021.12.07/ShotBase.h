#pragma once
#include "DxLib.h"
#include "Quaternion.h"
#include "Transform.h"
class SceneManager;
class SpriteAnimator;

class ShotBase
{

public:

	// コンストラクタ・Init・Createの区別がややこしいので、
	// Init無し
	ShotBase(SceneManager* manager, Transform* parent);

	virtual void Create(VECTOR birthPos, VECTOR dir);
	virtual void Update(void);
	virtual bool CheckAlive(void);
	virtual void Move(void);
	virtual void Draw(void);
	virtual void Release(void);
	virtual void CreateExplosion(void);

	virtual float GetSpeed(void);
	virtual float GetTimeAlive(void);

	bool IsAlive(void);
	VECTOR GetPos(void);
	float GetCollisionRadius(void);

protected:

	SceneManager* scenemanager_;
	SpriteAnimator* mExplosion;

	Transform* mTransformParent;

	// モデル制御の基本情報
	Transform transform_;

	// 発射方向
	VECTOR dir_;

	// 生存時間
	bool mIsAlive;
	float mStepAlive;

	// 当たり判定の半径
	float mCollisionRadius;

private:

	static constexpr float DEFAULT_SPEED = 35.0f;
	static constexpr float DEFAULT_TIME_ALIVE = 10.0f;

};

