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
	// ���W
	VECTOR pos_;
	// �傫��
	float size_;
	// �ړ�����
	VECTOR dir_;
	// �ړ����x
	float speed_;
	// ��������
	float lifetime_;

	float zLen_;
};

