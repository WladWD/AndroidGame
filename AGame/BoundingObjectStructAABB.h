#include "BoundingObjectStructBase.h"

#pragma once
namespace Bounding
{
	class BoundingObjectStructAABB : public BoundingObjectStructBase
	{
		glm::vec3 mCenter;
		glm::vec3 mExtent;
		////////////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 mTransformMatrix;//local to world space
		////////////////////////////////////////////////////////////////////////////////////////////
		void BuildBoundingStruct(Mesh::VTMesh *mMesh, uint32_t mVertexCount);
		////////////////////////////////////////////////////////////////////////////////////////////
	public:
		BoundingObjectStructAABB(void *mMeshClass, Mesh::VTMesh *mMesh, uint32_t mVertexCount);
		~BoundingObjectStructAABB();
		////////////////////////////////////////////////////////////////////////////////////////////
		void Transform(glm::mat4 mTransformMatrix);
		////////////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 GetTransformMatrix(void) const;
		////////////////////////////////////////////////////////////////////////////////////////////
		glm::vec3 GetCenter(void) const;
		glm::vec3 GetExtent(void) const;
		////////////////////////////////////////////////////////////////////////////////////////////
	};
}

