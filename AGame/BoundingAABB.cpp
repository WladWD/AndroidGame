#include "BoundingAABB.h"


Collision::BoundingAABB::BoundingAABB(glm::vec3 mCenter, glm::vec3 mExtent) : mCenter(mCenter), mExtent(mExtent)
{
}

Collision::BoundingAABB::~BoundingAABB()
{
}

glm::vec3 Collision::BoundingAABB::GetCenter(void) const
{
	return mCenter;
}

glm::vec3 Collision::BoundingAABB::GetExtent(void) const
{
	return mExtent;
}
