#include "MHeder.h"
#include "Mesh.h"

#pragma once
namespace ShapeGenerator
{
	class MShapeGenerator
	{
	public:
		MShapeGenerator(void);
		~MShapeGenerator();

		static void GenCylinder(int32_t uVSliceCount, int32_t uHSliceCount, float fYOffset, float fRadius, float fHeight, GLuint &vbBuffer, GLuint &ibBuffer, uint32_t &uCount);
	};
}

