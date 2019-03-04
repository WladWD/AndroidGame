#include "ImageResource.h"
#include "ResourceBase.h"
#include <string>

#pragma once
namespace Resource
{
	class ImageResourceLoad
	{
		//////////////////////////////////////////////////////
		ImageResource *mImages;//удалить в содержащеи классе
		//////////////////////////////////////////////////////
		Resource::GLTextureResource ReadImage(char *mResourceTexture, GLuint &mTextureID, uint32_t &mSize);//read Image and Generate GL_texture_ID
		//////////////////////////////////////////////////////
	public:
		ImageResourceLoad(std::string mFileName, Resource::ResourceBase *mResourceLoad);
		~ImageResourceLoad();
		//////////////////////////////////////////////////////
		ImageResource *GetImageResource(void);
	};
}

