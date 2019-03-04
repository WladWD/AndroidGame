#include "CollectBase.h"


Draw::CollectBase::CollectBase(Draw::Collect * mCollect, Camera::MCamera * cCamera, float mHeight, float mAngle) :
	cCamera(cCamera), mHeight(mHeight), mAngle(mAngle), mDeltaConst(1), mIntersect(false), mPicked(false)
{
	mWorld = glm::mat4(1.0f);
	//mDeltaConst = std::rand() & 1 ? 1.0f : -1.0f;

	mModelDraw = mCollect->GetDrawModel();
	mSphere = new Collision::BoundingSphereInstance(mCollect->GetBoundingSphere(), mWorld);
}

Draw::CollectBase::~CollectBase()
{
	delete mSphere;
}

/*void Draw::CollectBase::Present(float mHeight, float mAngle)
{
	this->mHeight = mHeight;
	this->mAngle = mAngle;
}
*/
float Draw::CollectBase::GetHeight(void)
{
	return mHeight;
}

const Collision::BoundingSphereInstance * Draw::CollectBase::GetBoundingSphere(void)
{
	return mSphere;
}
