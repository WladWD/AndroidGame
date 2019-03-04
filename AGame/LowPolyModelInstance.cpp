#include "LowPolyModelInstance.h"


Collision::LowPolyModelInstance::LowPolyModelInstance(LowPolyModel * mLowpolyModel, glm::mat4 mWorld) : LowPolyModelInstanceBase(mLowpolyModel, mWorld)
{
}

Collision::LowPolyModelInstance::~LowPolyModelInstance()
{
}

bool Collision::LowPolyModelInstance::GetNextTriangleOrigin(glm::vec3 & mV0, glm::vec3 & mV1, glm::vec3 & mV2) const
{
	return mLowpolyModel->GetNextTriangle(mV0, mV1, mV2);
}

bool Collision::LowPolyModelInstance::GetNextTriangleWithMatrix(glm::vec3 & mV0, glm::vec3 & mV1, glm::vec3 & mV2, glm::mat4 mWorld) const
{
	bool mRes = mLowpolyModel->GetNextTriangle(mV0, mV1, mV2);
	mV0 = glm::vec3(mWorld * glm::vec4(mV0, 1.0f));
	mV1 = glm::vec3(mWorld * glm::vec4(mV1, 1.0f));
	mV2 = glm::vec3(mWorld * glm::vec4(mV2, 1.0f));
	return mRes;
}
