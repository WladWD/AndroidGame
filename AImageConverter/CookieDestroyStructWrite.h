#include "MeshObject.h"

#pragma once
namespace Resource
{
#define COOKIE_PICES_COUNT 64
	struct CookieDestroy
	{
		glm::vec4 mCenter;
		glm::vec4 mPicesCenter[COOKIE_PICES_COUNT];
		/*
		glm::vec4 mMoveDirections[COOKIE_PICES_COUNT];
		/*float mVisibility;
		float mGlobalTime;

		CookieDestroy(void) : mVisibility(1.0f), mGlobalTime(0.0f)
		{ }*/
	};

	struct SphereBounding
	{
		glm::vec4 mCenterRadius;
	};

	struct AABBStruct 
	{
		glm::vec3 mCenter;
		glm::vec3 mExtent;
	};
}
