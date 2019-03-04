#include "LoadCookie.h"


Load::LoadCookie::LoadCookie(Resource::ResourceBase * resourceLoad, std::string mName) : LoadBase(resourceLoad, mName)
{
	Load(mName);
}

Load::LoadCookie::~LoadCookie()
{
	delete mBounding;
	delete mDrawModelLoad;
	delete mLowPolyModel;
}

void Load::LoadCookie::Load(std::string mFileName)
{
	mDrawModelLoad = new LoadDrawModel(resourceLoad, mFileName);
	mBounding = new LoadSphereCookieBounding(mFileName + "sp", resourceLoad);
	mLowPolyModel = new LoadLowPolyModel(resourceLoad, mFileName + "lp");
}

Collision::LowPolyModel * Load::LoadCookie::GetLowPolyModel(void)
{
	return mLowPolyModel->GetLowPolyModel();
}

DrawCookie::CookieDestroy * Load::LoadCookie::GetCookieDestroy(void)
{
	return mBounding->GetCookieDestroy();
}

Collision::BoundingSphere * Load::LoadCookie::GetSphereBounding(void)
{
	return mBounding->GetSphereBounding();
}
