#pragma once
#include "SceneBase.h"

class SceneManager;
class SpaceDome;
class RockManager;
class BossShip;
class PlayerShip;

class BattleScene : public SceneBase
{
public:
	// 自機破壊からのリスタート時間
	static constexpr float TIME_RESTART = 2.0f;

	static constexpr float TIME_RESTERT_BOSS_END = 5.0f;

	BattleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	SpaceDome* mSpaceDome;
	RockManager* mRockManager;
	BossShip* mBossShip;
	PlayerShip* mPlayerShip;

	float mStepShipDestroy;

	int mClearIm;
};