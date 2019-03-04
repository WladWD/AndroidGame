#include "Collision.h"

//bool AABBSphereIntersection(const Draw::BarrierCollisionStruct &mObjectA, const Draw::CookieCollisionStruct &mObjectB);
bool Bounding::AABBSphereIntersection(const Draw::BarrierCollisionStruct &mObjectA, const Draw::CookieCollisionStruct &mObjectB)
{
	//glm::vec3 mCenter;
	//float Radius;

	glm::mat4 mTransformMatrix = glm::inverse(mObjectA.mBounding->GetWorldMatrix()) * mObjectB.mBoundingCookie->GetWorldMatrix();
	glm::vec4 mCenterRadius = mObjectB.mBoundingCookie->GetCenterRadius();
	glm::vec3 mWorldCenter = glm::vec3(mTransformMatrix * glm::vec4(glm::vec3(mCenterRadius), 1.0f));
	float mRadius = glm::length(mTransformMatrix * glm::vec4(mCenterRadius.w, 0.0f, 0.0f, 0.0f));

	/*glm::vec4 mD = mObjectB.GetPositionRadius();
	glm::vec4 mPR = mObjectB->GetTransformMatrix() * glm::vec4(mD.x, mD.y, mD.z, 1.0f);
	Radius = glm::length(glm::vec3(mObjectB->GetTransformMatrix() * glm::vec4(mD.x + mD.w, mD.y, mD.z, 1.0f)) - glm::vec3(mPR));
	mPR.w = Radius;

	mCenter = glm::vec3(glm::inverse(mObjectA->GetTransformMatrix()) * glm::vec4(mPR.x, mPR.y, mPR.z, 1.0f));
	Radius = glm::length(glm::vec3((glm::inverse(mObjectA->GetTransformMatrix()) * glm::vec4(mPR.x + mPR.w, mPR.y, mPR.z, 1.0f))) - mCenter);*/

	//return AABBSphereIntersection(mObjectA.mBounding->GetCenter(), mObjectA.mBounding->GetExtent(), glm::vec4(mWorldCenter, mRadius));

	//DEBUG MODE
	//return false;

	if (AABBSphereIntersection(mObjectA.mBounding->GetCenter(), mObjectA.mBounding->GetExtent(), glm::vec4(mWorldCenter, mRadius)))
		return ModelModelIntersection(mObjectA.mLowpolyModel, mObjectB.mLowpolyModel);
	return false;
}

bool Bounding::SphereSphereIntersect(const Collision::BoundingSphereInstance * mObjectA, const Collision::BoundingSphereInstance * mObjectB)
{
	glm::mat4 mTransformMatrix = glm::inverse(mObjectA->GetWorldMatrix()) * mObjectB->GetWorldMatrix();
	glm::vec4 mCenterRadius = mObjectB->GetCenterRadius();
	glm::vec3 mWorldCenter = glm::vec3(mTransformMatrix * glm::vec4(glm::vec3(mCenterRadius), 1.0f));
	float mRadius = glm::length(mTransformMatrix * glm::vec4(mCenterRadius.w, 0.0f, 0.0f, 0.0f));
	return SphereSphereIntersect(mObjectA->GetCenterRadius(), glm::vec4(mWorldCenter, mRadius));
}

bool Bounding::SphereSphereIntersect(glm::vec4 msp1, glm::vec4 msp2)
{
	return (mSQ(msp1.x - msp2.x) + mSQ(msp1.y - msp2.y) + mSQ(msp1.z - msp2.z)) <= mSQ(msp1.w + msp2.w);
}

