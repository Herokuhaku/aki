#include "SceneManager.h"
#include "AsoUtility.h"
#include "SpriteAnimator.h"
#include "Camera.h"
#include "EventShot.h"
#include "Turret.h"
#include "PlayerShip.h"
#include "BossShip.h"

BossShip::BossShip(SceneManager* manager, PlayerShip* player)
{
	mSceneManager = manager;
	mPlayerShip = player;
	Init();
}

void BossShip::Init(void)
{
	VECTOR pos = { 0.0f, 0.0f, 4000.0f };

	// ƒ‚ƒfƒ‹‚ÌŠî–{î•ñ
	mTransform.SetModel(MV1LoadModel("Model/BossShip/BossShip.mv1"));

	float scale = 2.0f;
	mTransform.scl = { scale, scale , scale };
	mTransform.pos = pos;
	mTransform.quaRot = Quaternion::Euler
	(
		AsoUtility::Deg2RadF(20.0f),
		AsoUtility::Deg2RadF(210.0f),
		AsoUtility::Deg2RadF(0.0f)
	);
	mTransform.quaRotLocal = Quaternion::Euler
	(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);
	mTransform.Update();

	// –C‘ä
	mTurrets.clear();
	// ‘O•û
	MakeTurret(
		{ 4.5f, 5.5f, 7.8f },
		{ 0.0f, 0.0f, AsoUtility::Deg2RadF(-18.0f) });
	MakeTurret(
		{ -4.5f, 5.5f, 7.8f },
		{ 0.0f, 0.0f, AsoUtility::Deg2RadF(18.0f) });

	// ‰¡
	MakeTurret(
		{ 4.5f, 5.5f, 0.0f },
		{ AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(90.0f), 0.0f });
	MakeTurret(
		{ -4.5f, 5.5f, 0.0f },
		{ AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(-90.0f), 0.0f });

	// Œã•û
	MakeTurret(
		{ 3.5f, 5.0f, -17.8f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(18.0f) });
	MakeTurret(
		{ -3.5f, 5.0f, -17.8f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(-18.0f) });

	// ó‘Ô‘JˆÚ
	SceneManager::SCENE_ID sceneId = mSceneManager->GetSceneID();
	switch (sceneId)
	{
	case SceneManager::SCENE_ID::EVENT:
		ChangeState(STATE::EVENT);
		break;
	case SceneManager::SCENE_ID::BATTLE:
	{
		ChangeState(STATE::BATTLE);
		// “–‚½‚è”»’è
		int ret = MV1SetupCollInfo(mTransform.modelId, -1, 1, 1, 1);
		break;
	}
	default:
		break;
	}

	mExplosions.clear();
}

void BossShip::Update(void)
{
	switch (mState)
	{
	case BossShip::STATE::EVENT:
	{
		VECTOR dir = mTransform.GetForward();
		mTransform.pos = VAdd(mTransform.pos, VScale(dir, SPEED_MODE));
		// ƒCƒxƒ“ƒg—p‚Ì’e
		mEventShot->Update();
		if (!mEventShot->IsAlive()) {
			mEventTime -= mSceneManager->GetDeltaTime();
			if (mEventTime < 0.0f) {
				mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
				return;
			}
		}

		// –C‘ä
		UpdateTurret();
	}
		break;
	case BossShip::STATE::BATTLE:
	{
		// Œü‚¢‚Ä‚¢‚é•ûŒü‚ÉˆÚ“®
		VECTOR dir = mTransform.GetForward();
		mTransform.pos = VAdd(mTransform.pos, VScale(dir, SPEED_MODE));

		// Œü‚¢‚Ä‚¢‚éŠp“x‚ð­‚µ•ÏX
		float speed = 0.05f * mSceneManager->GetDeltaTime();
		float rad = AsoUtility::Deg2RadF(1.0f);
		Quaternion axis = Quaternion::AngleAxis(
			speed, AsoUtility::AXIS_Y);
		mTransform.quaRot = mTransform.quaRot.Mult(axis);

		// “–‚½‚è”»’è‚ÌXV
		int ret = MV1RefreshCollInfo(mTransform.modelId, -1);

		// –C‘ä
		UpdateTurret();

		// ƒ^ƒŒƒbƒg‚Ì”j‰ó”»’è
		bool isAllBreak = true;
		for (auto turret : mTurrets)
		{
			if (turret->IsAlive())
			{
				isAllBreak = false;
			}
		}
		if (isAllBreak)
		{
			ChangeState(STATE::DESTROY);
			return;
		}
	}
		break;
	case BossShip::STATE::DESTROY:
		mDestroyTime -= mSceneManager->GetDeltaTime();
		if (mDestroyTime < 0.0f) {
			ChangeState(STATE::END);
		}
		UpdateExplosion();
		break;
	case BossShip::STATE::END:
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::TITLE, true);
		break;
	default:
		break;
	}
	mTransform.Update();
}

void BossShip::UpdateTurret(void)
{
	for (auto turret : mTurrets)
	{
		turret->Update();
	}
}

