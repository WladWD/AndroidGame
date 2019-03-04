#include "LoadImageBase.h"

#pragma once
namespace Load
{
	class LoadImages : public LoadImageBase
	{
		//////////////////////////////////////////////////////
		Resource::ImageResource *mImages;//������� � ���������� ������
		//////////////////////////////////////////////////////
		Resource::GLTextureResource ReadImage(char *mResourceTexture, GLuint &mTextureID, uint32_t &mSize);//read Image and Generate GL_texture_ID
		//////////////////////////////////////////////////////
	public:
		LoadImages(std::string mFileName, Resource::ResourceBase *mResourceLoad);
		~LoadImages();
		//////////////////////////////////////////////////////
		Resource::ImageResource *GetImageResource(void);
	};
}

