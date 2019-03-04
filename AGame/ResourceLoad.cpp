#include "ResourceLoad.h"


Resource::ResourceLoad::ResourceLoad(std::string mResourceName, Resource::ResourceBase * mResourceLoad)
{
	ReadImages(mResourceName, mResourceLoad);
	ReadModel(mResourceName, mResourceLoad);
}

Resource::ResourceLoad::~ResourceLoad()
{
	delete mModelResource;
}

void Resource::ResourceLoad::ReadImages(std::string mResourceName, Resource::ResourceBase *mResourceLoad)
{
	std::string mImageName = mResourceName.substr(0, mResourceName.find_last_of('.')) + ".tifm";
	ImageResourceLoad *mImageResourceLoad = new ImageResourceLoad(mImageName, mResourceLoad);

	mImagesResource = mImageResourceLoad->GetImageResource();

	delete mImageResourceLoad;
}

void Resource::ResourceLoad::ReadModel(std::string mResourceName, Resource::ResourceBase *mResourceLoad)
{
	mModelResource = new ModelResourceLoad(mResourceName, mResourceLoad);
}

Resource::ImageResource * Resource::ResourceLoad::GetImagesResource(void)
{
	return mImagesResource;
}

Resource::ModelObject * Resource::ResourceLoad::GetModelObjects(GLuint & mDrawObjectCount)
{
	return mModelResource->GetModelObjects(mDrawObjectCount);
}

char *Resource::ResourceLoad::GetVertexBufferData(uint32_t &mVertBufferSize)
{
	return mModelResource->GetVertexBufferData(mVertBufferSize);
}

char *Resource::ResourceLoad::GetIndexBufferData(uint32_t &mIdxBufferSize)
{
	return mModelResource->GetIndexBufferData(mIdxBufferSize);
}

GLuint Resource::ResourceLoad::GetVertexBuffer(void)
{
	return mModelResource->GetVertexBuffer();
}

GLuint Resource::ResourceLoad::GetIndexBuffer(GLenum & mIndexFormat)
{
	return mModelResource->GetIndexBuffer(mIndexFormat);
}
