#pragma once
#include <chrono>
#include "TitleScene.h"
#include "GameScene.h"
class SceneBase;
class Fader;
class Camera;
class MiniCamera;
class ResourceManager;

class SceneManager
{

public:

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME,
		EVENT,
		BATTLE
	};

	void Init(void);
	void Init3D(void);
	void Update(void);
	void Release(void);

	void ChangeScene(SCENE_ID nextId, bool isFading);

	SCENE_ID GetSceneID(void);

	// デルタタイムの取得
	float GetDeltaTime(void);

	Camera* GetCamera(void);

	ResourceManager* GetResource(void);

private:

	SCENE_ID sceneid_;
	SCENE_ID waitsceneid_;

	SceneBase* scene_;
	Fader* fader_;
	Camera* camera_;
	MiniCamera* mMiniCamera;

	ResourceManager* resourcemanager_;

	bool mIsSceneChanging;

	// デルタタイム
	std::chrono::system_clock::time_point tickcount_;
	double deltatime_;

	void ResetDeltaTime(void);

	void DoChangeScene(void);

};