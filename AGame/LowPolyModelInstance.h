#include "LowPolyModelInstanceBase.h"
#include "LowPolyModel.h"

#pragma once
namespace Collision
{
	class LowPolyModelInstance : public LowPolyModelInstanceBase
	{
	public:
		LowPolyModelInstance(LowPolyModel *mLowpolyModel, glm::mat4 mWorld);
		~LowPolyModelInstance();
		////////////////////////////////////////////////////////////////////////////////////////////////
		bool GetNextTriangleOrigin(glm::vec3 &mV0, glm::vec3 &mV1, glm::vec3 &mV2) const;
		bool GetNextTriangleWithMatrix(glm::vec3 &mV0, glm::vec3 &mV1, glm::vec3 &mV2, glm::mat4 mWorld) const;
		////////////////////////////////////////////////////////////////////////////////////////////////
	};
}

