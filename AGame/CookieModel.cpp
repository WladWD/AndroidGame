#include "CookieModel.h"


Collision::CookieModel::CookieModel(Resource::ModelObject * mObjects, GLuint mDrawObjectCount, GLuint mElementArray, GLuint mVertexBuffer, GLenum mIndexFormat, Resource::ImageResource *mImages) :
	ModelBase(mObjects, mDrawObjectCount, mElementArray, mVertexBuffer, mIndexFormat, mImages)
{
}

Collision::CookieModel::~CookieModel()
{
}
