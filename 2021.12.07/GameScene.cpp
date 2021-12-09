#include <cmath>
#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "GameScene.h"
#include "SpaceDome.h"
#include "Stage.h"
#include "PlayerShip.h"
#include "RockManager.h"
#include "SpeechBalloon.h"

GameScene::GameScene(SceneManager* manager) : SceneBase(manager)
{
}

void GameScene::Init(void)
{
	playership_ = new PlayerShip(scenemanager_);
	playership_->Init();

	spacedome_ = new SpaceDome(scenemanager_,playership_->GetTransForm());
	spacedome_->Init();

	stage_ = new Stage(scenemanager_,playership_->GetTransForm());
	stage_->Init();

	scenemanager_->GetCamera()->ChangeCameraMode(Camera::MODE::SPRING);
	scenemanager_->GetCamera()->SetShip(playership_->GetTransForm());

	// �J�������[�h�̐ݒ�
	rockmanager_ = new RockManager(scenemanager_, playership_->GetTransForm());
	rockmanager_->Init();

	stepshipdestroy_ = 0.0f;
}

void GameScene::Update(void)
{
	spacedome_->Update();
	stage_->Update();
	playership_->Update();
	rockmanager_->Update();
	
	if (playership_->isDestroy()) {
		stepshipdestroy_ += scenemanager_->GetDeltaTime();
		if (stepshipdestroy_ > TIME_RESTART) {
			scenemanager_->ChangeScene(SceneManager::SCENE_ID::GAME, true);
		}
	}                        
	auto info = MV1CollCheck_Sphere(stage_->GetModelDungeon(), -1, playership_->GetTransForm()->pos, PlayerShip::COLLISION_RADIUS);
	if (info.Dim != nullptr) {
		playership_->Destroy();
	}
	MV1CollResultPolyDimTerminate(info);	// �V�[���J��
	if (keyTrgDown[KEY_SYS_START])
	{
		scenemanager_->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}
}

void GameScene::Draw(void)
{
	// �w�i & �s����
	spacedome_->Draw();

	// �w�i�I�u�W�F�N�g
	stage_->Draw();
	rockmanager_->Draw();

	// �L�����N�^�[�n
	playership_->Draw();

	// �G�t�F�N�g�n
	
	// 2D,UI�n
	playership_->GetSpeechBalloon()->Draw();
}

void GameScene::Release(void)
{
	spacedome_->Release();
	delete spacedome_;

	stage_->Release();
	delete stage_;

	playership_->Release();
	delete playership_;

	rockmanager_->Release();
	delete rockmanager_;
}
