#include "BoundingObjectStructAABB.h"


Bounding::BoundingObjectStructAABB::BoundingObjectStructAABB(void * mMeshClass, Mesh::VTMesh *mMesh, uint32_t mVertexCount) : BoundingObjectStructBase(mMeshClass)
{
	BuildBoundingStruct(mMesh, mVertexCount);
	mTransformMatrix = glm::mat4(1.0f);
}

Bounding::BoundingObjectStructAABB::~BoundingObjectStructAABB()
{
}

void Bounding::BoundingObjectStructAABB::BuildBoundingStruct(Mesh::VTMesh * mMesh, uint32_t mVertexCount)
{
	//float min_x, min_y, min_z;
	//float s_x = 0.0f, s_y = 0.0f, s_z = 0.0f;
	//float max_x, max_y, max_z;
	glm::vec3 minVec, maxVec;


	minVec = maxVec = mMesh[0].gWorldPos;

	/*min_x = max_x = mPos.x;
	min_y = max_y = mPos.y;
	min_z = max_z = mPos.z;*/

	for (register uint32_t i = 1; i < mVertexCount; i++)
	{
		//mPos = mMesh[i].gWorldPos;

		minVec = glm::min(minVec, mMesh[i].gWorldPos);
		maxVec = glm::max(maxVec, mMesh[i].gWorldPos);

		/*s_x += mPos.x;
		s_y += mPos.y;
		s_z += mPos.z;

		min_x = glm::min(min_x, mPos.x);
		min_y = glm::min(min_y, mPos.y);
		min_z = glm::min(min_z, mPos.z);

		max_x = glm::max(max_x, mPos.x);
		max_y = glm::max(max_y, mPos.y);
		max_z = glm::max(max_z, mPos.z);*/
	}

	mCenter = (maxVec + minVec) * 0.5f;
	mExtent = (maxVec - minVec) * 0.5f;
}

void Bounding::BoundingObjectStructAABB::Transform(glm::mat4 mTransformMatrix)
{
	this->mTransformMatrix = mTransformMatrix;
}

glm::mat4 Bounding::BoundingObjectStructAABB::GetTransformMatrix(void) const
{
	return mTransformMatrix;
}

glm::vec3 Bounding::BoundingObjectStructAABB::GetCenter(void) const
{
	return mCenter;
}

glm::vec3 Bounding::BoundingObjectStructAABB::GetExtent(void) const
{
	return mExtent;
}
