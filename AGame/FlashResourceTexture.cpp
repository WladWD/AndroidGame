#include "FlashResourceTexture.h"


DrawFlash::FlashResourceTexture::FlashResourceTexture(Resource::MapResource *mMapResource, Resource::TextureLoad * textureLoad, std::string mFlashTextureName) : 
	TextureResource::ResourceTextureBase(mMapResource, textureLoad, mFlashTextureName)
{
	//mFlashTexture = mMapResource->GetResourceByID(textureLoad->LoadFromResource(mFlashTextureName.c_str()));
}

DrawFlash::FlashResourceTexture::~FlashResourceTexture()
{
}

//const Resource::GLTextureResource & DrawFlash::FlashResourceTexture::GetFlashTexture(void)
//{
//	return mFlashTexture;
//}
