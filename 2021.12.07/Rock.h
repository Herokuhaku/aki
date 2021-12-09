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

	// モデル制御の基本情報
	Transform transform_;
};

