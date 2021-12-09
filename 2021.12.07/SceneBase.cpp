#include "SceneBase.h"
#include "SceneManager.h"

SceneBase::SceneBase(SceneManager* _manager)
{
	scenemanager_ = _manager;
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init(void)
{
}

void SceneBase::Update(void)
{
}

void SceneBase::Draw(void)
{
}

void SceneBase::Release(void)
{
}

SceneManager* SceneBase::GetSceneManager(void)
{
	return scenemanager_;
}
