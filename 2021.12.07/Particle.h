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
	// 座標
	VECTOR pos_;
	// 大きさ
	float size_;
	// 移動方向
	VECTOR dir_;
	// 移動速度
	float speed_;
	// 生存時間
	float lifetime_;

	float zLen_;
};

