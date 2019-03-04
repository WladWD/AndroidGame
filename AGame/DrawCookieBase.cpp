#include "DrawCookieBase.h"


DrawCookie::DrawCookieBase::DrawCookieBase(Draw::Cookie *mCookie, Camera::MCamera *cCamera) : cCamera(cCamera)//, mBounding(mBounding)
{
	//InitBaseData();
	//mCookieDestroy = mBounding->GetCookieDestroy();
	//mBoundingSphere = new Bounding::BoundingObjectStructSphere(mBounding, mCookieDestroy->mCenter);//mBounding->GetVertexBuffer(), mBounding->GetVertexCount());
	mWorld = glm::mat4(1.0f);

	mCookieDestroy = mCookie->GetCookieDestroy();
	mModelDraw = mCookie->GetDrawModel();
	mSphere = new Collision::BoundingSphereInstance(mCookie->GetBoundingSphere(), mWorld);
	mLowpolyModel = new Collision::LowPolyModelInstance(mCookie->GetLowPolyModel(), mWorld);
}

DrawCookie::DrawCookieBase::~DrawCookieBase()
{
	//delete mBoundingSphere;
	/*delete mImagesResource;
	delete mObjects;

	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);*/
	delete mSphere;
	delete mLowpolyModel;
}

const Collision::BoundingSphereInstance * DrawCookie::DrawCookieBase::GetBoundingSphere()
{
	return mSphere;
}

const Collision::LowPolyModelInstance * DrawCookie::DrawCookieBase::GetLowPolyModel(void)
{
	return mLowpolyModel;
}

//void DrawCookie::DrawCookieBase::InitBaseData(void)
//{
//	/*Resource::ResourceLoad *mModel = new Resource::ResourceLoad(mResourceName, mResourceLoad);
//
//	mImagesResource = mModel->GetImagesResource();
//	mIndexBuffer = mModel->GetIndexBuffer(mIndexFormat);
//	mVertexBuffer = mModel->GetVertexBuffer();
//	mObjects = mModel->GetModelObjects(mDrawObjectCount);
//
//	delete mModel;*/
//
//	mImagesResource = mBounding->GetImageResource();
//	mObjects = mBounding->GetModelObject();
//	mBounding->GetDrawData(mIndexFormat, mVertexBuffer, mIndexBuffer, mDrawObjectCount);
//}
