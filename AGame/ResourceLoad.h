#include "ImageResourceLoad.h"
#include "ModelResourceLoad.h"

#pragma once
namespace Resource
{
	class ResourceLoad
	{
		/////////////////////////////////////////////////////////////////////////////////
		ImageResource *mImagesResource;
		/////////////////////////////////////////////////////////////////////////////////
		ModelResourceLoad *mModelResource;
		/////////////////////////////////////////////////////////////////////////////////
		void ReadImages(std::string mResourceName, Resource::ResourceBase *mResourceLoad);
		void ReadModel(std::string mResourceName, Resource::ResourceBase *mResourceLoad);
		/////////////////////////////////////////////////////////////////////////////////
	public:
		ResourceLoad(std::string mResourceName, Resource::ResourceBase *mResourceLoad);
		~ResourceLoad();
		/////////////////////////////////////////////////////////////////////////////////
		ImageResource *GetImagesResource(void);
		/////////////////////////////////////////////////////////////////////////////////
		ModelObject *GetModelObjects(GLuint &mDrawObjectCount);
		/////////////////////////////////////////////////////////////////////////////////
		char *GetVertexBufferData(uint32_t &mVertBufferSize);
		char *GetIndexBufferData(uint32_t &mIdxBufferSize);
		/////////////////////////////////////////////////////////////////////////////////
		GLuint GetVertexBuffer(void);
		GLuint GetIndexBuffer(GLenum &mIndexFormat);
		/////////////////////////////////////////////////////////////////////////////////
	};
}

