#include "DxLib.h"
#include "GameCommon.h"
#include "Camera.h"
#include "AsoUtility.h"
#include "Transform.h"
#include "Quaternion.h"
#include "SceneManager.h"

Camera::Camera(SceneManager* manager)
{
	scenemanager_ = manager;
	Init();
}

Camera::~Camera()
{
}

void Camera::Init()
{
	ChangeCameraMode(MODE::FREE);
}

void Camera::SetDefault(void)
{

	// カメラの初期設定
	pos_ = DEFAULT_CAMERA_POS;
	targetpos_ = VAdd(pos_, RELATIVE_TARGET_POS);
	cameraup_ = { 0.0f, 1.0f, 0.0f };
	VECTOR axisDeg = { 35.0f,0.0f,0.0f };
	//// 回転
	//if (!AsoUtility::EqualsVZero(axisDeg)) {
	//	VECTOR axisRad;
	//	axisRad.x = AsoUtility::Deg2RadF(axisDeg.x);
	//	axisRad.y = AsoUtility::Deg2RadF(axisDeg.y);
	//	axisRad.z = AsoUtility::Deg2RadF(axisDeg.z);

	//	// クォータニオン(回転)の更新
	//	Quaternion axis = Quaternion::Euler(axisRad);
	//	mQuaRot = mQuaRot.Mult(axis);

	//	VECTOR localpos = mQuaRot.PosAxis(RELATIVE_TARGET_POS);
	//	mTargetPos = VAdd(mPos, localpos);

	//	mCameraUp = mQuaRot.GetUp();
	//	// カメラの上方向

	//}
	// カメラはX軸に傾いているが、この傾いた状態を傾き無しとする
	// mQuaRotは回転計算用で、
	// あくまで軸となるのは、カメラ座標と注視点とする
	mQuaRot = Quaternion();

}

void Camera::Update()
{

}

void Camera::SetBeforeDraw(void)
{

	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(50.0f, 25000.0f);

	switch (mode_) {
	case MODE::NONE:
		break;
	case MODE::FREE:
		SetBeforeDrawFree();
		break;
	case MODE::FIXED_POINT:
		SetBeforeDrawFixedPoint();
		break;
	case MODE::FOLLOW:
		SetBeforeDrawFollow();
		break;
	case MODE::SPRING:
		SetBeforeDrawFollowSpring();
		break;	
	case MODE::SHAKE:
		SetBeforeDrawShake();
		break;
	default:
		break;
	}

	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(
		pos_,
		targetpos_,
		cameraup_
	);



}

void Camera::SetBeforeDrawFree(void)
{
	VECTOR movedir = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_W)) {
		movedir = AsoUtility::DIR_F;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		movedir = AsoUtility::DIR_B;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		movedir = AsoUtility::DIR_L;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		movedir = AsoUtility::DIR_R;
	}

	VECTOR axisDeg = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_UP)) {
		axisDeg.x += -1.0f;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		axisDeg.x += 1.0f;
	}	
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		axisDeg.y += -1.0f;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		axisDeg.y += 1.0f;
	}

	// 回転
	if (!AsoUtility::EqualsVZero(axisDeg)) {
		VECTOR axisRad;
		axisRad.x = AsoUtility::Deg2RadF(axisDeg.x);
		axisRad.y = AsoUtility::Deg2RadF(axisDeg.y);
		axisRad.z = AsoUtility::Deg2RadF(axisDeg.z);
	
		// クォータニオン(回転)の更新
		Quaternion axis = Quaternion::Euler(axisRad);
		mQuaRot = mQuaRot.Mult(axis);

		VECTOR localpos = mQuaRot.PosAxis(RELATIVE_TARGET_POS);
		targetpos_ = VAdd(pos_,localpos);
	
		cameraup_ = mQuaRot.GetUp();
		// カメラの上方向
		
	}

	// 移動
	if (!AsoUtility::EqualsVZero(movedir)) {
		float speed = 30.0f;
		
		MATRIX mat = mQuaRot.ToMatrix();
		// 移動させたい方向
		VECTOR dir = VNorm(VTransform(movedir, mat));

		VECTOR movePow = VScale(dir, speed);

		pos_ = VAdd(pos_, movePow);
		targetpos_ = VAdd(targetpos_, movePow);
	}
}

void Camera::SetBeforeDrawFixedPoint(void)
{
}

