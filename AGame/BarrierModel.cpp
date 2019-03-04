#include "BarrierModel.h"


Collision::BarrierModel::BarrierModel(Resource::ModelObject * mObjects, GLuint mDrawObjectCount, GLuint mElementArray, GLuint mVertexBuffer, GLenum mIndexFormat, Resource::ImageResource *mImages) :
	ModelBase(mObjects, mDrawObjectCount, mElementArray, mVertexBuffer, mIndexFormat, mImages)
{
}

Collision::BarrierModel::~BarrierModel()
{
}
