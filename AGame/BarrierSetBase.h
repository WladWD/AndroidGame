#include "BarrierBase.h"
#include "GlobalMove.h"
#include "Object.h"
#include <vector>

#pragma once
namespace Barrier
{
	class BarrierSetBase
	{
	protected:
		//////////////////////////////////////////////////////////////////////////////////
		Camera::MCamera *cCamera;
		GameEngine::GlobalMove *mGloablMove;
		//////////////////////////////////////////////////////////////////////////////////
		float fHeight, fStep;
		//////////////////////////////////////////////////////////////////////////////////
		std::vector<uint32_t> mIntersectIndexes;
		//////////////////////////////////////////////////////////////////////////////////
		std::vector<BarrierBase *> mBarriers;
		std::vector<bool> mBarriersType;
		std::vector<Shader::ShaderBarrierBase *> mShaders;
		std::vector<Draw::Barrier *> mBarrierData;
		//////////////////////////////////////////////////////////////////////////////////
		virtual void InitBarriers(Resource::ResourceBase * mResourceLoad, int32_t mStaticBarriers, int32_t mDynamicBarriers) = 0;
	public:
		BarrierSetBase(float fStep, float fHeight, Camera::MCamera *cCamera, GameEngine::GlobalMove *mGloablMove);
		virtual ~BarrierSetBase();
		//////////////////////////////////////////////////////////////////////////////////
		virtual bool Intersect(const Draw::CookieCollisionStruct &mCookieCollision) = 0;
		//////////////////////////////////////////////////////////////////////////////////
		virtual void DrawBarriers(void) = 0;
		//////////////////////////////////////////////////////////////////////////////////
		virtual void Update(float fDeltaTime, float fGlobalTime) = 0;
		//////////////////////////////////////////////////////////////////////////////////
		virtual void Present(void) = 0;
		//////////////////////////////////////////////////////////////////////////////////
	};
}

