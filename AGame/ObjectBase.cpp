#include "ObjectBase.h"


Bounding::ObjectBase::ObjectBase(void)
{
}

Bounding::ObjectBase::~ObjectBase()
{
	delete mImagesResource;
	delete[] mObjects;

	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
}

void Bounding::ObjectBase::GetDrawData(GLenum & mIndexFormat, GLuint & mVertexBuffer, GLuint & mIndexBuffer, GLuint & mDrawObjectCount)
{
	mIndexFormat = this->mIndexFormat;
	mVertexBuffer = this->mVertexBuffer;
	mIndexBuffer = this->mIndexBuffer;
	mDrawObjectCount = this->mDrawObjectCount;
}

/*void Bounding::BoundingObjectBase::SetWorldMatrix(glm::mat4 mWorld)
{
	this->mWorld = mWorld;
}*/

Resource::ModelObject * Bounding::ObjectBase::GetModelObject(void)
{
	return mObjects;
}

Resource::ImageResource * Bounding::ObjectBase::GetImageResource(void)
{
	return mImagesResource;
}

uint32_t Bounding::ObjectBase::GetVertexCount(void)
{
	return mVertexCount;
}

uint32_t Bounding::ObjectBase::GetIndexCount(void)
{
	return mIndexCount;
}

/*bool Bounding::ObjectBase::Intersect(ObjectBase * mObject, const glm::mat4* mWorld1, const glm::mat4 *mWorld2)
{
	Mesh::OOBB mObject1;
	Mesh::OOBB mObject2;

	mObject1.mCenter = this->mOOBB.mCenter;//(*mWorld1) * this->mOOBB.mCenter;// this->mOOBB.mCenter;// (*mWorld1) * this->mOOBB.mCenter;
	mObject1.mDim = this->mOOBB.mDim;//glm::transpose(glm::inverse(*mWorld1)) * this->mOOBB.mDim; //this->mOOBB.mDim;// glm::transpose(glm::inverse(*mWorld1)) * this->mOOBB.mDim;

	mObject2.mCenter = mObject->mOOBB.mCenter;//(*mWorld2) * mObject->mOOBB.mCenter;// mObject->mOOBB.mCenter;// (*mWorld2) * mObject->mOOBB.mCenter;
	mObject2.mDim = mObject->mOOBB.mDim;//glm::transpose(glm::inverse(*mWorld2)) * mObject->mOOBB.mDim;// mObject->mOOBB.mDim;// glm::transpose(glm::inverse(*mWorld2)) * mObject->mOOBB.mDim;

	return OOBBIntersect(&mObject1, &mObject2, mWorld1, mWorld2);
}
*/