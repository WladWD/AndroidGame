#include "LoadBoundingBase.h"
#include "BoundingSphere.h"

#pragma once
namespace Load
{
	class LoadSphereCookieBounding : public LoadBoundingBase
	{
		////////////////////////////////////////////////////////////////////////////////////////
		DrawCookie::CookieDestroy *mCookieDestroy;
		Collision::BoundingSphere *mBounding;
		////////////////////////////////////////////////////////////////////////////////////////
		void Load(std::string mName);
		////////////////////////////////////////////////////////////////////////////////////////
	public:
		LoadSphereCookieBounding(std::string mFileName, Resource::ResourceBase * mResourceLoad);
		~LoadSphereCookieBounding();
		////////////////////////////////////////////////////////////////////////////////////////
		DrawCookie::CookieDestroy *GetCookieDestroy(void);
		Collision::BoundingSphere *GetSphereBounding(void);
		////////////////////////////////////////////////////////////////////////////////////////
	};
}

