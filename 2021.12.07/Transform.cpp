#include "DxLib.h"
#include "Transform.h"

Transform::Transform(void)
{
	modelId = -1;
}

Transform::Transform(int model)
{
	modelId = model;
}

void Transform::Update(void)
{

	// 大きさ
	matScl = MGetScale(scl);

	// 回転
	rot = quaRot.ToEuler();
	matRot = quaRot.ToMatrix();

	// 位置
	matPos = MGetTranslate(pos);

	// 行列の合成
	MATRIX mat = MGetIdent();
	mat = MMult(mat, matScl);
	Quaternion q = quaRot.Mult(quaRotLocal);
	mat = MMult(mat, q.ToMatrix());
	mat = MMult(mat, matPos);

	// 行列をモデルに判定
	if (modelId != -1)
	{
		MV1SetMatrix(modelId, mat);
	}

}

void Transform::SetModel(int model)
{
	modelId = model;
}

VECTOR Transform::GetForward(void)
{
	return GetDir({ 0.0f, 0.0f, 1.0f });
}

VECTOR Transform::GetBack(void)
{
	return GetDir({ 0.0f, 0.0f, -1.0f });
}

VECTOR Transform::GetRight(void)
{
	return GetDir({ 1.0f, 0.0f, 0.0f });
}

VECTOR Transform::GetLeft(void)
{
	return GetDir({ -1.0f, 0.0f, 0.0f });
}

VECTOR Transform::GetUp(void)
{
	return GetDir({ 0.0f, 1.0f, 0.0f });
}

VECTOR Transform::GetDown(void)
{
	return GetDir({ 0.0f, -1.0f, 0.0f });
}

VECTOR Transform::GetDir(VECTOR vec)
{
	return VNorm(VTransform(vec, quaRot.ToMatrix()));
}
