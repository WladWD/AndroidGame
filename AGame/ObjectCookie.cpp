#include "ObjectCookie.h"


Bounding::ObjectCookie::ObjectCookie(Resource::ResourceBase * mResourceLoad, DrawCookie::CookieDestroy *mCookieDestroy, std::string mResourceName, std::string mCollisionObjectName) : 
	ObjectBase(), mCookieDestroy(mCookieDestroy), mResourceName(mResourceName), mCollisionObjectName(mCollisionObjectName)
{
	Init(mResourceName, mResourceLoad);
	Bounding::ReadCoockieCollisionData *mCookieCollision = new Bounding::ReadCoockieCollisionData(mCollisionObjectName, mResourceLoad, mCookieDestroy);
	//InitCollisionModel(, mResourceLoad);
	delete mCookieCollision;
}

Bounding::ObjectCookie::ObjectCookie(Resource::ResourceBase * mResourceLoad, DrawCookie::CookieDestroy *mCookieDestroy, std::string mResourceName,
	std::string mCollisionObjectName, std::string mCollisionModelName) : ObjectBase(), mCookieDestroy(mCookieDestroy)
{
	//Init(mResourceName, mResourceLoad);
}

Bounding::ObjectCookie::~ObjectCookie()
{
	delete[] vertexBuffer;
	delete[] indexBuffer;
}

DrawCookie::CookieDestroy * Bounding::ObjectCookie::GetCookieDestroy(void)
{
	return mCookieDestroy;
}

void Bounding::ObjectCookie::ReleaseResource(void)
{
	delete[] vertexBuffer;
	delete[] indexBuffer;

	delete mImagesResource;
	delete[] mObjects;

	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
}

void Bounding::ObjectCookie::ReCreateResource(Resource::ResourceBase * resourceLoad)
{
	Init(mResourceName, resourceLoad);
}

void Bounding::ObjectCookie::Init(std::string mResourceName, Resource::ResourceBase * mResourceLoad)
{
	Resource::ResourceLoad *mModel = new Resource::ResourceLoad(mResourceName, mResourceLoad);

	mImagesResource = mModel->GetImagesResource();
	mIndexBuffer = mModel->GetIndexBuffer(mIndexFormat);
	mVertexBuffer = mModel->GetVertexBuffer();
	mObjects = mModel->GetModelObjects(mDrawObjectCount);

	indexBuffer = reinterpret_cast<GLushort *>(mModel->GetIndexBufferData(mIndexCount));
	mIndexCount /= sizeof(GLushort);

	vertexBuffer = reinterpret_cast<Mesh::VTMesh *>(mModel->GetVertexBufferData(mVertexCount));
	mVertexCount /= sizeof(Mesh::VTMesh);

	mIndexCollisionCount = mIndexCount;
	mVertexCollisionCount = mVertexCount;

	delete mModel;
}

void Bounding::ObjectCookie::InitCollisionModel(std::string mResourceName, Resource::ResourceBase * mResourceLoad)
{
	/*Resource::ResourceLoad *mModel = new Resource::ResourceLoad(mResourceName, mResourceLoad);

	indexBuffer = reinterpret_cast<GLushort *>(mModel->GetIndexBufferData(mIndexCollisionCount));
	mIndexCollisionCount /= sizeof(GLushort);

	vertexBuffer = reinterpret_cast<Mesh::VTMesh *>(mModel->GetVertexBufferData(mVertexCollisionCount));
	mVertexCollisionCount /= sizeof(Mesh::VTMesh);

	delete mModel;*/
}

Mesh::VTMesh * Bounding::ObjectCookie::GetVertexBuffer()
{
	return vertexBuffer;
}

GLushort * Bounding::ObjectCookie::GetIndexBuffer()
{
	return indexBuffer;
}

uint32_t Bounding::ObjectCookie::GetVertexCollisionCount(void)
{
	return mVertexCollisionCount;
}

uint32_t Bounding::ObjectCookie::GetIndexCollisionCount(void)
{
	return mIndexCollisionCount;
}
