#include "DrawEndGameBlur.h"


DrawFullScreen::DrawEndGameBlur::DrawEndGameBlur(Resource::ResourceBase *resourceLoad, uint32_t mDimX, uint32_t mDimY, float mDelayTime, float mDuriationTime) :
	mLocalTime(-mDelayTime * 1000.0f), mDelayTime(mDelayTime * 1000.0f), mDuriationTime(mDuriationTime * 1000.0f), mValue(0.0f), mOffset(1.0f / static_cast<float>(mDimX), 1.0f / static_cast<float>(mDimY)), mMipLevel(1.0f),
	mRealDimX(mDimX), mRealDimY(mDimY)
{
	Init(resourceLoad, mDimX, mDimY);
}

DrawFullScreen::DrawEndGameBlur::~DrawEndGameBlur()
{
	delete mFramebufferResource;
}

void DrawFullScreen::DrawEndGameBlur::Init(Resource::ResourceBase *resourceLoad, uint32_t mDimX, uint32_t mDimY)
{
	mMipLevel = glm::min(glm::log2(static_cast<float>(mDimX)), glm::log2(static_cast<float>(mDimY))) * 0.4f;

	this->mDimX = ToPow2(glm::max(mDimX >> 1, 1U));
	this->mDimY = ToPow2(glm::max(mDimY >> 1, 1U));

	mFramebufferResource = new Framebuffer::FramebufferResource(this->mDimX, this->mDimY);
	mFullScreenBuffer = new FullScreenBuffer::FullScreenQuadBuffer();

	mDrawBlur = new DrawBlur(resourceLoad, mFramebufferResource->GetFramebufferTexture(), mFullScreenBuffer);
}

uint32_t DrawFullScreen::DrawEndGameBlur::ToPow2(uint32_t mVal)
{
	uint32_t mPow2 = 0;
	while (mVal) { ++mPow2; mVal >>= 1; };
	if (mPow2)
		mPow2 = glm::max(mPow2, 0U);
	else
		mPow2 = 0U;

	return 1 << mPow2;
}

void DrawFullScreen::DrawEndGameBlur::Resize(uint32_t mDimX, uint32_t mDimY)
{
	this->mDimX = ToPow2(glm::max(mDimX , 1U)); //mDimX;// ToPow2(glm::max(mDimX >> 1, 1U));
	this->mDimY = ToPow2(glm::max(mDimY , 1U)); //mDimY;// ToPow2(glm::max(mDimY >> 1, 1U));
	mOffset = glm::vec2(1.0f / static_cast<float>(this->mDimX), 1.0f / static_cast<float>(this->mDimY));
	mMipLevel = glm::min(glm::log2(static_cast<float>(this->mDimX)), glm::log2(static_cast<float>(this->mDimY))) * 0.25f;
	mRealDimX = mDimX;
	mRealDimY = mDimY;

	mFramebufferResource->Resize(this->mDimX, this->mDimY);//mDimX >> 1, mDimY >> 1);
	mDrawBlur->ResetSourceTexture(mFramebufferResource->GetFramebufferTexture());
}

void DrawFullScreen::DrawEndGameBlur::ResetCameraFov(Camera::MCamera *mCamera)
{
	mCamera->Resize(mDimX, mDimY);
	//glViewport(0, 0, mDimX, mDimY);
}

bool DrawFullScreen::DrawEndGameBlur::IsEndBlur(void)
{
	return mValue >= 1.0;
}

void DrawFullScreen::DrawEndGameBlur::BeginDrawBlurredObject(void)
{
	glViewport(0, 0, mDimX, mDimY);
	mFramebufferResource->SetFramebufferToDraw();
}

void DrawFullScreen::DrawEndGameBlur::EndDrawBlurredObject(void)
{
	mFramebufferResource->SetScreenFramebuffer();
	glViewport(0, 0, mRealDimX, mRealDimY);
}

void DrawFullScreen::DrawEndGameBlur::Update(float fDeltaTime, float fGlobalTime)
{
	mLocalTime += fDeltaTime;
	//mLocalTime = glm::max(mLocalTime - mDelayTime, 0.0f);
		
	mValue = glm::min(glm::max(0.0f, mLocalTime) / mDuriationTime, 1.0f);
}

void DrawFullScreen::DrawEndGameBlur::ShowBlur(void)
{
	const float mS = 0.92f;
	glDisable(GL_DEPTH_TEST);
	mDrawBlur->Draw( glm::vec4( mOffset, glm::pow(mValue, mS), mMipLevel * glm::sin(glm::pow(mValue, mS) * 1.5707963267948966192313216916398f) ));
	glEnable(GL_DEPTH_TEST);
}
