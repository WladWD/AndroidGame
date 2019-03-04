#include "LoadAABBBounding.h"


Load::LoadAABBBounding::LoadAABBBounding(std::string mFileName, Resource::ResourceBase * mResourceLoad) : LoadBoundingBase(mFileName, mResourceLoad)
{
	Load(mFileName);
}

Load::LoadAABBBounding::~LoadAABBBounding()
{
}

void Load::LoadAABBBounding::Load(std::string mName)
{
	MeshLoad::AABBStruct mAABB;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	char *mResource;
	uint64_t mResourceSize;
	mResourceLoad->GetResourceFromName(mName.c_str(), (const char **)&mResource, mResourceSize);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	mAABB = *(reinterpret_cast<MeshLoad::AABBStruct *>(mResource));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete mResource;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	mBounding = new Collision::BoundingAABB(mAABB.mCenter, mAABB.mExtent);
}

Collision::BoundingAABB * Load::LoadAABBBounding::GetAABBBounding(void)
{
	return mBounding;
}
