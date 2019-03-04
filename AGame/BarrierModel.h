#include "ModelBase.h"

#pragma once
namespace Collision
{
	class BarrierModel : public ModelBase
	{
		//////////////////////////////////////////////////////////////////////////////////////
	public:
		BarrierModel(Resource::ModelObject *mObjects, GLuint mDrawObjectCount, GLuint mElementArray, GLuint mVertexBuffer, GLenum mIndexFormat, Resource::ImageResource *mImages);
		~BarrierModel();
		//////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////
	};
}