void Camera::SetBeforeDrawFollow(void)
{
	// プレイヤーの座標
	VECTOR shippos = shiptransform_->pos;

	// プレイヤーの向き(回転)
	Quaternion shiprot = shiptransform_->quaRot;
	MATRIX shipmat = shiptransform_->matRot;

	//mPos = VAdd(shippos, RELATIVE_CAMERA_FOLLOW);

	VECTOR relativeCameraPos;
	// 行列計算
	relativeCameraPos = VTransform(RELATIVE_CAMERA_FOLLOW, shipmat);
	// クォータニオン
	//relativeCameraPos = shiprot.PosAxis(RELATIVE_CAMERA_FOLLOW);
	pos_ = VAdd(shippos, relativeCameraPos);

	VECTOR relativeTargetPos;
	relativeTargetPos = shiprot.PosAxis(RELATIVE_TARGET_POS);

	targetpos_ = VAdd(pos_, relativeTargetPos);

	//VECTOR relativeCameraUp;
	//relativeCameraUp = shiprot.PosAxis(RELATIVE_)
	//mCameraUp = 
	//mCameraUp = VTransform(AsoUtility::DIR_U, shipmat);
	cameraup_ = shiprot.PosAxis(AsoUtility::DIR_U);
	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(
		pos_,
		targetpos_,
		cameraup_
	);
	//
}

void Camera::SetBeforeDrawFollowSpring(void)
{
	// プレイヤー座標
	auto shippos = shiptransform_->pos;
	// プレイヤーの向き
	auto shiprot = shiptransform_->quaRot;
	// カメラの相対位置
	auto relativeCpos = shiprot.PosAxis(RELATIVE_CAMERA_SPRING);
	//バネの強さ(バネ定数)
	float POW_SPRING = 24.0f;
	float dampening = 2.0f * sqrt(POW_SPRING);

	//float delta = mSceneManager->GetDeltaTime();
	// deltaだとフレームで差が出たときに自機が揺れるため固定
	float delta = 0.016;
	// 理想位置
	auto idealpos = VAdd(shippos, relativeCpos);
	// 現在地と理想位置の差
	auto diff = VSub(pos_, idealpos);
	// バネの力((-バネの強さ * バネの伸び) - (抵抗 * カメラ速度))
	VECTOR force;
	force = VScale(diff, -POW_SPRING);
	force = VSub(force,VScale(velocity_,dampening));

	// カメラ速度を更新
	velocity_ = VAdd(velocity_,VScale(force,delta));

	// カメラ位置の更新
	pos_ = VAdd(pos_, VScale(velocity_, delta));

	// 自機の座標から回転
	VECTOR relativeTargetPos;
	relativeTargetPos = shiprot.PosAxis(RELATIVE_TARGET_POS);
	// 座標と回転座標を足す
	targetpos_ = VAdd(pos_, relativeTargetPos);

	cameraup_ = shiprot.PosAxis(AsoUtility::DIR_U);
	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(
		pos_,
		targetpos_,
		cameraup_
	);
}

void Camera::SetBeforeDrawShake(void)
{
	stepshake_ -= scenemanager_->GetDeltaTime();
	if (stepshake_ < 0.0f) {
		pos_ = defaultpos_;
		ChangeCameraMode(MODE::FIXED_POINT);
		return;
	}
	float pow = WIDTH_SHAKE * sinf(stepshake_ * SHAKE_SPEED);
	VECTOR vel = VScale(shakedir_, pow);
	pos_ = VAdd(defaultpos_, vel);
}

void Camera::Draw()
{
}

void Camera::DrawDebug(void)
{
}

void Camera::DrawUI(void)
{

	// 操作説明
	int x = 200;
	int y = 10;
	int addY = 40;
	DrawString(
		SCREEN_SIZE_X - x, y, "　【操作】", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　旋回：↑↓←→", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　加速：Ｂ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　発弾：Ｎ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　シーン遷移：Ｓｐａｃｅ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　1500m以上離れると", 0xffffff);
	y += 20;
	DrawString(
		SCREEN_SIZE_X - x, y, "　ゲームオーバー", 0xffffff);

}

void Camera::Release(void)
{
}

VECTOR Camera::GetPos(void)
{
	return pos_;
}

VECTOR Camera::GetTargetPos(void)
{
	return targetpos_;
}

VECTOR Camera::GetDir(void)
{
	return VNorm(VSub(targetpos_, pos_));
}

bool Camera::ChangeCameraMode(MODE mode)
{
	SetDefault();
	mode_ = mode;
	switch (mode_) {
	case MODE::NONE:
		break;
	case MODE::FREE:
		break;
	case MODE::FIXED_POINT:
		break;
	case MODE::FOLLOW:
		break;
	case MODE::SPRING:
		break;
	case MODE::SHAKE:
		stepshake_ = TIME_SHAKE;
		shakedir_ = VNorm(AsoUtility::DIR_R);
		defaultpos_ = pos_;
		break;
	default:
		break;
	}
	return true;
}

void Camera::SetShip(Transform* shiptransform)
{
	shiptransform_ = shiptransform;
}
