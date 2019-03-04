#include "LoadBase.h"


Load::LoadBase::LoadBase(Resource::ResourceBase * resourceLoad, std::string mName) : resourceLoad(resourceLoad)
{
}

Load::LoadBase::~LoadBase()
{
}

Collision::ModelBase * Load::LoadBase::GetModel(void)
{
	return mDrawModelLoad->GetDrawModel();
}
