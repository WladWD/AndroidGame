#include "CoffeeControll.h"


Draw::CoffeeControll::CoffeeControll(Draw::Collect *mCollect, Camera::MCamera *cCamera, float mHeight, float mAngleBase, float fZOffset, float mStepH,
	glm::vec2 fFog, const float *fFogColor, float mRotateVel, Shader::ShaderCollectBase *mShaderCollect,
	float mMinTime, float mMaxTime, int32_t mSectorsCount, float mMaxDelta,
	Resource::ResourceBase *resourceLoad, Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad,
	float fCookieMinYOffset, float mCookieZOffset, Score::Score *mScore) :
	CollectDrawControllBase(mCollect, cCamera, mHeight, mAngleBase, fZOffset, mStepH,
		fFog, fFogColor, mRotateVel, mShaderCollect,
		mSectorsCount, mMaxDelta),
	mMinTime(mMinTime * 1000.0f), mMaxTime(mMaxTime * 1000.0f),
	mCountCoffee(1), mScore(mScore)
{
	mRotateVelDelta = 0.01f;
	mRandom = new Engine::RandomNormal();

	mDrawFlash = new DrawFlash::DrawFlashCreator(resourceLoad, mMapResource, textureLoad, "resource\\textures\\flash\\coffee\\1.rif", cCamera, fCookieMinYOffset, mCookieZOffset);
	Init(mCollect, mShaderCollect);
}

Draw::CoffeeControll::~CoffeeControll()
{
	delete mRandom;
	delete mDrawFlash;

	for (register int32_t i = 0; i < mCollects.size(); ++i)
		delete mCollects[i];

	mCollects.clear();
	mCollects.shrink_to_fit();
}

void Draw::CoffeeControll::ResizeLine(void)
{
	if (mCurrentCount >= mCurrentTarget)
	{
		mCurrentCount = 0;
		mCurrentTarget = mMinTime + mRandom->GetNextDouble() * (mMaxTime - mMinTime);

		int32_t li = mIntAngle;
		mIntAngle = mRandom->GetNextInteger() % mSectorsCount;
		if (li == mIntAngle)
			mIntAngle = (mIntAngle + 1) % mSectorsCount;
	}
}

void Draw::CoffeeControll::Init(Draw::Collect *mCollect, Shader::ShaderCollectBase *mShader)
{
	float mRotateVal = 0.0f;
	float mDeltaVal = (4.0f * 6.28318530718f) / mCountCoffee;
	for (register uint32_t i = 0; i < mCountCoffee; ++i)
	{
		ResizeLine();

		CollectStandart *mCollectTMP = new CollectStandart(mCollect, cCamera, -mHeight, mAngleBase * mIntAngle, fZOffset, fFog,
			fFogColor, mRotateVel + mRotateVelDelta * mRandom->GetNextDouble(), mShader, mRotateVal, -mStepH, mDrawFlash);
		mCollects.push_back(mCollectTMP);

		mRotateVal += mDeltaVal;
	}
}

void Draw::CoffeeControll::Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight)
{
	mNearesIndex.clear();
	mCurrentCount += fDeltaTime;

	uint32_t minI = 0;
	for (register uint32_t i = 0; i < mCollects.size(); ++i) {
		mCollects[i]->Update(fDeltaTime, fGlobalTime, fDeltaHeight);
		if (mCollects[i]->GetHeight() < 0.0 && mCollects[i]->GetHeight() > mCollects[minI]->GetHeight())
			minI = i;

		if (mCollects[i]->GetHeight() > 0.0 && mCollects[i]->GetHeight() < mMaxDelta)
			mNearesIndex.push_back(i);
	}
	mNearesIndex.push_back(minI);
}

void Draw::CoffeeControll::Draw(void)
{
	for (register uint32_t i = 0; i < mCollects.size(); ++i)
		mCollects[i]->Draw();
}

void Draw::CoffeeControll::Intersect(const Draw::CookieCollisionStruct & mCookieCollision)
{
	uint32_t mCount = 0;
	for (register uint32_t i = 0; i < mNearesIndex.size(); ++i) {
		//if(!mCollects[mNearesIndex[i]]->IsCollected())
		if (mCollects[mNearesIndex[i]]->Intersect(mCookieCollision))
			mScore->IncCoffee();
			//++mCount;
		//score->Inc;
	}

}

void Draw::CoffeeControll::Present(void)
{
	for (register uint32_t i = 0; i < mCountCoffee; ++i)
	{
		if (mCollects[i]->GetHeight() > 0.0f && mCurrentCount >= mCurrentTarget)
		{
			ResizeLine();

			mCollects[i]->Present(mHeight, mAngleBase * mIntAngle, mRotateVel + mRotateVelDelta * mRandom->GetNextDouble());
		}
	}
}
