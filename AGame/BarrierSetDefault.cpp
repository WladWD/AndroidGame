#include "BarrierSetDefault.h"


Barrier::BarrierSetDefault::BarrierSetDefault(Resource::ResourceBase * mResourceLoad, Camera::MCamera *cCamera, GameEngine::GlobalMove *mGloablMove,
	float fStep, float fHeight, glm::vec2 fFog, const float *fFogColor, float fCookieMinYOffset,
	float mAngle, float fZOffset, float mStepH, int32_t mMinCount, int32_t mMaxCount, int32_t mSectorsCount, float mRotateVelCollect,
	Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad, float mCookieZOffset, Score::Score *mScore) : BarrierSetBase(fStep, fHeight, cCamera, mGloablMove),
	fFog(fFog), fFogColor(fFogColor), fCookieMinYOffset(fCookieMinYOffset),
	mStaticStepMin(0.5f * fStep), mStaticStepMax( 2.0 * fStep),
	mDynamicStepMin(fStep), mDynamicStepMax( 4.0f * fStep)
{
	mCollect = new Draw::CollectControll(mResourceLoad, cCamera, fHeight * 2.0f, mAngle, fZOffset, mStepH, mMinCount, mMaxCount, fFog, fFogColor, mSectorsCount, mRotateVelCollect,
		2.4f, mMapResource, textureLoad, fCookieMinYOffset, mCookieZOffset, mScore,
		"resource\\models\\collect\\sugar\\sugar.tdof",
		"resource\\models\\collect\\coffee\\coffee.tdof");
	InitBarriers(mResourceLoad, 22, 32);

}

Barrier::BarrierSetDefault::~BarrierSetDefault()
{

	delete mCollect;

	for (register uint32_t i = 0; i < mBarrierData.size(); i++)
		delete mBarrierData[i];
	for (register uint32_t i = 0; i < mShaders.size(); i++)
		delete mShaders[i];
	for (register uint32_t i = 0; i < mBarriers.size(); i++)
		delete mBarriers[i];
	//for (register uint32_t i = 0; i < mBarriersStatic.size(); i++)
	//	delete mBarriersStatic[i];

	mBarrierData.clear();
	mBarrierData.shrink_to_fit();

	mShaders.clear();
	mShaders.shrink_to_fit();

	mBarriers.clear();
	mBarriers.shrink_to_fit();

	mPresentVec.clear();
	mPresentVec.shrink_to_fit();
	
	mBarriersType.clear();
	mBarriersType.shrink_to_fit();
}

void Barrier::BarrierSetDefault::InitShaders(Resource::ResourceBase * mResourceLoad)
{
	mShaders.push_back(new Shader::ShaderBarrierRotor(mResourceLoad));
	mShaders.push_back(new Shader::ShaderBarrierStatic(mResourceLoad));
}

void Barrier::BarrierSetDefault::InitBoundingObjects(Resource::ResourceBase * mResourceLoad)
{
	mBarrierData.push_back(new Draw::Barrier(mResourceLoad, "resource\\models\\barrier\\blade_rotor\\blade.tdof"));//vv2.tdof barrier\\blade_rotor\\blade
	mBarrierData.push_back(new Draw::Barrier(mResourceLoad, "resource\\models\\static\\rock.tdof"));//vv2.tdof barrier\\blade_rotor\\blade
}

void Barrier::BarrierSetDefault::InitBarriers(Resource::ResourceBase * mResourceLoad, int32_t mStaticBarriers, int32_t mDynamicBarriers)
{
	InitShaders(mResourceLoad);
	InitBoundingObjects(mResourceLoad);
	//const int mp = 4;
	//mIntersectIndexes.push_back(0);
	mBarriers.reserve(mDynamicBarriers + mStaticBarriers);
	mBarriersType.reserve(mDynamicBarriers + mStaticBarriers);
	//mBarriersStatic.resize(mStaticBarriers);

	while (true) 
	{
		Barrier::BarrierBase *mBarrier;
		float mMinStep, mMaxStep;
		if (mStaticBarriers && (rand() & 1) || !mDynamicBarriers && mStaticBarriers)
		{
			mBarrier = new Barrier::DrawBarrierStatic(mBarrierData[1], mShaders[1], cCamera, fHeight, 4, 1.57f, -3.4f, fFog, fFogColor, mStaticBarriers);//1.57f - 2pi/s 3.14f
			--mStaticBarriers;
			mMinStep = mStaticStepMin;
			mMaxStep = mStaticStepMax;
			mBarriersType.push_back(true);
		}
		else if (mDynamicBarriers)
		{
			mBarrier = new Barrier::DrawBarrierRotor(mBarrierData[0], mShaders[0], cCamera, fHeight, 2.84f, 4.8f, fFog, fFogColor);

			--mDynamicBarriers;
			mMinStep = mDynamicStepMin;
			mMaxStep = mDynamicStepMax;
			mBarriersType.push_back(false);
		}
		else
			break;

		float mRand = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX));
		fHeight -= glm::mix(mMinStep, mMaxStep, mRand);
		mBarriers.push_back(mBarrier);
	}
	/*for (register uint32_t i = 0; i < mp; i++)
	{
		Barrier::DrawBarrierRotor *mBarrier = new Barrier::DrawBarrierRotor(mBarrierData[0], mShaders[0], cCamera, fHeight, 2.84f, 4.8f, fFog, fFogColor);//1.57f - 2pi/s 3.14f

		float mRand = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX));

		fHeight -= glm::mix(fStep, 4.0f * fStep, mRand);

		mBarriers.push_back(mBarrier);
	}

	for (register uint32_t i = 0; i < mp; i++)
	{
		Barrier::DrawBarrierStatic *mBarrier = new Barrier::DrawBarrierStatic(mBarrierData[1], mShaders[0], cCamera, fHeight, 4, 1.57f, -3.4f, fFog, fFogColor, i);//1.57f - 2pi/s 3.14f

		float mRand = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX));

		fHeight -= glm::mix(fStep, 4.0f * fStep, mRand);

		mBarriersStatic.push_back(mBarrier);
	}*/
}

