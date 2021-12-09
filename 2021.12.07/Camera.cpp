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

	// �J�����̏����ݒ�
	pos_ = DEFAULT_CAMERA_POS;
	targetpos_ = VAdd(pos_, RELATIVE_TARGET_POS);
	cameraup_ = { 0.0f, 1.0f, 0.0f };
	VECTOR axisDeg = { 35.0f,0.0f,0.0f };
	//// ��]
	//if (!AsoUtility::EqualsVZero(axisDeg)) {
	//	VECTOR axisRad;
	//	axisRad.x = AsoUtility::Deg2RadF(axisDeg.x);
	//	axisRad.y = AsoUtility::Deg2RadF(axisDeg.y);
	//	axisRad.z = AsoUtility::Deg2RadF(axisDeg.z);

	//	// �N�H�[�^�j�I��(��])�̍X�V
	//	Quaternion axis = Quaternion::Euler(axisRad);
	//	mQuaRot = mQuaRot.Mult(axis);

	//	VECTOR localpos = mQuaRot.PosAxis(RELATIVE_TARGET_POS);
	//	mTargetPos = VAdd(mPos, localpos);

	//	mCameraUp = mQuaRot.GetUp();
	//	// �J�����̏����

	//}
	// �J������X���ɌX���Ă��邪�A���̌X������Ԃ��X�������Ƃ���
	// mQuaRot�͉�]�v�Z�p�ŁA
	// �����܂Ŏ��ƂȂ�̂́A�J�������W�ƒ����_�Ƃ���
	mQuaRot = Quaternion();

}

void Camera::Update()
{

}

void Camera::SetBeforeDraw(void)
{

	// �N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
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

	// �J�����̐ݒ�
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

	// ��]
	if (!AsoUtility::EqualsVZero(axisDeg)) {
		VECTOR axisRad;
		axisRad.x = AsoUtility::Deg2RadF(axisDeg.x);
		axisRad.y = AsoUtility::Deg2RadF(axisDeg.y);
		axisRad.z = AsoUtility::Deg2RadF(axisDeg.z);
	
		// �N�H�[�^�j�I��(��])�̍X�V
		Quaternion axis = Quaternion::Euler(axisRad);
		mQuaRot = mQuaRot.Mult(axis);

		VECTOR localpos = mQuaRot.PosAxis(RELATIVE_TARGET_POS);
		targetpos_ = VAdd(pos_,localpos);
	
		cameraup_ = mQuaRot.GetUp();
		// �J�����̏����
		
	}

	// �ړ�
	if (!AsoUtility::EqualsVZero(movedir)) {
		float speed = 30.0f;
		
		MATRIX mat = mQuaRot.ToMatrix();
		// �ړ�������������
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
	// �v���C���[�̍��W
	VECTOR shippos = shiptransform_->pos;

	// �v���C���[�̌���(��])
	Quaternion shiprot = shiptransform_->quaRot;
	MATRIX shipmat = shiptransform_->matRot;

	//mPos = VAdd(shippos, RELATIVE_CAMERA_FOLLOW);

	VECTOR relativeCameraPos;
	// �s��v�Z
	relativeCameraPos = VTransform(RELATIVE_CAMERA_FOLLOW, shipmat);
	// �N�H�[�^�j�I��
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
	// �J�����̐ݒ�
	SetCameraPositionAndTargetAndUpVec(
		pos_,
		targetpos_,
		cameraup_
	);
	//
}

void Camera::SetBeforeDrawFollowSpring(void)
{
	// �v���C���[���W
	auto shippos = shiptransform_->pos;
	// �v���C���[�̌���
	auto shiprot = shiptransform_->quaRot;
	// �J�����̑��Έʒu
	auto relativeCpos = shiprot.PosAxis(RELATIVE_CAMERA_SPRING);
	//�o�l�̋���(�o�l�萔)
	float POW_SPRING = 24.0f;
	float dampening = 2.0f * sqrt(POW_SPRING);

	//float delta = mSceneManager->GetDeltaTime();
	// delta���ƃt���[���ō����o���Ƃ��Ɏ��@���h��邽�ߌŒ�
	float delta = 0.016;
	// ���z�ʒu
	auto idealpos = VAdd(shippos, relativeCpos);
	// ���ݒn�Ɨ��z�ʒu�̍�
	auto diff = VSub(pos_, idealpos);
	// �o�l�̗�((-�o�l�̋��� * �o�l�̐L��) - (��R * �J�������x))
	VECTOR force;
	force = VScale(diff, -POW_SPRING);
	force = VSub(force,VScale(velocity_,dampening));

	// �J�������x���X�V
	velocity_ = VAdd(velocity_,VScale(force,delta));

	// �J�����ʒu�̍X�V
	pos_ = VAdd(pos_, VScale(velocity_, delta));

	// ���@�̍��W�����]
	VECTOR relativeTargetPos;
	relativeTargetPos = shiprot.PosAxis(RELATIVE_TARGET_POS);
	// ���W�Ɖ�]���W�𑫂�
	targetpos_ = VAdd(pos_, relativeTargetPos);

	cameraup_ = shiprot.PosAxis(AsoUtility::DIR_U);
	// �J�����̐ݒ�
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

	// �������
	int x = 200;
	int y = 10;
	int addY = 40;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�y����z", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�@�@�@����F��������", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�@�@�@�����F�a", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�@�@�@���e�F�m", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�V�[���J�ځF�r��������", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@1500m�ȏ㗣����", 0xffffff);
	y += 20;
	DrawString(
		SCREEN_SIZE_X - x, y, "�@�Q�[���I�[�o�[", 0xffffff);

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
