#include "ObjectBase.h"
#include "CookieDestroyStruct.h"
#include "ReadCoockieCollisionData.h"

#pragma once
namespace Bounding
{
	//only GLushort - index and VTMesh vertex
	class ObjectCookie : public ObjectBase
	{
	protected:
		//////////////////////////////////////////////////////////////////////////////////
		std::string mResourceName;
		std::string mCollisionObjectName;
		//////////////////////////////////////////////////////////////////////////////////
		DrawCookie::CookieDestroy *mCookieDestroy;
		//////////////////////////////////////////////////////////////////////////////////
		//VTMesh only
		Mesh::VTMesh *vertexBuffer;
		GLushort *indexBuffer;
		//////////////////////////////////////////////////////////////////////////////////
		uint32_t mIndexCollisionCount;
		uint32_t mVertexCollisionCount;
		//////////////////////////////////////////////////////////////////////////////////
		void Init(std::string mResourceName, Resource::ResourceBase *mResourceLoad);//init drawer object
		void InitCollisionModel(std::string mResourceName, Resource::ResourceBase *mResourceLoad);//init collision object
		//////////////////////////////////////////////////////////////////////////////////
	public:
		ObjectCookie(Resource::ResourceBase * mResourceLoad, DrawCookie::CookieDestroy *mCookieDestroy, std::string mResourceName, std::string mCollisionObjectName);
		ObjectCookie(Resource::ResourceBase * mResourceLoad, DrawCookie::CookieDestroy *mCookieDestroy, std::string mResourceName, std::string mCollisionObjectName, std::string mCollisionModelName);
		~ObjectCookie();
		//////////////////////////////////////////////////////////////////////////////////
		DrawCookie::CookieDestroy *GetCookieDestroy(void);
		//////////////////////////////////////////////////////////////////////////////////
		void ReleaseResource(void);
		void ReCreateResource(Resource::ResourceBase *resourceLoad);
		//////////////////////////////////////////////////////////////////////////////////
		Mesh::VTMesh *GetVertexBuffer();
		GLushort *GetIndexBuffer();
		//////////////////////////////////////////////////////////////////////////////////
		uint32_t GetVertexCollisionCount(void);
		uint32_t GetIndexCollisionCount(void);
	};
}