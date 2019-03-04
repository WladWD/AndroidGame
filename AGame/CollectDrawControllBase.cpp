#include "CollectDrawControllBase.h"


Draw::CollectDrawControllBase::CollectDrawControllBase(Draw::Collect * mCollect, Camera::MCamera * cCamera, float mHeight, float mAngleBase,
	float fZOffset, float mStepH, glm::vec2 fFog, const float * fFogColor, float mRotateVel, 
	Shader::ShaderCollectBase * mShaderCollect, int32_t mSectorsCount, float mMaxDelta) :
	cCamera(cCamera), mHeight(mHeight), mAngleBase(mAngleBase), fZOffset(fZOffset), mStepH(mStepH),
	fFog(fFog), fFogColor(fFogColor), mRotateVel(mRotateVel), mSectorsCount(mSectorsCount), mMaxDelta(mMaxDelta),
	 mRotateVelDelta(0.000)
{
}

Draw::CollectDrawControllBase::~CollectDrawControllBase()
{
}

void Draw::CollectDrawControllBase::Intersect(const Draw::CookieCollisionStruct & mCookieCollision)
{
	uint32_t mCount = 0;
	for (register uint32_t i = 0; i < mNearesIndex.size(); ++i) {
		//if(!mCollects[mNearesIndex[i]]->IsCollected())
		if(mCollects[mNearesIndex[i]]->Intersect(mCookieCollision))
			++mCount;
				//score->Inc;
	}

}

void Draw::CollectDrawControllBase::Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight)
{
	mNearesIndex.clear();
	mHeight += fDeltaHeight;

	uint32_t minI = 0;
	for (register uint32_t i = 0; i < mCollects.size(); ++i) {
		mCollects[i]->Update(fDeltaTime, fGlobalTime, fDeltaHeight);

		if (mCollects[i]->GetHeight() < 0.0 && mCollects[i]->GetHeight() > mCollects[minI]->GetHeight() && !mCollects[i]->IsCollected())
			minI = i;

		if (mCollects[i]->GetHeight() > 0.0 && mCollects[i]->GetHeight() < mMaxDelta && !mCollects[i]->IsCollected())
			mNearesIndex.push_back(i);
	}
	mNearesIndex.push_back(minI);

}

void Draw::CollectDrawControllBase::Draw(void)
{
	for (register uint32_t i = 0; i < mCollects.size(); ++i)
		mCollects[i]->Draw();
}

void Draw::CollectDrawControllBase::DrawFlash(void)
{
	for (register uint32_t i = 0; i < mCollects.size(); ++i)
		mCollects[i]->DrawFlash();
}
