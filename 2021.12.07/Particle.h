#pragma once
#include <DxLib.h>
class SceneManager;
class Particle
{
public:
	Particle(SceneManager* manager, int img);
	void Generate(VECTOR pos,float size,VECTOR dir,float speed,float lifetime);
	void Update(void);
	void Draw(void);
	void Release(void);
	VECTOR GetPos(void) { return pos_; };
	void SetPos(VECTOR pos);
	float GetZLen(void);
	void SetZLen(float len);
	bool IsAlive(void);
private:
	SceneManager* scenemanager_;
	int imglight_;
	// À•W
	VECTOR pos_;
	// ‘å‚«‚³
	float size_;
	// ˆÚ“®•ûŒü
	VECTOR dir_;
	// ˆÚ“®‘¬“x
	float speed_;
	// ¶‘¶ŠÔ
	float lifetime_;

	float zLen_;
};

