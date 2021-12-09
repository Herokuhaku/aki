#pragma once
#include <vector>
#include "Transform.h"

class SceneManager;
class PlayerShip;
class Turret;
class EventShot;
class SpriteAnimator;

class BossShip
{
public:
	static constexpr float SPEED_MODE = 4.0f;
	static constexpr float TIME_EVENT = 4.0f;
	static constexpr float TIME_DESTROY = 10.0f;

	static constexpr COLOR_F FADE_C_FROM = { 1.0f, 1.0f, 1.0f, 1.0f };
	static constexpr COLOR_F FADE_C_TO = { 0.8f, 0.1f, 0.1f, 0.0f };

	// ���
	enum class STATE
	{
		NONE,
		EVENT,
		BATTLE,
		DESTROY,
		END
	};

	BossShip(SceneManager* manager, PlayerShip* player);
	void Init(void);
	void Update(void);
	void UpdateTurret(void);
	void Draw(void);
	void DrawTurret(void);
	void Release(void);

	void UpdateExplosion(void);
	void DrawExplosion(void);
	int GetModelID(void);

	inline Transform GetTranceform()
	{
		return mTransform;
	}

	inline std::vector<Turret*> GetTurrets()
	{
		return mTurrets;
	}

	// �{�X�̏��
	inline STATE GetState()
	{
		return mState;
	}

private:
	SceneManager* mSceneManager;

	// �v���C���[���
	PlayerShip* mPlayerShip;

	// ���f�����̊�{���
	Transform mTransform;

	// �C�x���g�e
	EventShot* mEventShot;
	float mEventTime;

	// �C��
	std::vector<Turret*> mTurrets;
	void MakeTurret(VECTOR localPos, VECTOR localAddAxis);

	// ���
	STATE mState;
	void ChangeState(STATE state);

	// ���ԊǗ��p
	float mDestroyTime;

	// �����G�t�F�N�g
	std::vector<SpriteAnimator*> mExplosions;
};
