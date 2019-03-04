#include "LoadBarrier.h"


Load::LoadBarrier::LoadBarrier(Resource::ResourceBase * resourceLoad, std::string mName) : LoadBase(resourceLoad, mName)
{
	Load(mName);
}

Load::LoadBarrier::~LoadBarrier()
{
	delete mBounding;
	delete mDrawModelLoad;
	delete mLowPolyModel;
}

void Load::LoadBarrier::Load(std::string mFileName)
{
	mDrawModelLoad = new LoadDrawModel(resourceLoad, mFileName);
	mBounding = new LoadAABBBounding(mFileName + "aabb", resourceLoad);
	mLowPolyModel = new LoadLowPolyModel(resourceLoad, mFileName + "lp");
}

Collision::LowPolyModel * Load::LoadBarrier::GetLowPolyModel(void)
{
	return mLowPolyModel->GetLowPolyModel();
}

Collision::BoundingAABB * Load::LoadBarrier::GetAABBBounding(void)
{
	return mBounding->GetAABBBounding();
}
