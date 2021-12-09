#pragma once
#include "SceneBase.h"
class SceneManager;
class BossShip;
class SpaceDome;

class EventScene : public SceneBase
{
public:
	EventScene(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	BossShip* bossship_;
	SpaceDome* spacedome_;
};

