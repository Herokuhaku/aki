#include "PlayerShip.h"
#include "AsoUtility.h"
#include "ParticleGenerator.h"
#include "SpriteAnimator.h"
#include "SpeechBalloon.h"
#include "SceneManager.h"

PlayerShip::PlayerShip(SceneManager* manager)
{
	scenemanager_ = manager;
	Init();
}

void PlayerShip::Init(void)
{
	transform_.SetModel(MV1LoadModel("Model/PlayerShip/PlayerShip.mv1"));

	float scale = 10.0f;
	transform_.scl = { scale,scale,scale };
	//transform_.quaRot = Quaternion::Euler(0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f);
	transform_.quaRot = Quaternion::Euler(0.0f, AsoUtility::Deg2RadF(0.0f), 0.0f);
	transform_.quaRotLocal = Quaternion();
	transform_.pos = AsoUtility::VECTOR_ZERO;

	transform_.Update();

	//// �G�t�F�N�g
	particleganerator_ = new ParticleGenerator(scenemanager_, transform_.pos, 12.0f);

	explosion_ = new SpriteAnimator(scenemanager_, ResourceManager::SRC::SHIP_EXPLOSION,20.0f, 8.0f);

	speechbaloon_ = new SpeechBalloon(scenemanager_, SpeechBalloon::TYPE::SPEECH, &transform_);
	speechbaloon_->SetText("�ǂ���!");
	speechbaloon_->SetTime(15.0f);
	speechbaloon_->SetRelativePos({ 15.0f,15.0f,0.0f });
	// �������
	ChangeState(STATE::RUN);
}

void PlayerShip::Update(void)
{
	switch (state_) {
	case PlayerShip::STATE::RUN:
		UpdateRun();
		for (auto& shot : shots_) {
			shot->Update();
		}
		break;
	case PlayerShip::STATE::DESTROY:
		UpdateDestoroy();
		break;
	default:
		break;
	}
	Shot();


	// ���f������̊�{���X�V
	transform_.Update();
}

void PlayerShip::Draw(void)
{
	switch (state_) {
	case PlayerShip::STATE::RUN:
		MV1DrawModel(transform_.modelId);
		particleganerator_->Draw();
		for (auto& shot : shots_) {
			shot->Draw();
		}
		break;
	case PlayerShip::STATE::DESTROY:
		explosion_->Draw();
		break;
	}
	//MV1DrawModel(transform_.modelId);

	//particleganerator_->Draw();

	// �f�o�b�O
	//DrawSphere3D(transform_.pos, COLLISION_RADIUS, 10, 0xffffff, 0xffffff, false);
}

void PlayerShip::Release(void)
{
	MV1DeleteModel(transform_.modelId);
	
	particleganerator_->Release();
	delete particleganerator_;

	explosion_->Release();
	delete explosion_;
}

void PlayerShip::ProcessTurn(void)
{
	// �E����
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		Turn(SPEED_ROT_DEG_X,AsoUtility::AXIS_Y);
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		Turn(-SPEED_ROT_DEG_X, AsoUtility::AXIS_Y);
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		Turn(-SPEED_ROT_DEG_Y, AsoUtility::AXIS_X);
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		Turn(SPEED_ROT_DEG_Y, AsoUtility::AXIS_X);
	}
}

void PlayerShip::Turn(double deg, VECTOR axis)
{
	double rad = AsoUtility::Deg2RadD(deg);
	Quaternion tmpQ = Quaternion::AngleAxis(rad, axis);
	transform_.quaRot = transform_.quaRot.Mult(tmpQ);
}

void PlayerShip::Shot(void)
{
	if (shotflag_ && cooltime_ <= 0.0f) {
		shotflag_ = false;
		cooltime_ = 0.15f;
	}

	if (CheckHitKey(KEY_INPUT_N) && !shotflag_) {
		shotflag_ = true;
		shots_.emplace_back(new PlayerShot(scenemanager_,&transform_));		
		// �{�X����J�����ʒu�ւ̕���
		VECTOR dir = VNorm(transform_.GetForward());
		shots_[shots_.size()-1]->Create(transform_.pos, dir);
	}

	if (shotflag_) {
		cooltime_ -= scenemanager_->GetDeltaTime();
	}
}

void PlayerShip::UpdateRun(void)
{
	// ��]����
	ProcessTurn();

	VECTOR forward = transform_.GetForward();

	// �ړ�
	transform_.pos = VAdd(transform_.pos, VScale(forward, SPEED_MOVE));
	VECTOR tmp = VAdd(transform_.pos, VScale(transform_.GetForward(), 30.0f));
	particleganerator_->SetPos(tmp);
	particleganerator_->SetRot(transform_.GetBack());
	particleganerator_->Update();
}

void PlayerShip::UpdateDestoroy(void)
{
}

void PlayerShip::Destroy(void)
{
	ChangeState(STATE::DESTROY);
}

bool PlayerShip::isDestroy(void)
{
	return state_ == STATE::DESTROY;
}

Transform* PlayerShip::GetTransForm(void)
{
	return &transform_;
}

SpeechBalloon* PlayerShip::GetSpeechBalloon(void)
{
	return speechbaloon_;
}

std::vector<PlayerShot*> PlayerShip::GetShots(void)
{
	return shots_;
}

void PlayerShip::ChangeState(STATE state)
{
	state_ = state;
	switch (state_) {
	case PlayerShip::STATE::RUN:
		break;
	case PlayerShip::STATE::DESTROY:
		explosion_->Create(transform_.pos);
		break;
	}
}
