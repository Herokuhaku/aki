#include "GameCommon.h"
#include "SceneManager.h"
#include "Resource.h"
#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator(
	SceneManager* manager, ResourceManager::SRC src, int size, float speed)
{

	mSceneManager = manager;

	// 画像の読み込み
	Resource res = mSceneManager->GetResource()->Load(src);
	mCntTotalAnim = res.mNumX * res.mNumY;
	//mImages = new int[mCntTotalAnim];
	//res.CopyHandle(mImages);
	mImages = res.mHandleIds;

	// 大きさ
	mSize = size;

	// アニメーションスピード
	mSpeedAnim = speed;

	ChangeState(STATE::NONE);

}

void SpriteAnimator::Create(VECTOR pos)
{
	mStepAnim = 0.0f;
	mPos = pos;
	ChangeState(STATE::PLAY);
}

void SpriteAnimator::Update(void)
{

	switch (mState)
	{
	case SpriteAnimator::STATE::NONE:
		break;
	case SpriteAnimator::STATE::PLAY:
	{
		mStepAnim += mSceneManager->GetDeltaTime();
		int cnt = (int)(mStepAnim * mSpeedAnim);
		mIdxAnim = cnt % mCntTotalAnim;

		if (cnt >= mCntTotalAnim)
		{
			ChangeState(STATE::END);
		}
	}
		break;

	case SpriteAnimator::STATE::END:
		
		break;
	default:
		break;
	}

}

void SpriteAnimator::Draw(void)
{

	switch (mState)
	{
	case SpriteAnimator::STATE::NONE:
		break;
	case SpriteAnimator::STATE::PLAY:

		DrawModiBillboard3D(
			mPos,
			// 左上
			-mSize,
			mSize,
			// 右上
			mSize,
			mSize,
			// 右下
			mSize,
			-mSize,
			// 左下
			-mSize,
			-mSize,
			mImages[mIdxAnim],
			true
		);

		if (IS_DEBUG)
		{
			//DrawSphere3D(mPos, 10.0f, 3, 0x00ff00, 0x222222, true);
		}

		break;
	case SpriteAnimator::STATE::END:
		break;
	default:
		break;
	}

}

void SpriteAnimator::Release(void)
{
	//for (int i = 0; i < CNT_ANIM; i++)
	//{
	//	DeleteGraph(mImages[i]);
	//}
}

VECTOR SpriteAnimator::GetPos(void)
{
	return mPos;
}

void SpriteAnimator::SetPos(VECTOR pos)
{
	mPos = pos;
}

float SpriteAnimator::GetZLen(void)
{
	return mZLen;
}

void SpriteAnimator::SetZLen(float len)
{
	mZLen = len;
}

bool SpriteAnimator::IsEnd(void)
{
	return mState == STATE::END;
}

void SpriteAnimator::ChangeState(STATE state)
{

	mState = state;
	switch (mState)
	{
	case SpriteAnimator::STATE::NONE:
		break;
	case SpriteAnimator::STATE::PLAY:
		mStepAnim = 0.0f;
		break;
	case SpriteAnimator::STATE::END:
		break;
	}

}
