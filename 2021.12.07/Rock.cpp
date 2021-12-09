#include "Rock.h"

Rock::Rock()
{
}

void Rock::Init(int modelid, VECTOR pos, VECTOR angle, VECTOR scale)
{
	transform_.modelId = modelid;
	transform_.pos = pos;
	transform_.quaRot = Quaternion::Euler(angle);
	transform_.quaRotLocal = Quaternion();
	transform_.rot = angle;
	transform_.scl = scale;
	transform_.Update();
}

void Rock::Update(void)
{
	transform_.Update();
}

void Rock::Draw(void)
{
	MV1DrawModel(transform_.modelId);
}

void Rock::Release(void)
{
}
