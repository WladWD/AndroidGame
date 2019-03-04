#include "ReadCoockieCollisionData.h"



Bounding::ReadCoockieCollisionData::ReadCoockieCollisionData(std::string mFileName, Resource::ResourceBase * mResourceLoad, DrawCookie::CookieDestroy *mCookieDestroy) : 
	ReadCollisionObjectDataBase(), mCookieDestroy(mCookieDestroy)
{
	ReadCollisionData(mFileName, mResourceLoad);
}

Bounding::ReadCoockieCollisionData::~ReadCoockieCollisionData()
{
}

void Bounding::ReadCoockieCollisionData::ReadCollisionData(std::string mFileName, Resource::ResourceBase * mResourceLoad)
{
	const char *mResource;
	uint64_t mResourceSize;
	mResourceLoad->GetResourceFromName(mFileName.c_str(), &mResource, mResourceSize);

	char *mRes = const_cast<char *>(mResource);
	uint64_t mOffset = 0;

	mCookieDestroy->mCenter = *(reinterpret_cast<glm::vec4 *>(mRes + mOffset));
	mOffset += sizeof(glm::vec4);
	mResourceSize -= sizeof(glm::vec4);

	memcpy(mCookieDestroy->mPicesCenter, reinterpret_cast<glm::vec4 *>(mRes + mOffset), sizeof(mCookieDestroy->mPicesCenter));//mResourceSize);//

	delete mResource;
}
