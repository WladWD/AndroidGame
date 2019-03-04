#include "BarrierSetBase.h"
#include "DrawBarrierRotor.h"
#include "Cookie.h"
#include "CollectControll.h"
#include "DrawBarrierStatic.h"

#pragma once
namespace Barrier
{
	class BarrierSetDefault : public BarrierSetBase
	{
		float mStaticStepMin, mStaticStepMax;
		float mDynamicStepMin, mDynamicStepMax;
		//////////////////////////////////////////////////////////////////////////////////
		std::vector<int32_t> mPresentVec;
		//////////////////////////////////////////////////////////////////////////////////
		Draw::CollectControllBase *mCollect;
		//////////////////////////////////////////////////////////////////////////////////
		float fCookieMinYOffset;
		//////////////////////////////////////////////////////////////////////////////////
		glm::vec2 fFog;
		const float *fFogColor;
		//////////////////////////////////////////////////////////////////////////////////
		int32_t Random(int32_t b, int32_t e);
		void RandomizePresent(void);
		void InitShaders(Resource::ResourceBase * mResourceLoad);
		void InitBoundingObjects(Resource::ResourceBase * mResourceLoad);
		//////////////////////////////////////////////////////////////////////////////////
		void InitBarriers(Resource::ResourceBase * mResourceLoad, int32_t mStaticBarriers = 12, int32_t mDynamicBarriers = 12);
	public:
		BarrierSetDefault(Resource::ResourceBase * mResourceLoad, Camera::MCamera *cCamera, GameEngine::GlobalMove *mGloablMove,
			float fStep, float fHeight, glm::vec2 fFog, const float *fFogColor, float fCookieMinYOffset,
			float mAngle, float fZOffset, float mStepH, int32_t mMinCount, int32_t mMaxCount, int32_t mSectorsCount, float mRotateVelCollect, 
			Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad, float mCookieZOffset, Score::Score *mScore);
		~BarrierSetDefault();
		//////////////////////////////////////////////////////////////////////////////////
		void DrawBarriers(void);
		//////////////////////////////////////////////////////////////////////////////////
		bool Intersect(const Draw::CookieCollisionStruct &mCookieCollision);
		//////////////////////////////////////////////////////////////////////////////////
		void Update(float fDeltaTime, float fGlobalTime);
		//////////////////////////////////////////////////////////////////////////////////
		void Present(void);
		//////////////////////////////////////////////////////////////////////////////////
	};
}

