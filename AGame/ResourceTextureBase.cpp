#include "ResourceTextureBase.h"


TextureResource::ResourceTextureBase::ResourceTextureBase(Resource::MapResource *mMapResource, Resource::TextureLoad * textureLoad, std::string mTextureName)
{
	mTexture = mMapResource->GetResourceByID(textureLoad->LoadFromResource(mTextureName.c_str()));
}

TextureResource::ResourceTextureBase::~ResourceTextureBase()
{
}

const Resource::GLTextureResource & TextureResource::ResourceTextureBase::GetTexture(void)
{
	return mTexture;
}
