#include "BoundingObjectStructSphere.h"


Bounding::BoundingObjectStructSphere::BoundingObjectStructSphere(void * mMeshClass, Mesh::VTMesh * mMesh, uint32_t mVertexCount) : BoundingObjectStructBase(mMeshClass)
{
	BuildBoundingStruct(mMesh, mVertexCount);
	mTransformMatrix = glm::mat4(1.0f);
}

Bounding::BoundingObjectStructSphere::BoundingObjectStructSphere(void *mMeshClass, glm::vec4 mCenterRadius) : BoundingObjectStructBase(mMeshClass), mCenterRadius(mCenterRadius)
{

}

Bounding::BoundingObjectStructSphere::~BoundingObjectStructSphere()
{
}

void Bounding::BoundingObjectStructSphere::BuildBoundingStruct(Mesh::VTMesh * mMesh, uint32_t mVertexCount)
{
	const float mRadiusScale = 1.0001f;
	float Radius = 0.0f;
	glm::vec3 sumVec;
	glm::vec3 mSphereCenter;
	glm::vec3 minVec, maxVec;
	minVec = maxVec = mMesh[0].gWorldPos;


	for (register uint32_t i = 1; i < mVertexCount; i++)
	{
		sumVec += mMesh[i].gWorldPos;
		minVec = glm::min(minVec, mMesh[i].gWorldPos);
		maxVec = glm::max(maxVec, mMesh[i].gWorldPos);
	}

	sumVec *= (1.0f / static_cast<float>(mVertexCount));
	mSphereCenter = (maxVec + minVec) * 0.5f;

	for (register uint32_t i = 0; i < mVertexCount; i++)
		Radius = glm::max(glm::length(mSphereCenter - mMesh[i].gWorldPos), Radius);

	mCenterRadius = glm::vec4(mSphereCenter, Radius * mRadiusScale);
}

void Bounding::BoundingObjectStructSphere::Transform(glm::mat4 mTransformMatrix)
{
	this->mTransformMatrix = mTransformMatrix;
}

glm::mat4 Bounding::BoundingObjectStructSphere::GetTransformMatrix(void) const
{
	return mTransformMatrix;
}

glm::vec4 Bounding::BoundingObjectStructSphere::GetPositionRadius(void) const
{
	return mCenterRadius;
}
