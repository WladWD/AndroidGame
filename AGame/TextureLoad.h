#include "MapResource.h"
#include "ResourceBase.h"
#include "LoadImageBase.h"

#pragma once
namespace Resource 
{
	class TextureLoad : public Load::LoadImageBase
	{
		MapResource *mapResource;
		//Resource::ResourceBase *resourceLoad;
		///////////////////////////////////////////////////////////////////////////////
		Resource::GLTextureResource LoadFromResourceImage(const char *ResourceName);
		///////////////////////////////////////////////////////////////////////////////
	public:
		TextureLoad(MapResource *mapResource, Resource::ResourceBase *resourceLoad);
		~TextureLoad();
		///////////////////////////////////////////////////////////////////////////////
		uint32_t LoadFromResource(const char *ResourceName);
		///////////////////////////////////////////////////////////////////////////////
	};
}

