#pragma once
#include <map>

#include "Transform.h"
#include "ResourceManager.h"
#include "IntVector3.h"
#include "common/Vector3.h"
#include "Rock.h"

class SceneManager;
class RockManager
{
public:
	// 1マップ当たりのサイズ
	static constexpr int MAP_SIZE = 2000;
	// 1マップ当たりの生成する岩の数
	static constexpr int NUM_CREATE = 30;
	RockManager(SceneManager* manager,Transform* trans);
	void Init();
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	SceneManager* scenemanager_;
	Transform* transform_;
	ResourceManager* resourcemanager_;
	
	std::map<Int3, std::vector<Rock*>> rocks_;
	Rock* CreateRandom(Int3 mappos);
};

