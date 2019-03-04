#include "BoundingSphereInstance.h"



Collision::BoundingSphereInstance::BoundingSphereInstance(BoundingSphere * mBoundingSphere, glm::mat4 mWorld) : mBoundingSphere(mBoundingSphere), mWorld(mWorld)
{
}

Collision::BoundingSphereInstance::~BoundingSphereInstance()
{
}

void Collision::BoundingSphereInstance::SetWorld(glm::mat4 mWorld)
{
	this->mWorld = mWorld;
}

glm::mat4 Collision::BoundingSphereInstance::GetWorldMatrix(void) const
{
	return mWorld;
}

glm::vec4 Collision::BoundingSphereInstance::GetCenterRadius(void) const
{
	/*glm::vec4 mCenterRadius = mBoundingSphere->GetCenterRadius();
	glm::vec3 mWorldCenter = glm::vec3( mWorld * glm::vec4(glm::vec3(mCenterRadius), 1.0f) );
	float mRadius = (mWorld * glm::vec4(0.0f, 0.0f, mCenterRadius.w, 1.0f)).z;

	return glm::vec4(mWorldCenter, mRadius);*/
	return mBoundingSphere->GetCenterRadius();
}
