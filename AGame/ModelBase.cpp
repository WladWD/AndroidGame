#include "ModelBase.h"


Collision::ModelBase::ModelBase(Resource::ModelObject * mObjects, GLuint mDrawObjectCount, GLuint mElementArray, GLuint mVertexBuffer, GLenum mIndexFormat, Resource::ImageResource *mImages) :
	mObjects(mObjects), mDrawObjectCount(mDrawObjectCount), mElementArray(mElementArray), mVertexBuffer(mVertexBuffer), mIndexFormat(mIndexFormat), mImages(mImages)
{
}

Collision::ModelBase::~ModelBase()
{
	delete[] mObjects;
	delete mImages;
}

void Collision::ModelBase::BindBuffers(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementArray);
}

void Collision::ModelBase::UnBindBuffers(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint Collision::ModelBase::GetDrawObjectCount(void)
{
	return mDrawObjectCount;
}

void Collision::ModelBase::Draw(uint32_t mDrawIndex)
{
	Resource::GLTextureResource glTexRes = mImages->GetTextureByID(mObjects[mDrawIndex].GetTextureID(0));
	glBindTexture(glTexRes.texture_target, glTexRes.texture);

	glDrawElements(GL_TRIANGLES, mObjects[mDrawIndex].GetIndexCount(), mIndexFormat, reinterpret_cast<const void *>(mObjects[mDrawIndex].GetIndexOffset()));
	//GL_TRIANGLES GL_LINES GL_UNSIGNED_SHORT 0x1403
}
