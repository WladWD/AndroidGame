#include "Cookie.h"


Draw::Cookie::Cookie(Resource::ResourceBase *resourceLoad, std::string mName)
{
	//////////////////////////////////////////////////////////////////////////////////////////
	Load::LoadCookie *mLoadCookie = new Load::LoadCookie(resourceLoad, mName);
	//////////////////////////////////////////////////////////////////////////////////////////
	mLowpolyModel = mLoadCookie->GetLowPolyModel();
	mCookieDestroy = mLoadCookie->GetCookieDestroy();
	mBoundingCookie = mLoadCookie->GetSphereBounding();
	mModelDraw = mLoadCookie->GetModel();
	//////////////////////////////////////////////////////////////////////////////////////////
	delete mLoadCookie;
	//////////////////////////////////////////////////////////////////////////////////////////
}

Draw::Cookie::~Cookie()
{
	delete mModelDraw;
	delete mBoundingCookie;
	delete mCookieDestroy;
	delete mLowpolyModel;
}

Collision::LowPolyModel * Draw::Cookie::GetLowPolyModel(void)
{
	return mLowpolyModel;
}

DrawCookie::CookieDestroy * Draw::Cookie::GetCookieDestroy(void)
{
	return mCookieDestroy;
}

Collision::BoundingSphere * Draw::Cookie::GetBoundingSphere(void)
{
	return mBoundingCookie;
}
