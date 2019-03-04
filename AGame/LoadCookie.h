#include "LoadBase.h"
#include "LoadSphereCookieBounding.h"

#pragma once
namespace Load
{
	class LoadCookie : public LoadBase
	{
		//////////////////////////////////////////////////////////////////////////////////
		LoadSphereCookieBounding *mBounding;
		LoadLowPolyModel *mLowPolyModel;
		//////////////////////////////////////////////////////////////////////////////////
		void Load(std::string mFileName);
	public:
		LoadCookie(Resource::ResourceBase *resourceLoad, std::string mName);
		~LoadCookie();
		//////////////////////////////////////////////////////////////////////////////////
		Collision::LowPolyModel *GetLowPolyModel(void);
		DrawCookie::CookieDestroy *GetCookieDestroy(void);
		Collision::BoundingSphere *GetSphereBounding(void);
		//////////////////////////////////////////////////////////////////////////////////
	};
}

