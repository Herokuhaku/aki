#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Camera.h"
#include "TitleScene.h"
#include "SpaceDome.h"
#include "ParticleGenerator.h"
#include "TextScroll.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	mImgStartLogo = LoadGraph("Image/StartLogo.png");
	spacedome_ = new SpaceDome(scenemanager_, nullptr);
	spacedome_->Init();

	scenemanager_->GetCamera()->Init();
	text_ = new TextScroll(scenemanager_);
	text_->Init();
}//	particlegenerator = new ParticleGenerator(mSceneManager, {0,0,0},100);
//	particlegenerator->Init();
//}

void TitleScene::Update(void)
{

	// ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		scenemanager_->ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}
	spacedome_->Update();
	text_->Update();
	//particlegenerator->Update();
}

void TitleScene::Draw(void)
{
	spacedome_->Draw();
	//particlegenerator->Draw();
	// ƒƒS•`‰æ
	DrawLogo();
	text_->Draw();
}

void TitleScene::DrawLogo(void)
{

	int cx = SCREEN_SIZE_X / 2;
	int cy = SCREEN_SIZE_Y / 2;
	DrawRotaGraph(
		cx, cy - 200,
		1.0f, 0.0f, mImgStartLogo, true);

	char* msg = (char*)"Push Space";
	SetFontSize(28);
	int len = (int)strlen(msg);
	int width = GetDrawStringWidth(msg, len);
	DrawFormatString((SCREEN_SIZE_X / 2) - (width / 2), 200, 0x87cefa, msg);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetFontSize(16);
}

void TitleScene::Release(void)
{

	DeleteGraph(mImgStartLogo);
	spacedome_->Release();
	delete spacedome_;
}
