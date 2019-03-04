#include "DrawObject.h"
#include "LowPolyModelInstance.h"
#include "BoundingSphereInstance.h"

#pragma once
namespace Draw
{
	struct CookieCollisionStruct 
	{
		const Collision::LowPolyModelInstance *mLowpolyModel;
		const Collision::BoundingSphereInstance *mBoundingCookie;
	};

	class Cookie : public DrawObject
	{
		//////////////////////////////////////////////////////////////////////////////////////
		Collision::LowPolyModel *mLowpolyModel;
		DrawCookie::CookieDestroy *mCookieDestroy;
		Collision::BoundingSphere *mBoundingCookie;
		//////////////////////////////////////////////////////////////////////////////////////
	public:
		Cookie(Resource::ResourceBase *resourceLoad, std::string mName);
		~Cookie();
		//////////////////////////////////////////////////////////////////////////////////////
		Collision::LowPolyModel *GetLowPolyModel(void);
		DrawCookie::CookieDestroy *GetCookieDestroy(void);
		Collision::BoundingSphere *GetBoundingSphere(void);
		//////////////////////////////////////////////////////////////////////////////////////
	};
}

