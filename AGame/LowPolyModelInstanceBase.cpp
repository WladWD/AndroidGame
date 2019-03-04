#include "LowPolyModelInstanceBase.h"


Collision::LowPolyModelInstanceBase::LowPolyModelInstanceBase(LowPolyModelBase * mLowpolyModel, glm::mat4 mWorld) : mLowpolyModel(mLowpolyModel), mWorld(mWorld)
{
}

Collision::LowPolyModelInstanceBase::~LowPolyModelInstanceBase()
{
	//delete mLowpolyModel;
}

void Collision::LowPolyModelInstanceBase::SetWorld(glm::mat4 mWorld)
{
	this->mWorld = mWorld;
}

bool Collision::LowPolyModelInstanceBase::GetNextTriangle(glm::vec3 & mV0, glm::vec3 & mV1, glm::vec3 & mV2) const
{
	bool mRes = mLowpolyModel->GetNextTriangle(mV0, mV1, mV2);
	mV0 = glm::vec3(mWorld * glm::vec4(mV0, 1.0f));
	mV1 = glm::vec3(mWorld * glm::vec4(mV1, 1.0f));
	mV2 = glm::vec3(mWorld * glm::vec4(mV2, 1.0f));
	return mRes;
}

glm::mat4 Collision::LowPolyModelInstanceBase::GetWorldMatrix(void) const
{
	return mWorld;
}