void BossShip::Draw(void)
{
	switch (mState)
	{
	case BossShip::STATE::EVENT:
		MV1DrawModel(mTransform.modelId);
		mEventShot->Draw();
		DrawTurret();
		break;
	case BossShip::STATE::BATTLE:
		MV1DrawModel(mTransform.modelId);
		DrawTurret();
		break;
	case BossShip::STATE::DESTROY:
	{
		float diff = TIME_DESTROY - mDestroyTime;
		auto c = AsoUtility::Lerp(
			FADE_C_FROM, FADE_C_TO, (diff / TIME_DESTROY));

		int num = MV1GetMaterialNum(mTransform.modelId);

		for (int i = 0; i < num; i++) {
			MV1SetMaterialDifColor(mTransform.modelId, i, c);
		}
		MV1DrawModel(mTransform.modelId);
		DrawExplosion();
		break;
	}
	default:
		break;
	}
}

void BossShip::DrawTurret(void)
{
	for (auto turret : mTurrets)
	{
		turret->Draw();
	}
}

void BossShip::Release(void)
{
	MV1DeleteModel(mTransform.modelId);
	for (auto turret : mTurrets)
	{
		turret->Release();
		delete turret;
	}
	mTurrets.clear();
}

void BossShip::UpdateExplosion(void)
{
	// ’¸“_”
	int indexNum = 30;

	// Šp“x‚Ì‰Šú‰»
	float cntAngle = 0;
	float cntAngle2 = 0;

	// ‰~‚Ì’†SÀ•W
	VECTOR cPos = mTransform.pos;
	VECTOR offset = mTransform.GetUp();
	offset = VScale(offset, 200.0f);
	cPos = VAdd(cPos, offset);

	VECTOR vPos;
	Quaternion rot;
	Quaternion rot2;

	// ”¼Œa
	float radius = 700.0f;

	while (360 > cntAngle)
	{
		// ’¸“_À•W
		rot = Quaternion::AngleAxis(AsoUtility::Deg2RadF(cntAngle),AsoUtility::AXIS_Y);
		while (360 > cntAngle2)
		{
			rot2 = Quaternion::AngleAxis(AsoUtility::Deg2RadF(cntAngle2),AsoUtility::AXIS_Z);
			rot2 = rot2.Mult(rot);
			rot2 = mTransform.quaRot.Mult(rot2);
			// ‘Š‘ÎÀ•W‚ð‰ñ“]
			VECTOR pos = rot2.PosAxis({ radius , 0.0f,0.0f });
			pos.z *= 2.5;
			
			VECTOR p = pos;
			float x = mTransform.rot.x,y = mTransform.rot.y,z= mTransform.rot.z;

			pos.x = cos(z) * p.x + -sin(z) * p.y;
			pos.y = sin(z) * p.x + cos(z) * p.y;

			pos.y = (cos(x) * p.y + -sin(x) * p.z);
			pos.z = (sin(x) * p.y + cos(x) * p.z);

			pos.x = -(cos(y) * p.x + -sin(y) * p.z);
			pos.z = (sin(y) * p.x + cos(y) * p.z);

			//pos.z *= 2;
			// ’†SÀ•W‚É‰Á‚¦‚é
			vPos = VAdd(cPos, pos);
			//DrawSphere3D(vPos, 5, 5, 0xffffff, 0xffa0ff, true);

			// ¶¬
			int i = rand() % 1000;
			if (i == 0)
			{
				SpriteAnimator* explosion = new SpriteAnimator(mSceneManager, ResourceManager::SRC::SHIP_EXPLOSION, 120, 8.0f);
				explosion->Create(vPos);
				mExplosions.push_back(explosion);
			}
			cntAngle2 += (float)(360 / indexNum);
		}
		cntAngle += (float)(360 / indexNum);
		cntAngle2 = 0.0f;
	}

	for (auto explosion : mExplosions)
	{
		explosion->Update();
	}
}

void BossShip::DrawExplosion(void)
{
	for (auto explosion : mExplosions)
	{
		explosion->Draw();
	}
}

int BossShip::GetModelID(void)
{
	return mTransform.modelId;
}

void BossShip::MakeTurret(VECTOR localPos, VECTOR localAddAxis)
{
	Turret* turret = nullptr;
	turret = new Turret(
		mSceneManager, mPlayerShip->GetTransForm(), &mTransform,
		localPos, localAddAxis);
	turret->Init();
	mTurrets.push_back(turret);
}

void BossShip::ChangeState(STATE state)
{
	mState = state;

	switch (mState)
	{
	case BossShip::STATE::EVENT:
		mEventTime = TIME_EVENT;
		mEventShot = new EventShot(mSceneManager, &mTransform);
		// ƒJƒƒ‰‚Ì•ûŒü‚É”ò‚Î‚·
		VECTOR dir = VNorm(VSub(mSceneManager->GetCamera()->GetPos(), mTransform.pos));
		mEventShot->Create(mTransform.pos, dir);
		break;
	case BossShip::STATE::BATTLE:
		int ret;
		ret = MV1SetupCollInfo(mTransform.modelId, -1, 1, 1, 1);
		break;
	case BossShip::STATE::DESTROY:
		mDestroyTime = TIME_DESTROY;
		mExplosions.clear();
		break;
	default:
		break;
	}
}

