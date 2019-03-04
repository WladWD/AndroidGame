#include "LoadSphereBounding.h"


Load::LoadSphereBounding::LoadSphereBounding(std::string mFileName, Resource::ResourceBase * mResourceLoad) : LoadBoundingBase(mFileName, mResourceLoad)
{
	Load(mFileName);
}

Load::LoadSphereBounding::~LoadSphereBounding()
{
}

void Load::LoadSphereBounding::Load(std::string mName)
{
	glm::vec4 mCenterRadius;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	char *mResource;
	uint64_t mResourceSize;
	mResourceLoad->GetResourceFromName(mName.c_str(), (const char **)&mResource, mResourceSize);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	mCenterRadius = *(reinterpret_cast<glm::vec4 *>(mResource));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete mResource;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	mBounding = new Collision::BoundingSphere(mCenterRadius);
}

Collision::BoundingSphere *Load::LoadSphereBounding::GetBounding(void)
{
	return mBounding;
}
