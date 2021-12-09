#include "SpaceDome.h"
#include "AsoUtility.h"

SpaceDome::SpaceDome(SceneManager* manager,Transform* trans)
{
	scenemanager_ = manager;
	shiptransform_ = trans;
	Init();
}

void SpaceDome::Init(void)
{
	transform_.SetModel(MV1LoadModel("Model/SkyDome/SkyDome.mv1"));

	float scale = 1.0f;
	transform_.scl = { scale,scale,scale };
	transform_.quaRot = Quaternion::Euler(0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f);
	transform_.quaRotLocal = Quaternion();
	transform_.pos = AsoUtility::VECTOR_ZERO;

	transform_.Update();
	MV1SetWriteZBuffer(transform_.modelId, false);

	if (shiptransform_ == nullptr) {
		mState = STATE::STAY;
	}
	else {
		mState = STATE::FOLLOW;
	}
}

void SpaceDome::Update(void)
{
	switch (mState) {
	case SpaceDome::STATE::STAY:
			break;
	case SpaceDome::STATE::FOLLOW:
		transform_.pos = shiptransform_->pos;
		break;
	}
	transform_.Update();
	//transform_.Update();
}

void SpaceDome::Draw(void)
{
	MV1DrawModel(transform_.modelId);

}

void SpaceDome::Release(void)
{
	MV1DeleteModel(transform_.modelId);
}

void SpaceDome::ChangeState(STATE state)
{
	mState = state;
	switch (mState) {
	case SpaceDome::STATE::STAY:
		transform_.pos = AsoUtility::VECTOR_ZERO;
		break;
	case SpaceDome::STATE::FOLLOW:
		transform_.pos = shiptransform_->pos;
		break;
	}
}
