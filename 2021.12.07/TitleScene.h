#pragma once
#include "SceneBase.h"
class TextScroll;
class SpaceDome;
class ParticleGenerator;

class TitleScene : public SceneBase
{

public:

	TitleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawLogo(void);
	void Release(void) override;

private:
	SpaceDome* spacedome_;
	int mImgStartLogo;

	SceneManager* mng_;
	ParticleGenerator* particlegenerator;
	TextScroll* text_;
};

