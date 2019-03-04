#include "ModelResourceLoad.h"


Resource::ModelResourceLoad::ModelResourceLoad(std::string mResourceName, Resource::ResourceBase * mResourceLoad)
{
	const char *cpRes;
	char *Resource, *pRes;
	uint64_t length;
	mResourceLoad->GetResourceFromName(mResourceName.c_str(), &cpRes, length);
	Resource = const_cast<char *>(cpRes);

	pRes = Resource;

	GLuint mVertSize;
	GLuint mIndexSize;

	mVertSize = *(reinterpret_cast<GLuint *>(pRes));
	pRes += sizeof(GLuint);

	mIndexSize = *(reinterpret_cast<GLuint *>(pRes));
	pRes += sizeof(GLuint);

	mDrawObjectCount = *(reinterpret_cast<GLuint *>(pRes));
	pRes += sizeof(GLuint);

	mIndexFormat = *(reinterpret_cast<GLuint *>(pRes));
	pRes += sizeof(GLuint);

	mObjects = new ModelObject[mDrawObjectCount];

	for (register uint32_t i = 0; i < mDrawObjectCount; i++)
	{
		uint32_t mSize;
		ReadObject(pRes, i, mSize);
		pRes += mSize;
	}

	//////////////////////////////////////////////////////////////////////////////////////
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	mVertBufferSize = mVertSize;
	mVertBuffer = new char[mVertSize];
	memcpy(mVertBuffer, pRes, mVertSize);

	//Mesh::VTMesh *mMesh = (Mesh::VTMesh *)mVertBuffer;

	glBufferData(GL_ARRAY_BUFFER, mVertSize, mVertBuffer, GL_STATIC_DRAW);
	//////////////////////////////////////////////////////////////////////////////////////
	pRes += mVertSize;
	//////////////////////////////////////////////////////////////////////////////////////
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	mIdxBufferSize = mIndexSize;
	mIdxBuffer = new char[mIndexSize];
	memcpy(mIdxBuffer, pRes, mIndexSize);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexSize, mIdxBuffer, GL_STATIC_DRAW);
	//////////////////////////////////////////////////////////////////////////////////////
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] Resource;
}

Resource::ModelResourceLoad::~ModelResourceLoad()
{
	delete[] mVertBuffer;
	delete[] mIdxBuffer;
}

void Resource::ModelResourceLoad::ReadObject(char * mResourceModel, uint32_t index, uint32_t & mSize)
{
	mSize = sizeof(DrawParam);

	DrawParam mDrawParam;
	mDrawParam = *(reinterpret_cast<DrawParam *>(mResourceModel));
	
	mObjects[index].Init(mDrawParam.mIndexCount, mDrawParam.mIndexOffset);

	GLuint *mTextures = new GLuint[mDrawParam.mImageCount];
	for (register uint32_t j = 0; j < mDrawParam.mImageCount; j++)
	{
		GLuint mDiffuseID;
		mDiffuseID = *(reinterpret_cast<GLuint *>(mResourceModel + mSize));
		mTextures[j] = mDiffuseID;

		mSize += sizeof(GLuint);
	}

	mObjects[index].AppendTextures(mTextures, mDrawParam.mImageCount);
}

char *Resource::ModelResourceLoad::GetVertexBufferData(uint32_t &mVertBufferSize) 
{
	mVertBufferSize = this->mVertBufferSize;
	char *data = new char[mVertBufferSize];
	memcpy(data, mVertBuffer, mVertBufferSize);
	return data;
}

char *Resource::ModelResourceLoad::GetIndexBufferData(uint32_t &mIdxBufferSize) 
{
	mIdxBufferSize = this->mIdxBufferSize;
	char *data = new char[mIdxBufferSize];
	memcpy(data, mIdxBuffer, mIdxBufferSize);
	return data;
}

Resource::ModelObject * Resource::ModelResourceLoad::GetModelObjects(GLuint & mDrawObjectCount)
{
	mDrawObjectCount = this->mDrawObjectCount;
	return mObjects;
}

GLuint Resource::ModelResourceLoad::GetVertexBuffer(void)
{
	return mVertexBuffer;
}

GLuint Resource::ModelResourceLoad::GetIndexBuffer(GLenum &mIndexFormat)
{
	mIndexFormat = this->mIndexFormat;
	return mIndexBuffer;
}
