#include "BarrierBase.h"


Barrier::BarrierBase::BarrierBase(Draw::Barrier *mBarrier, Camera::MCamera *cCamera, float fHeight) : fHeight(fHeight), fAngle(0.0f), cCamera(cCamera),
	PI(3.1415926f)
{
	//mWorld_OOBB = glm::mat4(1.0f);
	//Init();
	mDeltaConst = std::rand() & 1 ? 1.0f : -1.0f;
	fAngle = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * PI * 4.0f;

	mWorld = glm::mat4(1.0f);
	/*Collision::ModelBase *mModelDraw;
		Collision::LowPolyModel *mLowpolyModel;
		Collision::BoundingAABB *mBounding;*/
	/*Collision::ModelBase *mModelDraw;
		Collision::LowPolyModelInstance *mLowpolyModel;
		Collision::BoundingAABBInstance *mBounding;*/
	mModelDraw = mBarrier->GetDrawModel();
	mBounding = new Collision::BoundingAABBInstance(mBarrier->GetBoundingAABB(), mWorld);
	mLowpolyModel = new Collision::LowPolyModelInstance(mBarrier->GetLowPolyModel(), mWorld);
}

Barrier::BarrierBase::~BarrierBase()
{
	//delete mAABB;
	//DeleteResources();

	delete mBounding;
	delete mLowpolyModel;

	/*delete mImagesResource;
	delete mObjects;

	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);*/
}

float Barrier::BarrierBase::GetCurrentHeight(void)
{
	return fHeight;
}

bool Barrier::BarrierBase::Intersect(const Draw::CookieCollisionStruct &mCookieCollision)
{
	//MessageBox(nullptr, L"Add Code", L" ", MB_OK);
	Draw::BarrierCollisionStruct mBarrierStruct;
	mBarrierStruct.mBounding = mBounding;
	mBarrierStruct.mLowpolyModel = mLowpolyModel;

	return Bounding::AABBSphereIntersection(mBarrierStruct, mCookieCollision);
	//return false;
}

/*void Barrier::BarrierBase::DeleteResources(void)
{
	delete mAABB;
}

void Barrier::BarrierBase::InitializeResources(Bounding::Object *mObjects)
{
	this->mBounding = mObjects;
	Init();
}*/

//void Barrier::BarrierBase::Init(void)
//{
//	/*Resource::ResourceLoad *mModel = new Resource::ResourceLoad(mResourceName, mResourceLoad);
//
//	mImagesResource = mModel->GetImagesResource();
//	mIndexBuffer = mModel->GetIndexBuffer(mIndexFormat);
//	mVertexBuffer = mModel->GetVertexBuffer();
//	mObjects = mModel->GetModelObjects(mDrawObjectCount);
//
//	delete mModel;*/
//
//	mImagesResource = mBounding->GetImageResource();
//	mObjects = mBounding->GetModelObject();
//	mBounding->GetDrawData(mIndexFormat, mVertexBuffer, mIndexBuffer, mDrawObjectCount);
//
//	mAABB = new Bounding::BoundingObjectStructAABB(mBounding, mBounding->GetVertexBuffer(), mBounding->GetVertexCount());
//}

