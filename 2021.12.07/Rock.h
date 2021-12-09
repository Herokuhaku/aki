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

	// ƒ‚ƒfƒ‹§Œä‚ÌŠî–{î•ñ
	Transform transform_;
};

