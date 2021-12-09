#pragma once
#include <vector>
#include "Transform.h"
#include "PlayerShot.h"
class SpriteAnimator;
class SceneManager;
class ParticleGenerator;
class SpeechBalloon;

class PlayerShip
{
public:
	// 移動スピード
	static constexpr float SPEED_MOVE = 10.0f;

	// 自機の回転量
	static constexpr float SPEED_ROT_DEG_X = 1.0f;
	static constexpr float SPEED_ROT_DEG_Y = 1.0f;

	static constexpr float COLLISION_RADIUS = 20.0f;

	enum class STATE {
		NONE,RUN,DESTROY
	};
	PlayerShip(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	
	// 操作
	void ProcessTurn(void);
	void Turn(double deg,VECTOR axis);
	void Shot(void);
	// 破壊系
	void UpdateRun(void);
	void UpdateDestoroy(void);
	// 自機破壊
	void Destroy(void);
	// 生存確認
	bool isDestroy(void);

	Transform* GetTransForm(void);

	SpeechBalloon* GetSpeechBalloon(void);

	std::vector<PlayerShot*> GetShots(void);
private:
	ParticleGenerator* particleganerator_;
	SceneManager* scenemanager_;
	// モデル制御の基本情報
	Transform transform_;
	SpriteAnimator* explosion_;

	STATE state_;
	SpeechBalloon* speechbaloon_;
	void ChangeState(STATE state);

	std::vector<PlayerShot*> shots_;

	float cooltime_;
	bool shotflag_;
};

