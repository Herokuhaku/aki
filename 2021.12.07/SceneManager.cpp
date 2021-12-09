#include <chrono>
#include "DxLib.h"
#include "Fader.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "EventScene.h"
#include "BattleScene.h"

void SceneManager::Init()
{

	sceneid_ = SCENE_ID::GAME;
	waitsceneid_ = SCENE_ID::NONE;

	fader_ = new Fader();
	fader_->Init();

	camera_ = new Camera(this);
	camera_->Init();

	resourcemanager_ = new ResourceManager();
	resourcemanager_->Init();

	scene_ = new TitleScene(this);
	scene_->Init();

	mIsSceneChanging = false;

	// デルタタイム
	tickcount_ = std::chrono::system_clock::now();

	// 3D用の設定
	Init3D();

}

void SceneManager::Init3D(void)
{

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	//SetCameraNearFar(0.0f, 50.0f);

	// ライトの設定
	//ChangeLightTypeDir({ 0.0f, -1.0f, 0.0f });
	SetUseLighting(false);

	// 背景色設定
	SetBackgroundColor(0, 0, 0);
	//SetBackgroundColor(0, 100, 100);

	// カメラ設定
	// 初期状態では視点の位置が、 
	// x = 320.0f, y = 240.0f, z = (画面のサイズによって変化)
	// 注視点の位置は、
	// x = 320.0f, y = 240.0f, z = 1.0f、
	// カメラの上方向は
	// x = 0.0f, y = 1.0f, z = 0.0f
	// つまり画面のＸＹ平面上の中心に居てＺ軸のプラス方向を見るようなカメラになっています。
	//SetCameraPositionAndAngle(
	//	{ 0.0f, 200, -500.0f },
	//	30.0f * (DX_PI_F / 180.0f), 0.0f, 0.0f
	//);

	// フォグの設定
	SetFogEnable(true);
	SetFogColor(0,0,20);
	SetFogStartEnd(5000.0f, 15000.0f);
}

void SceneManager::Update(void)
{

	if (scene_ == nullptr)
	{
		return;
	}

	// デルタタイム
	auto tickCount = std::chrono::system_clock::now();
	deltatime_ = std::chrono::duration_cast<std::chrono::nanoseconds>(tickCount - tickcount_).count() / 1000000000.0f;
	tickcount_ = tickCount;

	fader_->Update();

	// カメラ更新ステップ
	camera_->Update();

	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面を初期化
	ClearDrawScreen();
	if (mIsSceneChanging)
	{
		Fader::FADE_STATE fState = fader_->GetState();
		switch (fState)
		{
		case Fader::FADE_STATE::FADE_IN:
			if (fader_->IsEnd())
			{
				fader_->SetFade(Fader::FADE_STATE::NONE);
				mIsSceneChanging = false;
			}
			break;
		case Fader::FADE_STATE::FADE_OUT:
			if (fader_->IsEnd())
			{
				DoChangeScene();
				fader_->SetFade(Fader::FADE_STATE::FADE_IN);
			}
			break;
		default:
			break;
		}
	}
	else 
	{
		scene_->Update();
	}


	// カメラ設定
	camera_->SetBeforeDraw();

	// 描画
	scene_->Draw();
	camera_->Draw();

	switch (sceneid_)
	{
	case SCENE_ID::TITLE:
		break;
	case SCENE_ID::GAME:
		// デバッグ描画
		camera_->DrawDebug();
		// UI描画
		camera_->DrawUI();
		break;
	}

	fader_->Draw();

}

void SceneManager::Release(void)
{
	delete fader_;

	scene_->Release();
	delete scene_;

	camera_->Release();
	delete camera_;

	resourcemanager_->Release();
	delete resourcemanager_;

}

void SceneManager::ChangeScene(SCENE_ID nextId, bool isFading)
{

	waitsceneid_ = nextId;

	if (isFading)
	{
		fader_->SetFade(Fader::FADE_STATE::FADE_OUT);
		mIsSceneChanging = true;
	}
	else 
	{
		DoChangeScene();
	}

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneid_;
}

float SceneManager::GetDeltaTime(void)
{
	//return 0.016f;
	return deltatime_;
}

Camera* SceneManager::GetCamera(void)
{
	return camera_;
}

ResourceManager* SceneManager::GetResource(void)
{
	return resourcemanager_;
}

void SceneManager::ResetDeltaTime(void)
{
	deltatime_ = 0.016f;
	tickcount_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(void)
{

	resourcemanager_->Release();
	scene_->Release();

	sceneid_ = waitsceneid_;

	switch (sceneid_)
	{
	case SCENE_ID::TITLE:
		scene_ = new TitleScene(this);
		break;
	case SCENE_ID::GAME:
		scene_ = new GameScene(this);
		break;
	case SCENE_ID::EVENT:
		scene_ = new EventScene(this);
		break;
	case SCENE_ID::BATTLE:
		scene_ = new BattleScene(this);
		break;
	default:
		break;
	}

	scene_->Init();
	
	ResetDeltaTime();

	waitsceneid_ = SCENE_ID::NONE;

}



