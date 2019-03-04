#include "DrawPipeBase.h"
#include "DrawPipeDefault.h"
#include "GlobalMove.h"
#include "BarrierManager.h"
#include "ObjectCookie.h"

#pragma once
namespace DrawPipe
{
	class PipeDrawControl
	{
		bool mIntersect;
		////////////////////////////////////////////////////////////////////////////////
		Camera::MCamera *cCamera;
		////////////////////////////////////////////////////////////////////////////////
		GameEngine::DrawPipeBase *mDrawPipe;
		GameEngine::GlobalMove *mGlobalMove;
		////////////////////////////////////////////////////////////////////////////////
		Barrier::BarrierManager* mBarrierManager;
		////////////////////////////////////////////////////////////////////////////////
	public:
		PipeDrawControl(Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource, Camera::MCamera *cCamera,
			float fOffset, float fRadius, uint32_t V_Count, uint32_t U_Count,
			float fFogStart, float fFogRadius, const float *fFogColor, float fCylinderHeight, float fMoveSpeed, float fCookieMinYOffset,
			float mAngle, float fZOffset, float mStepH, int32_t mMinCount, int32_t mMaxCount, int32_t mSectorsCount, float mRotateVelCollect, float mCookieZOffset, Score::Score *mScore);
		~PipeDrawControl();
		////////////////////////////////////////////////////////////////////////////////
		void SetCookieIndexDraw(uint32_t mIndex, Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource,
			float fOffset, float fRadius, uint32_t V_Count, uint32_t U_Count,
			float fFogStart, float fFogRadius, const float *fFogColor);
		////////////////////////////////////////////////////////////////////////////////
		bool Intersect(const Draw::CookieCollisionStruct &mCookieCollision);//const Bounding::ObjectCookie *mCoocieObject, const Bounding::BoundingObjectStructSphere *mCookieBounding);
		////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////
		void SetBarriers(uint32_t mIndex, Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource);
		////////////////////////////////////////////////////////////////////////////////
		void Update(float fDeltaTime, float fGlobalTime);
		////////////////////////////////////////////////////////////////////////////////
		float GetDeltaDistance(void);
		////////////////////////////////////////////////////////////////////////////////
		void Draw(void);
		////////////////////////////////////////////////////////////////////////////////
	};
}
