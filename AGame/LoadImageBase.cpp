#include "LoadImageBase.h"


Load::LoadImageBase::LoadImageBase(Resource::ResourceBase *mResourceLoad) : resourceLoad(mResourceLoad)
{
}

Load::LoadImageBase::~LoadImageBase()
{
}

/*
Resource::GLTextureResource Load::LoadImageBase::ReadImage(std::string mFileName)
{
	char *mResource;
	uint64_t mLenght;
	mResourceLoad->GetResourceFromName(mFileName.c_str(), (const char *)&mResource, mLenght);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	mTextureID = *(reinterpret_cast<GLuint *>(mResourceTexture));
	MeshLoad::MainTextureStruct mts = *(reinterpret_cast<MeshLoad::MainTextureStruct *>(mResourceTexture + sizeof(GLuint)));
	MeshLoad::Dim mDim = *(reinterpret_cast<MeshLoad::Dim *>(mResourceTexture + sizeof(MeshLoad::MainTextureStruct) + sizeof(GLuint)));
	GLuint mTexSize = *(reinterpret_cast<GLuint *>(mResourceTexture + sizeof(MeshLoad::MainTextureStruct) + sizeof(MeshLoad::Dim) + sizeof(GLuint)));
	uint8_t *pixels = reinterpret_cast<uint8_t *>(mResourceTexture + sizeof(MeshLoad::MainTextureStruct) + sizeof(MeshLoad::Dim) + sizeof(GLuint) + sizeof(GLuint));

	mSize = sizeof(MeshLoad::MainTextureStruct) + sizeof(MeshLoad::Dim) + sizeof(GLuint) + mTexSize + sizeof(GLuint);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Resource::GLTextureResource glTexRes;
	glTexRes.texture_target = mts.target;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &glTexRes.texture);
	glBindTexture(glTexRes.texture_target, glTexRes.texture);// mts->externalFormat GL_BGR
	glTexImage2D(glTexRes.texture_target, 0, mts.internalFormat, mDim.width, mDim.height, 0, mts.externalFormat, mts.pixelType, pixels);

	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT);//GL_REPEAT
	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glGenerateMipmap(glTexRes.texture_target);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glBindTexture(glTexRes.texture_target, 0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete[] mResource;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return glTexRes;

}

Resource::GLTextureResource Load::LoadImageBase::ReadImage(char * mResourceTexture, GLuint & mTextureID, uint32_t & mSize)
{
	//lod 0 - ONLY  !!!
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	mTextureID = *(reinterpret_cast<GLuint *>(mResourceTexture));
	MeshLoad::MainTextureStruct mts = *(reinterpret_cast<MeshLoad::MainTextureStruct *>(mResourceTexture + sizeof(GLuint)));
	MeshLoad::Dim mDim = *(reinterpret_cast<MeshLoad::Dim *>(mResourceTexture + sizeof(MeshLoad::MainTextureStruct) + sizeof(GLuint)));
	GLuint mTexSize = *(reinterpret_cast<GLuint *>(mResourceTexture + sizeof(MeshLoad::MainTextureStruct) + sizeof(MeshLoad::Dim) + sizeof(GLuint)));
	uint8_t *pixels = reinterpret_cast<uint8_t *>(mResourceTexture + sizeof(MeshLoad::MainTextureStruct) + sizeof(MeshLoad::Dim) + sizeof(GLuint) + sizeof(GLuint));

	mSize = sizeof(MeshLoad::MainTextureStruct) + sizeof(MeshLoad::Dim) + sizeof(GLuint) + mTexSize + sizeof(GLuint);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Resource::GLTextureResource glTexRes;
	glTexRes.texture_target = mts.target;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &glTexRes.texture);
	glBindTexture(glTexRes.texture_target, glTexRes.texture);// mts->externalFormat GL_BGR
	glTexImage2D(glTexRes.texture_target, 0, mts.internalFormat, mDim.width, mDim.height, 0, mts.externalFormat, mts.pixelType, pixels);

	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT);//GL_REPEAT
	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glGenerateMipmap(glTexRes.texture_target);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glBindTexture(glTexRes.texture_target, 0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return glTexRes;
}
*/