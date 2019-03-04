#include "DrawObject.h"


Draw::DrawObject::DrawObject(void)
{
}

Draw::DrawObject::~DrawObject()
{
}

Collision::ModelBase * Draw::DrawObject::GetDrawModel(void)
{
	return mModelDraw;
}
