#include "BoundingObjectStructAABB.h"
#include "BoundingObjectStructSphere.h"
#include "Object.h"
#include "ObjectCookie.h"
#include "Cookie.h"
#include "Barrier.h"


#pragma once
namespace Bounding
{
#define mSQ(x) (x)*(x)

	bool SphereSphereIntersect(glm::vec4 msp1, glm::vec4 msp2);
	bool TriangleRayIntersection(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 vOrigin, glm::vec3 vDir, float &outDist);
	bool TriangleTriangleIntersection(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	bool TriangleTriangleIntersectionCheap(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	bool ModelModelIntersection(const Collision::LowPolyModelInstance *m0, const Collision::LowPolyModelInstance *m1);

	bool AABBSphereIntersection(glm::vec3 AABB_Pos, glm::vec3 AABB_Extent, glm::vec4 SpherePosRadius);
	//bool AABBSphereIntersection(const BoundingObjectStructAABB *mObjectA, const BoundingObjectStructSphere *mObjectB);
	bool AABBSphereIntersection(const Draw::BarrierCollisionStruct &mObjectA, const Draw::CookieCollisionStruct &mObjectB);
	bool SphereSphereIntersect(const Collision::BoundingSphereInstance *mObjectA, const Collision::BoundingSphereInstance *mObjectB);
	//Draw::BarrierCollisionStruct
	//Draw::CookieCollisionStruct
}
