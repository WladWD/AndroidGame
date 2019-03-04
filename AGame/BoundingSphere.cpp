#include "BoundingSphere.h"


Collision::BoundingSphere::BoundingSphere(glm::vec4 mCenterRadius) : mCenterRadius(mCenterRadius)
{
}

Collision::BoundingSphere::~BoundingSphere()
{
}

glm::vec4 Collision::BoundingSphere::GetCenterRadius(void)
{
	return mCenterRadius;
}
