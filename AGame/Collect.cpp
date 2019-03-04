#include "Collect.h"


Draw::Collect::Collect(Resource::ResourceBase *resourceLoad, std::string mName)
{
	//////////////////////////////////////////////////////////////////////////////////////////
	Load::LoadCollect *mLoadCollect = new Load::LoadCollect(resourceLoad, mName);
	//////////////////////////////////////////////////////////////////////////////////////////
	mBoundingCookie = mLoadCollect->GetSphereBounding();
	mModelDraw = mLoadCollect->GetModel();
	//////////////////////////////////////////////////////////////////////////////////////////
	delete mLoadCollect;
	//////////////////////////////////////////////////////////////////////////////////////////
}

Draw::Collect::~Collect()
{
	delete mModelDraw;
	delete mBoundingCookie;
}

Collision::BoundingSphere * Draw::Collect::GetBoundingSphere(void)
{
	return mBoundingCookie;
}
