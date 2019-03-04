#include "ImageResource.h"


Resource::ImageResource::ImageResource(GLuint *mID, Resource::GLTextureResource *mTextures, GLuint mCount)
{
	for (register uint32_t i = 0; i < mCount; i++)
		mTexturesPerModel.insert(std::make_pair(mID[i], mTextures[i]));
}

Resource::ImageResource::~ImageResource()
{
	for (std::map<GLuint, Resource::GLTextureResource>::iterator m_it = mTexturesPerModel.begin(); m_it != mTexturesPerModel.end(); m_it++)
	{
		glDeleteTextures(1, &m_it->second.texture);
	}

	mTexturesPerModel.clear();
}

Resource::GLTextureResource Resource::ImageResource::GetTextureByID(GLuint mID)
{
	std::map<GLuint, Resource::GLTextureResource>::iterator m_it = mTexturesPerModel.find(mID);

	if (m_it != mTexturesPerModel.end()) return m_it->second;
	else 
	{
		throw L"Error No Texture Find";
		return {};
	}
}
