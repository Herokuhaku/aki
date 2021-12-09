#pragma once
#include "DxLib.h"
#include "ResourceManager.h"
class SceneManager;

class SpriteAnimator
{

public:

	static constexpr int CNT_ANIM = 7;
	static constexpr float SPEED_ANIM = 8.0f;

	enum class STATE
	{
		NONE,
		PLAY,
		END
	};

	// コンストラクタ・Init・Createの区別がややこしいので、
	// Init無し
	SpriteAnimator(SceneManager* manager, ResourceManager::SRC src, int size, float speed);

	void Create(VECTOR pos);
	void Update(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos(void);
	void SetPos(VECTOR pos);

	float GetZLen(void);
	void SetZLen(float len);

	bool IsEnd(void);

private:

	SceneManager* mSceneManager;

	// 状態
	STATE mState;

	// 画像ハンドル
	int* mImages;

	// 再生インデックス
	int mIdxAnim;

	// 座標
	VECTOR mPos;

	// 角度
	VECTOR mAngles;

	// 大きさ
	float mSize;

	// アニメーション用更新ステップ
	float mStepAnim;

	// カメラからのZ距離
	float mZLen;

	// 総アニメーション数
	int mCntTotalAnim;

	// アニメーションスピード
	float mSpeedAnim;

	// 状態遷移
	void ChangeState(STATE state);

};
