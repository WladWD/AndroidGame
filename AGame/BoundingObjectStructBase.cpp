#include "BoundingObjectStructBase.h"



Bounding::BoundingObjectStructBase::BoundingObjectStructBase(void *mMesh) : mMesh(mMesh)
{
}

Bounding::BoundingObjectStructBase::~BoundingObjectStructBase(void)
{
}

void *Bounding::BoundingObjectStructBase::GetMeshObject(void) const
{
	return mMesh;
}