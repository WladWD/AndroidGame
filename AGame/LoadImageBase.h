#include "ImageResource.h"
#include "ResourceBase.h"
#include <string> 

#pragma once
namespace Load
{
	class LoadImageBase
	{
	protected:
		//////////////////////////////////////////////////////
		Resource::ResourceBase *resourceLoad;
		//////////////////////////////////////////////////////
		//virtual Resource::GLTextureResource ReadImage(std::string mFileName);
		//virtual Resource::GLTextureResource ReadImage(char *mResourceTexture, GLuint &mTextureID, uint32_t &mSize);//read Image and Generate GL_texture_ID
		//////////////////////////////////////////////////////
	public:
		LoadImageBase(Resource::ResourceBase *mResourceLoad);
		virtual ~LoadImageBase();
		//////////////////////////////////////////////////////
	};
}

