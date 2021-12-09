#pragma once
#include <DxLib.h>
class SceneManager;
class Transform;
class Stage
{
public:
	static constexpr float RAD = 20.0f;
	static constexpr float RADIUS = 10000.0f;
	Stage(SceneManager* manager,Transform* player);
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawGrid(void);
	void Release(void);

	int GetModelDungeon(void) { return modeldungeon_; };
private:

	SceneManager* scenemanager_;
	Transform* player_;
	int modeldungeon_;
	int modelboss_;
	VECTOR posdoungeon_;
	VECTOR posboss_;
};

