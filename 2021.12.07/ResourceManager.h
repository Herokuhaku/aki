#pragma once
#include <map>
#include <string>
#include "Resource.h"
class ResourceManager
{
public:

	ResourceManager(void);
	~ResourceManager(void);

	enum class SRC :int
	{
		SHIP_EXPLOSION,
		SHOT_EXPLOSION,
		SPEECH_BALLOON,
		SHOT_MODEL,
		TURRET_STAND,
		TURRET_GUN,
		ROCK01,
		ROCK02,
	};

	void Init(void);
	void Release(void);

	Resource Load(SRC src);
	int LoadModelDuplicate(SRC src);

private:

	std::map<SRC, Resource> mResourcesMap;
	std::map<SRC, Resource*> mLoadedMap;

	// ì‡ïîÉçÅ[Éh
	Resource* _Load(SRC src);

};

