#pragma once
#include "Transform.h"

class Rock
{
public:
	Rock();
	void Init(int modelid,VECTOR pos,VECTOR angle,VECTOR scale);
	void Update(void);
	void Draw(void);
	void Release(void);
private:

	// ���f������̊�{���
	Transform transform_;
};

