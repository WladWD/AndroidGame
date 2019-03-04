#include "Barrier.h"


Draw::Barrier::Barrier(Resource::ResourceBase *resourceLoad, std::string mName)
{
	//////////////////////////////////////////////////////////////////////////////////////////
	Load::LoadBarrier *mLoadBarrier = new Load::LoadBarrier(resourceLoad, mName);
	//////////////////////////////////////////////////////////////////////////////////////////
	mLowpolyModel = mLoadBarrier->GetLowPolyModel();
	mBounding = mLoadBarrier->GetAABBBounding();
	mModelDraw = mLoadBarrier->GetModel();
	//////////////////////////////////////////////////////////////////////////////////////////
	delete mLoadBarrier;
	//////////////////////////////////////////////////////////////////////////////////////////
}

Draw::Barrier::~Barrier()
{
	delete mLowpolyModel;
	delete mBounding;
	delete mModelDraw;
}

Collision::LowPolyModel * Draw::Barrier::GetLowPolyModel(void)
{
	return mLowpolyModel;
}

Collision::BoundingAABB * Draw::Barrier::GetBoundingAABB(void)
{
	return mBounding;
}
