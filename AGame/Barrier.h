#include "DrawObject.h"
#include "LowPolyModelInstance.h"
#include "BoundingAABBInstance.h"
#include "LoadBarrier.h"

#pragma once
namespace Draw
{
	struct BarrierCollisionStruct
	{
		const Collision::LowPolyModelInstance *mLowpolyModel;
		const Collision::BoundingAABBInstance *mBounding;
	};

	class Barrier : public DrawObject
	{
		//////////////////////////////////////////////////////////////////////////////////////
		Collision::LowPolyModel *mLowpolyModel;
		Collision::BoundingAABB *mBounding;
		//////////////////////////////////////////////////////////////////////////////////////
	public:
		Barrier(Resource::ResourceBase *resourceLoad, std::string mName);
		~Barrier();
		//////////////////////////////////////////////////////////////////////////////////////
		Collision::LowPolyModel *GetLowPolyModel(void);
		Collision::BoundingAABB *GetBoundingAABB(void);
		//////////////////////////////////////////////////////////////////////////////////////
	};
}

