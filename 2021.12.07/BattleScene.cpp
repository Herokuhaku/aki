#include "AsoUtility.h"
#include "GameCommon.h"
#include "SpaceDome.h"
#include "RockManager.h"
#include "BossShip.h"
#include "PlayerShip.h"
#include "Camera.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "PlayerShot.h"
#include "TurretShot.h"
#include "Turret.h"
#include "BattleScene.h"

BattleScene::BattleScene(SceneManager* manager) : SceneBase(manager)
{
}

void BattleScene::Init(void)
{
	mPlayerShip = new PlayerShip(scenemanager_);
	mPlayerShip->Init();

	mSpaceDome = new SpaceDome(scenemanager_, mPlayerShip->GetTransForm());
	mSpaceDome->Init();

	mRockManager = new RockManager(scenemanager_, mPlayerShip->GetTransForm());
	mRockManager->Init();

	mBossShip = new BossShip(scenemanager_, mPlayerShip);
	mBossShip->Init();

	// カメラ設定
	scenemanager_->GetCamera()->SetShip(mPlayerShip->GetTransForm());
	scenemanager_->GetCamera()->ChangeCameraMode(Camera::MODE::SPRING);

	mStepShipDestroy = TIME_RESTART;

	mClearIm = LoadGraph("Image/EndLogo.png");
}

void BattleScene::Update(void)
{
	// シーン遷移
	if (keyTrgDown[KEY_SYS_START])
	{
		// mSceneManager->ChangeScene(SceneManager::SCENE_ID::TITLE, true);
	}


	mPlayerShip->Update();
	mBossShip->Update();

	// 当たり判定
	if (mPlayerShip->isDestroy())
	{
		mStepShipDestroy -= scenemanager_->GetDeltaTime();
		if (mStepShipDestroy < 0.0f)
		{
			scenemanager_->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
		}
	}
	else
	{
		// 自機とボスの当たり判定
		if (mBossShip->GetState() == BossShip::STATE::BATTLE)
		{
			auto info = MV1CollCheck_Sphere(mBossShip->GetTranceform().modelId, -1,
				mPlayerShip->GetTransForm()->pos, mPlayerShip->COLLISION_RADIUS);
			if (info.HitNum > 0)
			{
				mPlayerShip->Destroy();
			}
			MV1CollResultPolyDimTerminate(info);
		}
	}

	// プレイヤーの弾の更新
	auto shots = mPlayerShip->GetShots();
	for (auto shot : shots)
	{
		if (shot->IsAlive())
		{
			shot->Update();
			// 弾とボスの当たり判定
			auto info = MV1CollCheck_Sphere(mBossShip->GetTranceform().modelId, -1,
				shot->GetPos(), shot->GetCollisionRadius());
			if (info.HitNum > 0)
			{
				shot->CreateExplosion();
			}

			// 弾と砲台の当たり判定
			auto turrets = mBossShip->GetTurrets();
			for (auto turret : turrets)
			{
				if (!turret->IsAlive())
				{
					continue;
				}
				if (AsoUtility::IsHitSpheres(shot->GetPos(), shot->GetCollisionRadius(),
					turret->GetPos(), Turret::COLLISION_RADIUS))
				{
					turret->Damage();
					shot->CreateExplosion();
					break;
				}
			}

			MV1CollResultPolyDimTerminate(info);
		}
	}

	// ボスの弾とプレイヤーの当たり判定
	auto turrets = mBossShip->GetTurrets();
	for (auto turret : turrets)
	{
		auto tShots = turret->GetShots();
		for (auto shot : tShots)
		{
			if (shot->IsAlive())
			{
				if (AsoUtility::IsHitSpheres(mPlayerShip->GetTransForm()->pos, PlayerShip::COLLISION_RADIUS,
					shot->GetPos(), shot->GetCollisionRadius()))
				{
					// 自機を破壊
					mPlayerShip->Destroy();
				}
			}
		}
	}
	

	mSpaceDome->Update();
	mRockManager->Update();
}

void BattleScene::Draw(void)
{
	mSpaceDome->Draw();
	mRockManager->Draw();

	mBossShip->Draw();
	mPlayerShip->Draw();

	// プレイヤーの弾の描画
	auto shots = mPlayerShip->GetShots();
	for (auto shot : shots)
	{
		if (shot->IsAlive())
		{
			shot->Draw();
		}
	}


}

void BattleScene::Release(void)
{
	mPlayerShip->Release();
	mPlayerShip = nullptr;
	mSpaceDome->Release();
	mSpaceDome = nullptr;
	mRockManager->Release();
	mRockManager = nullptr;
	mBossShip->Release();
	mBossShip = nullptr;
}
