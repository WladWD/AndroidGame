#include "ResourceLoad.h"
#include "ShaderBarrierBase.h"
#include "Mesh.h"
#include "LoadStructure.h"
#include "MCamera.h"

#pragma once
namespace Bounding
{
	class BoundingObjectStructBase
	{
	protected:
		////////////////////////////////////////////////////////////////////////////////////////////
		void *mMesh;
		////////////////////////////////////////////////////////////////////////////////////////////
		virtual void BuildBoundingStruct(Mesh::VTMesh *mMesh, uint32_t mVertexCount) = 0;
		////////////////////////////////////////////////////////////////////////////////////////////
	public:
		BoundingObjectStructBase(void *mMesh);
		virtual ~BoundingObjectStructBase(void);
		////////////////////////////////////////////////////////////////////////////////////////////
		/*  
		virtual void Rotate(glm::mat4 mMatrix) = 0;
		virtual void Move(glm::vec3 mVector) = 0;
		virtual void Scale(glm::vec3 mVector) = 0;
		////////////////////////////////////////////////////////////////////////////////////////////
		virtual void RotateOrigin(glm::mat4 mMatrix) = 0;
		virtual void MoveOrigin(glm::vec3 mVector) = 0;
		virtual void ScaleOrigin(glm::vec3 mVector) = 0;*/
		////////////////////////////////////////////////////////////////////////////////////////////
		void *GetMeshObject(void) const;
		////////////////////////////////////////////////////////////////////////////////////////////
	};
}

