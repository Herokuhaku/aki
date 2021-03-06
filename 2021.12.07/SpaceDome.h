#pragma once
#include "Transform.h"
class SceneManager;

class SpaceDome
{
public:
	enum class STATE {
		STAY,
		FOLLOW,
	};
	SpaceDome(SceneManager* manager,Transform* trans);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	
	SceneManager* scenemanager_;
	// モデル制御の基本情報
	Transform transform_;


	void ChangeState(STATE state);
	Transform* shiptransform_;

	STATE mState;
};

