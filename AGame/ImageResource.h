#include "MHeder.h"
#include "LoadStructure.h"
#include <map>

#pragma once
namespace Resource
{
	class ImageResource
	{
		///////////////////////////////////////////////////////////////////////
		std::map<GLuint, Resource::GLTextureResource> mTexturesPerModel;//key - image ID, value - Resource::GLTextureResource
		///////////////////////////////////////////////////////////////////////
	public:
		ImageResource(GLuint *mID, Resource::GLTextureResource *mTextures, GLuint mCount);
		~ImageResource();
		///////////////////////////////////////////////////////////////////////
		Resource::GLTextureResource GetTextureByID(GLuint mID);
		///////////////////////////////////////////////////////////////////////
	};
}

