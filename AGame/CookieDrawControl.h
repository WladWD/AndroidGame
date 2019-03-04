#include "DrawCookieBase.h"
#include "DrawCookieStandart.h"
#include "EndGameDraw.h"
#include "Object.h"
#include "ObjectCookie.h"
#include "LoadCookie.h"

#pragma once
namespace DrawCookie
{
	class CookieDrawControl
	{
		/*Collision::LowPolyModel *mLowpolyModel;
		DrawCookie::CookieDestroy *mCookieDestroy;
		Collision::BoundingSphere *mBoundingCookie;
		Collision::ModelBase *mModelDraw;*/
		Draw::Cookie *mCookie;
		/////////////////////////////////////////////////////////////////////////////////////
		//Bounding::ObjectCookie *mObject;
		/////////////////////////////////////////////////////////////////////////////////////
		Camera::MCamera *cCamera;
		/////////////////////////////////////////////////////////////////////////////////////
		DrawCookieBase *mCookieDraw;
		/////////////////////////////////////////////////////////////////////////////////////
	public:
		CookieDrawControl(Resource::ResourceBase *mResourceLoad, Camera::MCamera *cCamera, DrawCookie::CookieDestroy **mCookieDestroy, float fZOffset, float fYOffset, float fScale);
		~CookieDrawControl();
		/////////////////////////////////////////////////////////////////////////////////////
		void SetCookieIndexDraw(uint32_t mIndex, Resource::ResourceBase * mResourceLoad, DrawCookie::CookieDestroy **mCookieDestroy, float fZOffset, float fYOffset, float fScale);
		/////////////////////////////////////////////////////////////////////////////////////
		void Update(float fDeltaTime, float fGlobalTime);
		/////////////////////////////////////////////////////////////////////////////////////
		//const Bounding::ObjectCookie *GetObjectData(void);
		//const Collision::BoundingSphereInstance *GetBoundingObject(void);
		Draw::CookieCollisionStruct GetCookieCollision(void);
		/////////////////////////////////////////////////////////////////////////////////////
		void Draw(void);
		void DrawDestroyCookie(void);
		/////////////////////////////////////////////////////////////////////////////////////
	};
}

