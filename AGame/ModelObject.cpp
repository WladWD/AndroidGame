#include "ModelObject.h"


Resource::ModelObject::ModelObject(void) : mIndexCount(0), mIndexOffset(0), mTextureCount(0)
{
}

Resource::ModelObject::~ModelObject()
{
	delete mTextureIDs;
}

void Resource::ModelObject::Init(GLuint mIndexCount, GLuint mIndexOffset)
{
	this->mIndexCount = mIndexCount;
	this->mIndexOffset = mIndexOffset;
}

void Resource::ModelObject::AppendTextures(GLuint * mTextureIDs, GLuint mTextureCount)
{
	this->mTextureIDs = mTextureIDs;
	this->mTextureCount = mTextureCount;
}

const GLuint & Resource::ModelObject::GetIndexCount(void)
{
	return mIndexCount;
}

const GLuint & Resource::ModelObject::GetIndexOffset(void)
{
	return mIndexOffset;
}

GLuint Resource::ModelObject::GetTextureID(GLuint mNumTexture)
{
	if(mNumTexture < mTextureCount)
		return mTextureIDs[mNumTexture];
	else 
	{
		throw L"Error Indexed Texture";
		return (-1);
	}
}
