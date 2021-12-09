#include "Stage.h"
#include <math.h>
#include "AsoUtility.h"
#include "SceneManager.h"
#include "common/Vector3.h"
#include "Transform.h"

Stage::Stage(SceneManager* manager,Transform* player):scenemanager_(manager)
{
	player_ = player;
}

void Stage::Init(void)
{
	// ダンジョン
	modeldungeon_ = MV1LoadModel("Model/Rock/Dungeon.mv1");
	MV1SetScale(modeldungeon_, { 1.0f,1.0f,1.0f });
	MV1SetPosition(modeldungeon_, {1000.0f,400.0f,1300.0f});

	float rad = AsoUtility::RadIn2PI(180.0f);
	MV1SetRotationXYZ(modeldungeon_, { 0.0f,rad,0.0f});

	// ボス
	modelboss_ = MV1LoadModel("Model/BossShip/BossShip.mv1");
	MV1SetScale(modelboss_, { 2.0f,2.0f,2.0f });
	posboss_ = { 14500.0f,-800.0f,6500.0f };
	MV1SetPosition(modelboss_, posboss_);
	rad = AsoUtility::RadIn2PI(180.0f);
	MV1SetRotationXYZ(modelboss_, { 0.0f,rad,0.0f });
}

void Stage::Update(void)
{
	Float3 bosspos = posboss_;
	Float3 playerpos = player_->pos;
	//Float3 r = (bosspos - playerpos);
	//r = Float3(abs(r.x), abs(r.y), abs(r.z));
	Float3 r = Float3(std::pow((bosspos.x - playerpos.x), 2),std::pow((bosspos.y - playerpos.y),2),std::pow((bosspos.z - playerpos.z),2));
	bool flag = r.x + r.y + r.z <= std::pow((RAD + RADIUS), 2);
	if (flag) {
		scenemanager_->ChangeScene(SceneManager::SCENE_ID::EVENT, true);
	}
}

void Stage::Draw(void)
{
	DrawGrid();
	MV1DrawModel(modeldungeon_);
	MV1DrawModel(modelboss_);
	DrawSphere3D(posboss_, RADIUS, 10, 0xffffff,0xffffff, false);
}

void Stage::DrawGrid(void)
{
	constexpr int LEN = 3000.0f;
	constexpr int TERM = 100.0f;
	constexpr int NUM = LEN / TERM;

	for (int i = -NUM; i < NUM; i++) {
		DrawLine3D(VGet(-LEN, 0.0f, i * TERM), VGet(LEN, 0.0f, i * TERM), 0xff0000);
		//
		DrawLine3D(VGet(i * TERM, 0.0f,-LEN), VGet(i * TERM,0.0f,LEN), 0x0000ff);
		//DrawLine3D(VGet(-LEN, 0.0f, i * TERM), VGet(LEN, 0.0f, i * TERM), 0xff0000);
	}
	DrawLine3D(VGet(0.0f, -LEN,TERM), VGet(0.0f, LEN,TERM), 0x00ff00);
}

void Stage::Release(void)
{
	MV1DeleteModel(modeldungeon_);
	MV1DeleteModel(modelboss_);
}
