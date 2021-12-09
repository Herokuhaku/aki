#pragma once
#include "DxLib.h"

class Quaternion
{

public:
	
	static constexpr float kEpsilonNormalSqrt = 1e-15F;

	double w;
	double x;
	double y;
	double z;	

	Quaternion(void);
	Quaternion(VECTOR rad);
	Quaternion(double w,double x, double y, double z);

	// オイラー角からクォータニオンへ変換
	static Quaternion Euler(VECTOR rad);
	static Quaternion Euler(double radX, double radY, double radZ);

	// クォータニオンの合成
	static Quaternion Mult(Quaternion q1, Quaternion q2);
	Quaternion Mult(Quaternion q);

	// 指定軸を指定角分、回転させる
	static Quaternion AngleAxis(double rad, VECTOR axis);

	// 座標を回転させる
	static VECTOR PosAxis(Quaternion q, VECTOR pos);
	VECTOR PosAxis(VECTOR pos);

	// クォータニオンからオイラー角へ変換
	static VECTOR ToEuler(Quaternion q);
	VECTOR ToEuler(void);

	// クォータニオンから行列へ変換
	static MATRIX ToMatrix(Quaternion q);
	MATRIX ToMatrix(void);

	// ベクトルからクォータニオンに変換
	static Quaternion LookRotation(VECTOR dir);

	// 行列からクォータニオンに変換
	static Quaternion GetRotation(MATRIX mat);

	// 基本ベクトルを取得
	VECTOR GetForward(void);
	VECTOR GetBack(void);
	VECTOR GetRight(void);
	VECTOR GetLeft(void);
	VECTOR GetUp(void);
	VECTOR GetDown(void);

	static float Dot(Quaternion q1, Quaternion q2);
	float Dot(Quaternion b);

	// 正規化
	Quaternion Normalized(void);
	void Normalize(void);

	// 逆クォータニオン
	Quaternion Inverse(void);

	// 球面補間
	static Quaternion Slerp(Quaternion from, Quaternion to, double t);


private:

	// 基本ベクトルを取得
	VECTOR GetDir(VECTOR dir);

	Quaternion operator*(float& rhs);
	const Quaternion operator*(const float& rhs);
	Quaternion operator+(Quaternion& rhs);
	const Quaternion operator+(const Quaternion& rhs);

};
