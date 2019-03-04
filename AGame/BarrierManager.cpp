#include "BarrierManager.h"



Barrier::BarrierManager::BarrierManager(Resource::ResourceBase * mResourceLoad, Camera::MCamera * cCamera,
	GameEngine::GlobalMove * mGloablMove, float fHeight, glm::vec2 fFog, const float *fFogColor, float fCookieMinYOffset,
	float mAngle, float fZOffset, float mStepH, int32_t mMinCount, int32_t mMaxCount, int32_t mSectorsCount, float mRotateVelCollect,
	Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad, float mCookieZOffset, Score::Score *mScore) : cCamera(cCamera), fHeight(fHeight),
mGloablMove(mGloablMove), fFogColor(fFogColor), fFog(fFog), mCookieMinYOffset(fCookieMinYOffset), mCookieZOffset(mCookieZOffset),
mAngle(mAngle), fZOffset(fZOffset), mStepH(mStepH), mMinCount(mMinCount), mMaxCount(mMaxCount), mRotateVelCollect(mRotateVelCollect), mScore(mScore),
mSectorsCount(mSectorsCount)
{
	mBarrier = 0;
	LoadSet(0, mResourceLoad, mMapResource, textureLoad);
}

Barrier::BarrierManager::~BarrierManager()
{
	if (mBarrier) delete mBarrier;
}

void Barrier::BarrierManager::DrawBarriers(void)
{
	mBarrier->DrawBarriers();
}

void Barrier::BarrierManager::Upade(float fDeltaTime, float fGlobalTime)
{
	mBarrier->Update(fDeltaTime, fGlobalTime);
	mBarrier->Present();
}

bool Barrier::BarrierManager::Intersect(const Draw::CookieCollisionStruct &mCookieCollision)
{
	return mBarrier->Intersect(mCookieCollision);
}

void Barrier::BarrierManager::LoadSet(uint32_t SetIndex, Resource::ResourceBase * mResourceLoad, Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad)
{
	if(mBarrier) delete mBarrier;

	switch (SetIndex) 
	{
	case 0: 
	{
		mBarrier = new BarrierSetDefault(mResourceLoad, cCamera, mGloablMove, -fHeight * 0.1f, fHeight, fFog, fFogColor, mCookieMinYOffset,
			mAngle, fZOffset, mStepH, mMinCount, mMaxCount, mSectorsCount, mRotateVelCollect, mMapResource, textureLoad, mCookieZOffset, mScore);
	} break;
	}
}
