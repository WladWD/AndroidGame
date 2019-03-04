#include "LoadCollect.h"


Load::LoadCollect::LoadCollect(Resource::ResourceBase * resourceLoad, std::string mName) : LoadBase(resourceLoad, mName)
{
	Load(mName);
}

Load::LoadCollect::~LoadCollect()
{
	delete mBounding;
	delete mDrawModelLoad;
}

void Load::LoadCollect::Load(std::string mFileName)
{
	mDrawModelLoad = new LoadDrawModel(resourceLoad, mFileName);
	mBounding = new LoadSphereBounding(mFileName + "spc", resourceLoad);
}

Collision::BoundingSphere * Load::LoadCollect::GetSphereBounding(void)
{
	return mBounding->GetBounding();
}
