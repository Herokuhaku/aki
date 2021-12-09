#include "RockManager.h"
#include "Transform.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "AsoUtility.h"

RockManager::RockManager(SceneManager* manager, Transform* trans)
{
	scenemanager_ = manager;
	transform_ = trans;
	resourcemanager_ = scenemanager_->GetResource();
	Init();
}

void RockManager::Init()
{
}


void RockManager::Update(void)
{
	// プレイヤーの位置を見て、周囲27マスのマップ生成を\
	行うかどうかを判断する\
	3重ループが一番楽

	//// プレイヤー座標をマップ座標に変換
	Int3 mappos = (Int3(transform_->pos) / 2000);
	Int3 cmappos = { 0,0,0 };

	Int3 pos = cmappos + mappos;
	//std::vector<Rock*> rocks;
	for (auto& rock : rocks_) {
		if (rock.first.x == mappos.x &&
			rock.first.y == mappos.y &&
			rock.first.z == mappos.z) {
			return;
		}
	}
	rocks_.clear();
	for (int x = -1; x <= 1; ++x) {
		for (int y = -1; y <= 1; ++y) {
			for (int z = -1; z <= 1; ++z) {
				cmappos.x = x;
				cmappos.y = y;
				cmappos.z = z;
				pos = cmappos + mappos;
				CreateRandom(pos);
				//rocks.emplace_back(CreateRandom(pos));
			}
		}
	}

	/*
	if (rocks_.count(cmappos)) {
		return;
	}*/
	//rocks_.emplace(mappos, rocks);
}
void RockManager::Draw(void)
{
	Int3 mappos = (Int3(transform_->pos) / 2000);
	Int3 c;
	for (int x = -1; x <= 1; ++x) {
		for (int y = -1; y <= 1; ++y) {
			for (int z = -1; z <= 1; ++z) {
				c.x = x;
				c.y = y;
				c.z = z;
				if (rocks_.find(mappos + c) == rocks_.end()) {
					continue;
				}
				for (auto& rock : rocks_[mappos + c]) {
					rock->Draw();
				}
				//rocks.emplace_back(CreateRandom(pos));
			}
		}
	}
	//for (auto& map : rocks_) {
	//	// 元々ポインタだから参照じゃなくていい
	//	for (auto rock : map.second) {
	//		rock->Draw();
	//	}
	//}
}

void RockManager::Release(void)
{
	for (auto& map : rocks_) {
		// 元々ポインタだから参照じゃなくていい
		for (auto rock : map.second) {
			rock->Release();
			delete rock;
		}
		map.second.clear();
	}

	rocks_.clear();
}

Rock* RockManager::CreateRandom(Int3 mappos)
{
	std::vector<Rock*> roks;
	while (roks.size() < 30) {
		//岩のモデルをランダムに決める(ROCKは2種類だから %2 0or1で表せるように)
		int r = rand() % 2/* + static_cast<int>(ResourceManager::SRC::ROCK01)*/;
		int id = -1;
		////id = resourcemanager_->LoadModelDuplicate(static_cast<ResourceManager::SRC>(r));
		switch (r) {
		case 0:
			id = resourcemanager_->LoadModelDuplicate(ResourceManager::SRC::ROCK01);
			break;
		case 1:
			id = resourcemanager_->LoadModelDuplicate(ResourceManager::SRC::ROCK02);
			break;
		default:
			break;
		}

		// 位置
		VECTOR pos;
		pos.x = GetRand(20000) - 10000;
		pos.y = GetRand(20000) - 10000;
		pos.z = GetRand(20000) - 10000;
		
		Float3 angles;
		angles = Float3{
		AsoUtility::Deg2RadF(GetRand(360)),
		AsoUtility::Deg2RadF(GetRand(360)),
		0.0f };

		Float3 scale;
		float s = GetRand(150) + 2;
		scale = Float3{ s,s,s };

		Rock* ret = new Rock();
		ret->Init(id, pos, angles.toVECTOR(), scale.toVECTOR());
		roks.emplace_back(ret);
	}
	rocks_.emplace(mappos,roks);
	//rocks_[mappos] = roks;
	
	return nullptr;
}
