#pragma once
#include <vector>
#include "SceneBase.h"
#include "Stage.h"
class SceneManager;
class SpaceDome;
class PlayerShip;
class RockManager;

class GameScene : public SceneBase
{

public:
	// 自機破壊時からのリスタート
	static constexpr float TIME_RESTART = 2.0f;

	GameScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	SpaceDome* spacedome_;
	Stage* stage_;
	PlayerShip* playership_;
	RockManager* rockmanager_;

	float stepshipdestroy_;
};
