#include "EndGameDraw.h"


DrawCookie::EndGameDraw::EndGameDraw(float mEndGameDuration, float fEndGameTime, float mVel, float mEndGameAttantionTime, Camera::MCamera *mCamera) : mEndGameDuration(mEndGameDuration * 1000.0f),
mEndGameLocalTime(0.0f), mVel(mVel), fEndGameTime(fEndGameTime * 1000.0f), mCamera(mCamera)
{
	mRandom = new Random::RandomRotationAttenuation(0.0f, 0.1f, 0.0001f, 1e-3f, 0.1f, mEndGameAttantionTime,
										0.0f, 0.0f, 0.0f, 0.0f, 0.0f, mEndGameAttantionTime,
										0.0f, 0.1f, 0.0001f, 1e-3f, 0.1f, mEndGameAttantionTime);

	/*0.0f, 0.1f, 1e-3f, 0.1f, 
										0.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 0.1f, 1e-3f, 0.1f*/
}

DrawCookie::EndGameDraw::~EndGameDraw()
{
	delete mRandom;
}

void DrawCookie::EndGameDraw::Update(float fDeltaTime, float fGlobalTime)
{
	mEndGameLocalTime += fDeltaTime;

	mCookieDestroy->mGlobalTime += fDeltaTime / 1000.0f;//second
	mCookieDestroy->mVisibility = glm::pow(1.0f - glm::clamp(mEndGameLocalTime / mEndGameDuration, 0.0f, 1.0f), 4.0f);


	mRandom->Update(fDeltaTime, fGlobalTime);
	mCamera->SetRandomNoise(mRandom->GetTransormMatrix());
}

void DrawCookie::EndGameDraw::Draw(void)
{
}

bool DrawCookie::EndGameDraw::CheckEndGame(void)
{
	return mEndGameLocalTime >= fEndGameTime;//mEndGameDuration;
}

void DrawCookie::EndGameDraw::BeginDrawCookie(void)
{
	glEnable(GL_BLEND);

	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DrawCookie::EndGameDraw::EndDrawCookie(void)
{
	glDisable(GL_BLEND);
}

void DrawCookie::EndGameDraw::ReinitData(void)
{
	mCookieDestroy->mGlobalTime = 0.0f;
	mCookieDestroy->mVisibility = 0.0f;
	/*for (register uint32_t i = 0; i < COOKIE_PICES_COUNT; i++) 
		mCookieDestroy.mMoveDirections[i].w = mVel;*/

	for (register uint32_t i = 0; i < COOKIE_PICES_COUNT; i++)
		mCookieDestroy->mMoveDirections[i] = glm::vec4(glm::normalize(glm::vec3(mCookieDestroy->mPicesCenter[i]) ), mVel);//glm::normalize
	//- glm::vec3(mCookieDestroy.mCenter)
											//glm::vec4((glm::vec3(mCookieDestroy.mPicesCenter[i])), mVel);//glm::normalize
}

DrawCookie::CookieDestroy ** DrawCookie::EndGameDraw::GetCookieDestroy(void)
{
	return &mCookieDestroy;
}