void Barrier::BarrierSetDefault::DrawBarriers(void)
{
	//////////
	for (register uint32_t i = 0; i < mBarriers.size(); i++) 
		mBarriers[i]->Draw();

	mCollect->Draw();
}

bool Barrier::BarrierSetDefault::Intersect(const Draw::CookieCollisionStruct &mCookieCollision)
{
	//////////
	//return false;
	//////////
	bool intersect = false;

//goto pro_mode;

	for (register uint32_t i = 0; i < mIntersectIndexes.size(); i++)
	{
		intersect = intersect || mBarriers[mIntersectIndexes[i]]->Intersect(mCookieCollision);

		if (intersect)
			break;
	}

	mIntersectIndexes.clear();

pro_mode:

	if (!intersect)
		mCollect->Intersect(mCookieCollision);

	return intersect;
}

void Barrier::BarrierSetDefault::Update(float fDeltaTime, float fGlobalTime)
{
	float fMoveVal = mGloablMove->GetMove();
	fHeight += fMoveVal;
	for (register uint32_t i = 0; i < mBarriers.size(); i++)
	{
		mBarriers[i]->Update(fDeltaTime, fGlobalTime, fMoveVal);

		float mH = mBarriers[i]->GetCurrentHeight();

		if (mH > (fCookieMinYOffset - fStep) && mH < (fCookieMinYOffset + fStep))
			mIntersectIndexes.push_back(i);
	}

	mCollect->Update(fDeltaTime, fGlobalTime, fMoveVal);
}

int32_t Barrier::BarrierSetDefault::Random(int32_t b, int32_t e)
{
	int mR = rand();
	return b + (mR % (e - b + 1));
}

void Barrier::BarrierSetDefault::RandomizePresent(void)
{
	for (register int32_t i = 0; i < mPresentVec.size(); ++i)
		swap(mPresentVec[i], mPresentVec[Random(i, mPresentVec.size() - 1)]);
}

void Barrier::BarrierSetDefault::Present(void)
{
	mPresentVec.clear();

	for (register uint32_t i = 0; i < mBarriers.size(); ++i)
		if (mBarriers[i]->GetCurrentHeight() > fStep)
			mPresentVec.push_back(i);
	RandomizePresent();
	float mMinStep, mMaxStep;
	for (register int32_t i = 0; i < mPresentVec.size(); ++i)
	{
		mBarriers[mPresentVec[i]]->Present(fHeight);
		if (mBarriersType[mPresentVec[i]])
		{
			mMinStep = mStaticStepMin;
			mMaxStep = mStaticStepMax;
		}
		else 
		{
			mMinStep = mDynamicStepMin;
			mMaxStep = mDynamicStepMax;
		}
		//float mH = mBarriers[i]->GetCurrentHeight();
		//if (mH > (fCookieMinYOffset - fStep) && mH < (fCookieMinYOffset + fStep))
		//	mIntersectIndexes.push_back(i);

		float mRand = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX));

		fHeight -= glm::mix(mMinStep, mMaxStep, mRand);
	}

	//for (register uint32_t i = 0; i < mBarriers.size(); i++)
	//{
	//	if (mBarriers[i]->GetCurrentHeight() > fStep) 
	//	{
	//		mBarriers[i]->Present(fHeight);

	//		float mH = mBarriers[i]->GetCurrentHeight();

	//		//if (mH > -fStep && mH < fStep)
	//		if (mH >(fCookieMinYOffset - fStep) && mH < (fCookieMinYOffset + fStep))
	//			mIntersectIndexes.push_back(i);


	//		float mRand = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX));

	//		fHeight -= glm::mix(fStep, 4.0f * fStep, mRand);
	//	}
	//}


	mCollect->Present();
}
