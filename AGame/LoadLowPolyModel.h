#include "LoadModelBase.h"
#include "LowPolyModel.h"

#pragma once
namespace Load
{
	class LoadLowPolyModel
	{
		//////////////////////////////////////////////////////////////
		Collision::LowPolyModel *mLowPolyModel;
	protected:
		Resource::ResourceBase *resourceLoad;
		//////////////////////////////////////////////////////////////
		std::vector<glm::vec3> mVertexBuffer;
		//////////////////////////////////////////////////////////////
		std::vector<MeshLoad::MVertexTex> mVertex;
		std::vector<GLushort> mIndex;
		//////////////////////////////////////////////////////////////
		void Load(std::string mName);
		//////////////////////////////////////////////////////////////
	public:
		LoadLowPolyModel(Resource::ResourceBase *resourceLoad, std::string mName);
		~LoadLowPolyModel();
		//////////////////////////////////////////////////////////////
		std::vector<MeshLoad::MVertexTex> &GetVertexBuffer(void);
		std::vector<GLushort> &GetElementArray(void);
		//////////////////////////////////////////////////////////////
		Collision::LowPolyModel *GetLowPolyModel(void);
		//////////////////////////////////////////////////////////////
	};
}
/*

struct MVertexTex
{
glm::vec3 l_pos;
glm::vec2 l_tex;
};

std::ofstream mof(mFileName, std::ios::binary | std::ios::out);

	GLuint mVertSize = mBuffers->m_vertex.size() * sizeof(MeshLoad::MVertexTex);
	GLuint mIndexSize = mBuffers->m_index.size() * sizeof(GLushort);
	GLuint mDrawObjectCount = mObjects->mEntries.size();
	GLenum mIndexFormat = GL_UNSIGNED_SHORT;

	mof.write(reinterpret_cast<const char *>(&mVertSize), sizeof(GLuint));
	mof.write(reinterpret_cast<const char *>(&mIndexSize), sizeof(GLuint));
	mof.write(reinterpret_cast<const char *>(&mDrawObjectCount), sizeof(GLuint));
	mof.write(reinterpret_cast<const char *>(&mIndexFormat), sizeof(GLenum));

	for (register uint32_t i = 0; i < mDrawObjectCount; i++)
	{
		DrawParamLowPoly mDrawParam;
		mDrawParam.mIndexCount = mObjects->mEntries[i].GetIndexCount();
		mDrawParam.mIndexOffset = mObjects->mEntries[i].GetStartIndex();

		mof.write(reinterpret_cast<const char *>(&mDrawParam), sizeof(DrawParamLowPoly));
	}

	mof.write(reinterpret_cast<const char *>(mBuffers->m_vertex.data()), mVertSize);
	mof.write(reinterpret_cast<const char *>(mBuffers->m_index.data()), mIndexSize);

	mof.close();*/