bool Bounding::TriangleRayIntersection(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 vOrigin, glm::vec3 vDir, float &outDist)
{
	static const float mDelta = 0.00001f;
	outDist = 0.0f;
	float t, u, v;

	glm::vec3 p1 = vOrigin - v1;
	glm::vec3 a = v2 - v1;
	glm::vec3 b = v3 - v1;

	float md = glm::dot(glm::cross(a, b), vDir);
	if (glm::abs(md) < mDelta)
		return false;//в одной или парралельных плоскостях
	else 
	{
		t = glm::dot(glm::cross(p1, b), vDir) / md;

		if (t > 1.0f || t < 0.0f)
			return false;

		u = glm::dot(glm::cross(a, p1), vDir) / md;

		if (u > 1.0f || u < 0.0f)
			return false;

		v = glm::dot(glm::cross(a, b), p1) / md;

		if (v > 1.0f || v < 0.0f || v + u > 1.0f)
			return false;

		outDist = t;
		return true;
	}

	return false;
}

bool Bounding::TriangleTriangleIntersection(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	if (!TriangleTriangleIntersectionCheap(v1, v2, v3, p1, p2, p3))
		return false;

	//return TriangleTriangleIntersectionCheap(v1, v2, v3, p1, p2, p3);

	glm::vec3 mC[][2] = { {v1, v2 - v1}, {v1, v3 - v1}, {v2, v3 - v2} };
	glm::vec3 mC1[][2] = { { p1, p2 - p1 },{ p1, p3 - p1 },{ p2, p3 - p2 } };

	float mDist;
	for (register int32_t i = 0; i < 3; ++i)
		if (TriangleRayIntersection(p1, p2, p3, mC[i][0], mC[i][1], mDist) || TriangleRayIntersection(v1, v2, v3, mC1[i][0], mC1[i][1], mDist))
			return true;
	return false;
}

bool Bounding::TriangleTriangleIntersectionCheap(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	glm::vec4 mSp1, mSp2;

	glm::vec3 mCenter = (v1 + v2 + v3) * 0.333f;
	mSp1 = glm::vec4(mCenter, glm::length(mCenter - v1));

	mCenter = (p1 + p2 + p3) * 0.333f;
	mSp2 = glm::vec4(mCenter, glm::length(mCenter - p1));

	return SphereSphereIntersect(mSp1, mSp2);
}

bool Bounding::ModelModelIntersection(const Collision::LowPolyModelInstance * m0, const Collision::LowPolyModelInstance * m1)
{
	//////////////////////////////////////////////////////////////////////////////////////////
	const int32_t mCount = 10;
	///////////////////////////////
	static int32_t check = -1;
	///////////////////////////////
	//++check;

	if (++check == (mCount-1))
		return false;
	///////////////////////////////
	check %= mCount;
	//////////////////////////////////////////////////////////////////////////////////////////

	glm::vec3 v0, v1, v2;

	glm::mat4 mWorld = glm::inverse(m1->GetWorldMatrix()) * m0->GetWorldMatrix();
	while (m0->GetNextTriangleWithMatrix(v0, v1, v2, mWorld))
	{
		glm::vec3 mv0, mv1, mv2;
		while (m1->GetNextTriangleOrigin(mv0, mv1, mv2)) //GetNextTriangle
		{
			if (TriangleTriangleIntersection(v0, v1, v2, mv0, mv1, mv2))
			{
				return true;
			}
		}
	}
	return false;
}

bool Bounding::AABBSphereIntersection(glm::vec3 AABB_Pos, glm::vec3 AABB_Extent, glm::vec4 SpherePosRadius)
{
	glm::vec3 mMax, mMin;
	mMax = AABB_Pos + AABB_Extent;
	mMin = AABB_Pos - AABB_Extent;

	float d2 = 0.0f;
	for (register int i = 0; i < 3; i++) 
	{
		if (SpherePosRadius[i] < mMin[i])
			d2 += mSQ(SpherePosRadius[i] - mMin[i]);

		if (SpherePosRadius[i] > mMax[i])
			d2 += mSQ(SpherePosRadius[i] - mMax[i]);
	}

	return d2 <= mSQ(SpherePosRadius.w);
}