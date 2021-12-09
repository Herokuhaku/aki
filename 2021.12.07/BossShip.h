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

	// 状態
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

	// ボスの状態
	inline STATE GetState()
	{
		return mState;
	}

private:
	SceneManager* mSceneManager;

	// プレイヤー情報
	PlayerShip* mPlayerShip;

	// モデル情報の基本情報
	Transform mTransform;

	// イベント弾
	EventShot* mEventShot;
	float mEventTime;

	// 砲台
	std::vector<Turret*> mTurrets;
	void MakeTurret(VECTOR localPos, VECTOR localAddAxis);

	// 状態
	STATE mState;
	void ChangeState(STATE state);

	// 時間管理用
	float mDestroyTime;

	// 爆発エフェクト
	std::vector<SpriteAnimator*> mExplosions;
};
