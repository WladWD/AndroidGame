#include "LoadDrawModel.h"


Load::LoadDrawModel::LoadDrawModel(Resource::ResourceBase * resourceLoad, std::string mName) : mResourceLoad(resourceLoad)
{
	Load(mName);

	mModelBase = new Collision::ModelBase(mObjects, mDrawObjectCount, mIndexBuffer, mVertexBuffer, mIndexFormat, mImagesResource);
}

Load::LoadDrawModel::~LoadDrawModel()
{
}

Collision::ModelBase * Load::LoadDrawModel::GetDrawModel(void)
{
	return mModelBase;
}

void Load::LoadDrawModel::Load(std::string mName)
{
	ReadModel(mName);
	ReadImages(mName);
}

void Load::LoadDrawModel::ReadImages(std::string mResourceName)
{
	std::string mImageName = mResourceName.substr(0, mResourceName.find_last_of('.')) + ".tifm";
	LoadImages *mImageResourceLoad = new LoadImages(mImageName, mResourceLoad);

	mImagesResource = mImageResourceLoad->GetImageResource();

	delete mImageResourceLoad;
}

void Load::LoadDrawModel::ReadModel(std::string mResourceName)
{
	Resource::ModelResourceLoad *mModelResource = new Resource::ModelResourceLoad(mResourceName, mResourceLoad);

	mIndexBuffer = mModelResource->GetIndexBuffer(mIndexFormat);
	mVertexBuffer = mModelResource->GetVertexBuffer();
	mObjects = mModelResource->GetModelObjects(mDrawObjectCount);

	delete mModelResource;
}