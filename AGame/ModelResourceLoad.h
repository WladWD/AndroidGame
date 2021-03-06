#include "ModelObject.h"
#include "ResourceBase.h"
#include "Mesh.h"
#include <vector>

#pragma once
namespace Resource
{
	struct DrawParam
	{
		GLuint mIndexOffset;
		GLuint mIndexCount;
		GLuint mImageCount;
	};

	class ModelResourceLoad
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		uint32_t mVertBufferSize;
		uint32_t mIdxBufferSize;
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		char *mVertBuffer;
		char *mIdxBuffer;
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		ModelObject *mObjects;
		GLuint mDrawObjectCount;
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		GLenum mIndexFormat;
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		GLuint mVertexBuffer;//vertex buffer object
		GLuint mIndexBuffer;//element array object
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		void ReadObject(char *mResourceModel, uint32_t index, uint32_t &mSize);
	public:
		ModelResourceLoad(std::string mResourceName, Resource::ResourceBase *mResourceLoad);
		~ModelResourceLoad();
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		ModelObject *GetModelObjects(GLuint &mDrawObjectCount);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		char *GetVertexBufferData(uint32_t &mVertBufferSize);
		char *GetIndexBufferData(uint32_t &mIdxBufferSize);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		GLuint GetVertexBuffer(void);
		GLuint GetIndexBuffer(GLenum &mIndexFormat);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
	};
}

