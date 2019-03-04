#include "CollectControllBase.h"



Draw::CollectControllBase::CollectControllBase(Camera::MCamera *cCamera, float mHeight, float mAngleBase, float fZOffset, //fZOffset = Cookie fZOffset
	glm::vec2 fFog, const float *fFogColor, float mRotateVel, int32_t mSectorsCount) : cCamera(cCamera), mHeight(mHeight), mAngleBase(mAngleBase), fZOffset(fZOffset),
	fFog(fFog), fFogColor(fFogColor), mRotateVel(mRotateVel), mIntAngle(0), mSectorsCount(mSectorsCount)
{
	mRandom = new Engine::RandomNormal();
}

Draw::CollectControllBase::~CollectControllBase()
{
	delete mRandom;
}
