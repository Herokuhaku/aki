#pragma once
#include "DxLib.h"
#include "Quaternion.h"

// ifdef使いましょう！
#define IS_DEBUG false

// スクリーンサイズ
#define SCREEN_SIZE_X 1024
#define SCREEN_SIZE_Y 640

// 方向
enum class DIR
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
	MAX
};


///// <summary>
///// モデル制御の基本情報
///// 大きさ：VECTOR基準
///// 回転　：Quaternion基準
///// 位置　：VECTOR基準
///// </summary>
//struct Transform
//{
//
//	// 大きさ
//	VECTOR scl;
//	// 回転
//	VECTOR rot;
//	// 位置
//	VECTOR pos;
//
//	MATRIX matScl;
//	MATRIX matRot;
//	MATRIX matPos;
//
//	// 回転
//	Quaternion quaRot;
//	// ローカル回転
//	Quaternion quaRotLocal;
//
//};

