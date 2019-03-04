#include "CookieDrawControl.h"


DrawCookie::CookieDrawControl::CookieDrawControl(Resource::ResourceBase * mResourceLoad, Camera::MCamera * cCamera, DrawCookie::CookieDestroy **mCookieDestroy,
	float fZOffset, float fYOffset, float fScale) : cCamera(cCamera), mCookieDraw(0), mCookie(0)
{
	SetCookieIndexDraw(0, mResourceLoad, mCookieDestroy, fZOffset, fYOffset, fScale);
}

DrawCookie::CookieDrawControl::~CookieDrawControl()
{
	delete mCookieDraw;
	delete mCookie;
}

void DrawCookie::CookieDrawControl::SetCookieIndexDraw(uint32_t mIndex, Resource::ResourceBase * mResourceLoad, DrawCookie::CookieDestroy **mCookieDestroy,
	float fZOffset, float fYOffset, float fScale)
{
	if (mCookieDraw) delete mCookieDraw;
	if (mCookie) delete mCookie;

	switch (mIndex) 
	{
		case 0: 
		{
			//mObject = new Bounding::ObjectCookie(mResourceLoad, mCookieDestroy, "resource\\models\\cookie\\cookie.tdof", "resource\\models\\cookie\\cookie.tdofp");
			//mCookieDraw = new DrawCookieStandart(mObject, mResourceLoad, cCamera, fZOffset, fYOffset, fScale);

			/*Load::LoadCookie *mLoadCookie = new Load::LoadCookie(mResourceLoad, "resource\\models\\cookie\\cookie.tdof");
			mLowpolyModel = mLoadCookie->GetLowPolyModel();
			this->mCookieDestroy = mLoadCookie->GetCookieDestroy();
			mBoundingCookie = mLoadCookie->GetSphereBounding();
			mModelDraw = mLoadCookie->GetModel();
			*/

			mCookie = new Draw::Cookie(mResourceLoad, "resource\\models\\cookie\\cookie_v1.tdof");
			mCookieDraw = new DrawCookieStandart(mCookie, mResourceLoad, cCamera, fZOffset, fYOffset, fScale);
			*mCookieDestroy = mCookie->GetCookieDestroy();

			//delete mLoadCookie;
		}break;

	}
}

void DrawCookie::CookieDrawControl::Update(float fDeltaTime, float fGlobalTime)
{
	mCookieDraw->Update(fDeltaTime, fGlobalTime);
}

/*const Bounding::ObjectCookie *DrawCookie::CookieDrawControl::GetObjectData(void)
{
	return mObject;
}
*/
/*const Bounding::BoundingObjectStructSphere *DrawCookie::CookieDrawControl::GetBoundingObject(void)
{
	return mCookieDraw->GetBoundingSphere();
}*/

Draw::CookieCollisionStruct DrawCookie::CookieDrawControl::GetCookieCollision(void)
{
	Draw::CookieCollisionStruct mCookieCollision;
	mCookieCollision.mBoundingCookie = mCookieDraw->GetBoundingSphere();
	mCookieCollision.mLowpolyModel = mCookieDraw->GetLowPolyModel();

	return mCookieCollision;
}

void DrawCookie::CookieDrawControl::Draw(void)
{
	mCookieDraw->Draw();
}

void DrawCookie::CookieDrawControl::DrawDestroyCookie(void)
{
	mCookieDraw->DrawDestroyedCookie();
}
