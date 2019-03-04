#include "LoadLowPolyModel.h"


Load::LoadLowPolyModel::LoadLowPolyModel(Resource::ResourceBase *resourceLoad, std::string mName) : resourceLoad(resourceLoad)
{
	Load(mName);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	mVertexBuffer.resize(mVertex.size());
	for (register uint32_t i = 0; i < mVertexBuffer.size(); ++i)
		mVertexBuffer[i] = mVertex[i].l_pos;

	mLowPolyModel = new Collision::LowPolyModel(mVertexBuffer, mIndex);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	mVertex.clear();
	mVertex.shrink_to_fit();
}

Load::LoadLowPolyModel::~LoadLowPolyModel()
{
}

void Load::LoadLowPolyModel::Load(std::string mName)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char *mResource;
	uint64_t mLength;
	uint64_t mOffset = 0;
	resourceLoad->GetResourceFromName(mName.c_str(), (const char **)&mResource, mLength);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint mVertSize = *(reinterpret_cast<GLuint *>(mResource + mOffset));
	mOffset += sizeof(GLuint);

	GLuint mIndexSize = *(reinterpret_cast<GLuint *>(mResource + mOffset));
	mOffset += sizeof(GLuint);

	GLuint mDrawObjectCount = *(reinterpret_cast<GLuint *>(mResource + mOffset));
	mOffset += sizeof(GLuint);

	GLenum mIndexFormat = *(reinterpret_cast<GLuint *>(mResource + mOffset));
	mOffset += sizeof(GLenum);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	mVertSize /= sizeof(MeshLoad::MVertexTex);
	mIndexSize /= sizeof(GLushort);

	mVertex.resize(mVertSize);
	mIndex.resize(mIndexSize);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (register uint32_t i = 0; i < mDrawObjectCount; i++)
	{
		MeshLoad::DrawParamLowPoly mDrawParam = *(reinterpret_cast<MeshLoad::DrawParamLowPoly *>(mResource + mOffset));
		mOffset += sizeof(MeshLoad::DrawParamLowPoly);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	memcpy(mVertex.data(), reinterpret_cast<void *>(mResource + mOffset), mVertSize * sizeof(MeshLoad::MVertexTex));
	mOffset += mVertSize * sizeof(MeshLoad::MVertexTex);

	memcpy(mIndex.data(), reinterpret_cast<void *>(mResource + mOffset), mIndexSize * sizeof(GLushort));
	mOffset += mIndexSize * sizeof(GLushort);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	assert(mOffset == mLength);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete[] mResource;
}

std::vector<MeshLoad::MVertexTex>& Load::LoadLowPolyModel::GetVertexBuffer(void)
{
	return mVertex;
}

std::vector<GLushort>& Load::LoadLowPolyModel::GetElementArray(void)
{
	return mIndex;
}

Collision::LowPolyModel * Load::LoadLowPolyModel::GetLowPolyModel(void)
{
	return mLowPolyModel;
}

