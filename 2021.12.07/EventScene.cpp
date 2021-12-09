#include "EventScene.h"
#include "SceneManager.h"
#include "Camera.h"
#include "BossShip.h"
#include "EventScene.h"
#include "SpaceDome.h"
#include "KeyCheck.h"

EventScene::EventScene(SceneManager* manager) :SceneBase(manager)
{
}

void EventScene::Init(void)
{
	// �J�������[�h�ύX
	scenemanager_->GetCamera()->ChangeCameraMode(Camera::MODE::FIXED_POINT);

	// �{�X
	bossship_ = new BossShip(scenemanager_,nullptr);
	bossship_->Init();

	// �X�y�[�X�h�[��
	spacedome_ = new SpaceDome(scenemanager_,nullptr);
	spacedome_->Init();

	// 
}

void EventScene::Update(void)
{
	//if (keyTrgDown[KEY_SYS_START])
	//{
	//	mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	//}
	spacedome_->Update();
	bossship_->Update();
}

void EventScene::Draw(void)
{
	spacedome_->Draw();
	bossship_->Draw();
}

void EventScene::Release(void)
{
	bossship_->Release();
	delete bossship_;

	spacedome_->Release();
	delete spacedome_;
}
