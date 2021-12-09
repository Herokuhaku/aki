#pragma once
#include <DxLib.h>
#include <vector>
#include "Quaternion.h"

class SceneManager;
class Particle;
class ParticleGenerator
{
public:
	static constexpr int NUM_POLYGON = 10;
	static constexpr int SPLIT_ANGLE_DEG = 360 / NUM_POLYGON;
	static constexpr int PARTICLE= 30;

	static constexpr float GEN_MIN_SIZE = 5.0f;
	static constexpr float GEN_MAX_SIZE = 10.0f;

	static constexpr float GEN_MIN_SPEED = 10.0f;
	static constexpr float GEN_MAX_SPEED = 20.0f;

	static constexpr float GEN_MIN_LIFE = 1.0f;
	static constexpr float GEN_MAX_LIFE = 3.0f;
	ParticleGenerator(SceneManager* manager,VECTOR pos,float radius);
	void Init();
	void Update(void);
	void Draw(void);
	void DebugProcess(void);
	void DrawMeshSquare(void);
	void DrawMeshCircle(void);
	void Release(void);

	void SetPos(VECTOR pos);
	void SetRot(Quaternion rot);
private:
	// 座標
	VECTOR pos_;

	Quaternion quarot_;
	// 半径
	float radius_;
	// ポリゴンデータ
	VERTEX3D verticesSquare_[6];
	// ポリゴンデータ　円形
	//VERTEX3D vericesCircle[11];
	VERTEX3D verticesCircle_[NUM_POLYGON+1];
	// 頂点インデックス
	WORD indexs_[NUM_POLYGON * 3];

	Particle* Generate(Particle* particle);
	
	void CreateMeshSquare(void);
	void CreateMeshCircle(void);
	SceneManager* scenemanager_;

	int imglight_;
	std::vector<Particle*> particles_;
};

