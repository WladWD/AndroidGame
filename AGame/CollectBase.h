#include "ResourceLoad.h"
#include "ShaderCookieBase.h"
#include "Mesh.h"
#include "LoadStructure.h"
#include "ObjectCookie.h"
#include "BoundingObjectStructSphere.h"
#include "MCamera.h"
#include "Collect.h"
#include "BoundingSphereInstance.h"
#include "LowPolyModelInstance.h"
#include "Cookie.h"

#pragma once
namespace Draw
{
	class CollectBase
	{
	protected:
		/////////////////////////////////////////////////////////////////////////////////////
		bool mIntersect, mPicked;
		/////////////////////////////////////////////////////////////////////////////////////
		const double PI = 3.14151926;
		/////////////////////////////////////////////////////////////////////////////////////
		float mHeight, mAngle;
		/////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 mWorld;
		float mDeltaConst;
		/////////////////////////////////////////////////////////////////////////////////////
		Collision::ModelBase *mModelDraw;
		Collision::BoundingSphereInstance *mSphere;
		/////////////////////////////////////////////////////////////////////////////////////
		Camera::MCamera *cCamera;
		/////////////////////////////////////////////////////////////////////////////////////
		virtual void InitAttrib(void) = 0;
		/////////////////////////////////////////////////////////////////////////////////////
		virtual void DrawEvent(void) = 0;
	public:
		CollectBase(Draw::Collect *mCollect, Camera::MCamera *cCamera, float mHeight, float mAngle);
		virtual ~CollectBase();
		/////////////////////////////////////////////////////////////////////////////////////
		virtual bool Intersect(const Draw::CookieCollisionStruct &mCookieCollision) = 0;
		virtual void Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight) = 0;
		virtual void Draw(void) = 0;
		virtual void DrawFlash(void) = 0;
		virtual bool IsCollected(void) = 0;
		/////////////////////////////////////////////////////////////////////////////////////
		virtual bool Present(float mHeight, float mAngle, float mRotateVel) = 0;
		/////////////////////////////////////////////////////////////////////////////////////
		float GetHeight(void);
		/////////////////////////////////////////////////////////////////////////////////////
		const Collision::BoundingSphereInstance *GetBoundingSphere(void);
		/////////////////////////////////////////////////////////////////////////////////////
	};
}

