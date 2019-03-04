#include "BoundingAABBInstance.h"


Collision::BoundingAABBInstance::BoundingAABBInstance(BoundingAABB * mBoundingAABB, glm::mat4 mWorld) : mBoundingAABB(mBoundingAABB), mWorld(mWorld)
{
}

Collision::BoundingAABBInstance::~BoundingAABBInstance()
{
}

glm::vec3 Collision::BoundingAABBInstance::GetCenter(void) const
{
	return mBoundingAABB->GetCenter();
}

glm::vec3 Collision::BoundingAABBInstance::GetExtent(void) const
{
	return mBoundingAABB->GetExtent();
}

void Collision::BoundingAABBInstance::SetWorldMatrix(glm::mat4 mWorld)
{
	this->mWorld = mWorld;
}

glm::mat4 Collision::BoundingAABBInstance::GetWorldMatrix(void) const
{
	return mWorld;
}
