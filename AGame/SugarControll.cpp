#include "SugarControll.h"


Draw::SugarControll::SugarControll(Draw::Collect *mCollect, Camera::MCamera *cCamera, float mHeight, float mAngleBase, float fZOffset, float mStepH,
	glm::vec2 fFog, const float *fFogColor, float mRotateVel, Shader::ShaderCollectBase *mShaderCollect,
	int32_t mMinCount, int32_t mMaxCount, int32_t mSectorsCount, float mMaxDelta,
	Resource::ResourceBase *resourceLoad, Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad,
	float fCookieMinYOffset, float mCookieZOffset, Score::Score *mScore) : 
	CollectDrawControllBase(mCollect, cCamera, mHeight, mAngleBase, fZOffset, mStepH,
		fFog, fFogColor, mRotateVel, mShaderCollect,
		mSectorsCount, mMaxDelta), mCurrentCount(0), mCurrentTarget(0),
	mMinCount(mMinCount), mMaxCount(mMaxCount),
	mCountSugar(mMaxCount * 10), mScore(mScore)
{
	//mDrawFlash = new DrawFlash::DrawFlash();

	mDrawFlash = new DrawFlash::DrawFlashCreator(resourceLoad, mMapResource, textureLoad, "resource\\textures\\flash\\suggar\\1.rif", cCamera, fCookieMinYOffset, mCookieZOffset);

	mRandom = new Engine::RandomNormal();
	Init(mCollect, mShaderCollect);
}

Draw::SugarControll::~SugarControll()
{
	delete mDrawFlash;
	delete mRandom;

	for (register int32_t i = 0; i < mCollects.size(); ++i)
		delete mCollects[i];

	mCollects.clear();
	mCollects.shrink_to_fit();
}

void Draw::SugarControll::ResizeLine(void)
{
	if (mCurrentCount >= mCurrentTarget)
	{
		mCurrentCount = 0;
		mCurrentTarget = mMinCount + mRandom->GetNextInteger() % (mMaxCount - mMinCount + 1);
		
		int32_t li = mIntAngle;
		mIntAngle = mRandom->GetNextInteger() % mSectorsCount;
		if (li == mIntAngle)
			mIntAngle = (mIntAngle + 1) % mSectorsCount;
	}
}

void Draw::SugarControll::Init(Draw::Collect *mCollect, Shader::ShaderCollectBase *mShader)
{
	float mRotateVal = 0.0f;
	float mDeltaVal = (4.0f * 6.28318530718f) / mCountSugar;
	for (register uint32_t i = 0; i < mCountSugar; ++i)
	{

		ResizeLine();

		//mIntAngle += mRandom->GetNextDoubleIntGen(mVer);
		//mIntAngle = (mIntAngle + mSectorsCount) % mSectorsCount;

		CollectStandart *mCollectTMP = new CollectStandart(mCollect, cCamera, mHeight, mAngleBase * mIntAngle, fZOffset, fFog, 
			fFogColor, mRotateVel + mRotateVelDelta * mRandom->GetNextDouble(), mShader, mRotateVal, -mStepH, mDrawFlash);//+ mRotateVelDelta * mRandom->GetNextDouble()
		mCollects.push_back(mCollectTMP);

		mHeight += mStepH;
		++mCurrentCount;

		mRotateVal += mDeltaVal;
	}
}

void Draw::SugarControll::Intersect(const Draw::CookieCollisionStruct & mCookieCollision)
{
	uint32_t mCount = 0;
	for (register uint32_t i = 0; i < mNearesIndex.size(); ++i) {
		//if(!mCollects[mNearesIndex[i]]->IsCollected())
		if (mCollects[mNearesIndex[i]]->Intersect(mCookieCollision))
			mScore->IncSugar();
			//++mCount;
		//score->Inc;
	}

}

void Draw::SugarControll::Present(void)
{
	for (register uint32_t i = 0; i < mCountSugar; ++i)
	{
		if (mCollects[i]->GetHeight() > 0.0f)
		{
			ResizeLine();

			if (mCollects[i]->Present(mHeight, mAngleBase * mIntAngle, mRotateVel + mRotateVelDelta * mRandom->GetNextDouble()))//+ mRotateVelDelta * mRandom->GetNextDouble()
			{
				mHeight += mStepH;
				++mCurrentCount;
			}
		}
	}
}
