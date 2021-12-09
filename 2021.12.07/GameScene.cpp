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

	// カメラモードの設定
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
	MV1CollResultPolyDimTerminate(info);	// シーン遷移
	if (keyTrgDown[KEY_SYS_START])
	{
		scenemanager_->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}
}

void GameScene::Draw(void)
{
	// 背景 & 不透明
	spacedome_->Draw();

	// 背景オブジェクト
	stage_->Draw();
	rockmanager_->Draw();

	// キャラクター系
	playership_->Draw();

	// エフェクト系
	
	// 2D,UI系
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
