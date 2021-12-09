#pragma once
#include "DxLib.h"
#include "Quaternion.h"
#include "Transform.h"
class SceneManager;
class SpriteAnimator;

class ShotBase
{

public:

	// �R���X�g���N�^�EInit�ECreate�̋�ʂ���₱�����̂ŁA
	// Init����
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

	// ���f������̊�{���
	Transform transform_;

	// ���˕���
	VECTOR dir_;

	// ��������
	bool mIsAlive;
	float mStepAlive;

	// �����蔻��̔��a
	float mCollisionRadius;

private:

	static constexpr float DEFAULT_SPEED = 35.0f;
	static constexpr float DEFAULT_TIME_ALIVE = 10.0f;

};

