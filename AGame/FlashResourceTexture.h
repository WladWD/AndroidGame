#include "ResourceTextureBase.h"

#pragma once
namespace DrawFlash
{
	class FlashResourceTexture : public TextureResource::ResourceTextureBase
	{
		////////////////////////////////////////////////////////////////////////////////
	//	Resource::GLTextureResource mFlashTexture;
		////////////////////////////////////////////////////////////////////////////////
	public:
		FlashResourceTexture(Resource::MapResource *mMapResource, Resource::TextureLoad *textureLoad, std::string mFlashTextureName);
		~FlashResourceTexture();
		////////////////////////////////////////////////////////////////////////////////
		//const Resource::GLTextureResource &GetFlashTexture(void);
		////////////////////////////////////////////////////////////////////////////////
	};
}
