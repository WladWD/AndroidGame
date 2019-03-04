#include "LoadSphereCookieBounding.h"


Load::LoadSphereCookieBounding::LoadSphereCookieBounding(std::string mFileName, Resource::ResourceBase * mResourceLoad) : LoadBoundingBase(mFileName, mResourceLoad)
{
	mCookieDestroy = new DrawCookie::CookieDestroy();
	Load(mFileName);

	mBounding = new Collision::BoundingSphere(mCookieDestroy->mCenter);
}

Load::LoadSphereCookieBounding::~LoadSphereCookieBounding()
{
}

void Load::LoadSphereCookieBounding::Load(std::string mName)
{
	const char *mResource;
	uint64_t mResourceSize;
	mResourceLoad->GetResourceFromName(mName.c_str(), &mResource, mResourceSize);

	char *mRes = const_cast<char *>(mResource);
	uint64_t mOffset = 0;

	mCookieDestroy->mCenter = *(reinterpret_cast<glm::vec4 *>(mRes + mOffset));
	mOffset += sizeof(glm::vec4);
	mResourceSize -= sizeof(glm::vec4);

	memcpy(mCookieDestroy->mPicesCenter, reinterpret_cast<glm::vec4 *>(mRes + mOffset), sizeof(mCookieDestroy->mPicesCenter));//mResourceSize);//

	delete mResource;
}

DrawCookie::CookieDestroy * Load::LoadSphereCookieBounding::GetCookieDestroy(void)
{
	return mCookieDestroy;
}

Collision::BoundingSphere * Load::LoadSphereCookieBounding::GetSphereBounding(void)
{
	return mBounding;
}
