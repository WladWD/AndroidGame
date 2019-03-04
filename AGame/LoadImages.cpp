#include "LoadImages.h"



Load::LoadImages::LoadImages(std::string mFileName, Resource::ResourceBase * mResourceLoad) : LoadImageBase(mResourceLoad)
{
	const char *cpRes;
	char *Resource, *pRes;
	uint64_t length;
	mResourceLoad->GetResourceFromName(mFileName.c_str(), &cpRes, length);
	Resource = const_cast<char *>(cpRes);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint mTextureCount = *(reinterpret_cast<GLuint *>(Resource));

	pRes = Resource + sizeof(GLuint);

	GLuint *mTexturesIDs = new GLuint[mTextureCount];
	Resource::GLTextureResource *mGLTexturesIDs = new Resource::GLTextureResource[mTextureCount];
	for (register uint32_t i = 0; i < mTextureCount; i++)
	{
		uint32_t mSize;
		mGLTexturesIDs[i] = ReadImage(pRes, mTexturesIDs[i], mSize);
		pRes += mSize;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	mImages = new Resource::ImageResource(mTexturesIDs, mGLTexturesIDs, mTextureCount);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete[] Resource;
	delete[] mTexturesIDs;
	delete[] mGLTexturesIDs;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

Load::LoadImages::~LoadImages()
{
}

Resource::GLTextureResource Load::LoadImages::ReadImage(char * mResourceTexture, GLuint & mTextureID, uint32_t & mSize)
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

Resource::ImageResource * Load::LoadImages::GetImageResource(void)
{
	return mImages;
}
