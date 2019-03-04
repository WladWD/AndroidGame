#include "Engine.h"


GameEngine::Engine::Engine(JNIEnv *env, jobject rmng) : fCylinderHeight(128.0f), fCylinderRadius(4.0f), fStartAttention(fCylinderHeight * 0.6f), fEndAttention(fCylinderHeight * 0.98f), uSectorsCount(4),
fRotateAngle(2.0f * glm::pi<float>() / float(uSectorsCount)), fRotateTimeMs(0.005f), fMoveSpeed(32.0f),//64.0f
fCamOffset(-fCylinderRadius * 0.4f), fCookieMinYOffset(-fCylinderHeight * 0.0818f), //  ;;; 0.18f  ;fCamOffset(-fCylinderRadius * 0.8f)
mIntersect(false), mEndGame(false), mSleepApplication(false), width(1), height(1), mStopUpdate(false)
{	
	srand(time(0));

	Resource::ResourceBase *resourceLoad;
#if defined(_WIN64) | defined(_WIN32)	
	resourceLoad = new Resource::FileResource(env, rmng);
#else
	resourceLoad = new Resource::AssetResource(env, rmng);
#endif
	float mCookieZOffset = -fCylinderRadius * 0.8f + fCylinderRadius * 0.00018f;
	mMapResource = new Resource::MapResource();
	Resource::TextureLoad *textureLoad = new Resource::TextureLoad(mMapResource, resourceLoad);

	//Resource::GLTextureResource glTexRes = mMapResource->GetResourceByID(textureLoad->LoadFromResource("textures\\pipe\\1.rif"));
	float d1 = (1.0f - 0.85f);
	mScore = new Score::Score(mMapResource, textureLoad, resourceLoad, "resource\\textures\\font\\0001.rif",
		"resource\\textures\\score\\sugar\\1.rif",
		"resource\\textures\\score\\coffee\\1.rif",
		"resource\\textures\\score\\score\\2.rif",
		glm::vec4(0.55f, 0.85f, 0.85f, 1.0f),
		glm::vec4(0.85f, 0.85f, 1.0f, 1.0f),

		glm::vec4(0.55f, 0.85f - d1, 0.85f, 1.0f - d1),
		glm::vec4(0.85f, 0.85f - d1, 1.0f, 1.0f - d1),

		glm::vec4(0.55f, 0.85f - 2.0f * d1, 0.85f, 1.0f - 2.0f * d1),
		glm::vec4(0.85f, 0.85f - 2.0f * d1, 1.0f, 1.0f - 2.0f * d1),
		10);

	cCamera = new Camera::MCamera(1.0f, 1.0f, fEndAttention, width, height, fCamOffset, fRotateAngle, fRotateTimeMs);
	mDrawEndGame = new DrawCookie::EndGameDraw(4.0f, 1.0f, 8.0f, 1.0f, cCamera); //4.0f, 8.0f, 8.0f, cCamera);//4.0f, 1.0f, 8.0f, cCamera); // 4.0f, 1.0f, 8.0f, 1.0f, cCamera
	//mDrawPipe = new GameEngine::DrawPipe(resourceLoad, cCamera, fCylinderHeight, fCylinderRadius, fStartAttention, fEndAttention - fStartAttention, fFogColor, glTexRes);
	//mGlobalMove = new GlobalMove(fCylinderHeight, fMoveSpeed);
	mDrawPipe = new DrawPipe::PipeDrawControl(resourceLoad, textureLoad, mMapResource, cCamera, fCylinderHeight,
		fCylinderRadius, 16, 8, fStartAttention, fEndAttention - fStartAttention, fFogColor, fCylinderHeight, fMoveSpeed, fCookieMinYOffset,
		fRotateAngle, mCookieZOffset, -14.0f, 3, 9, uSectorsCount, 0.002f, mCookieZOffset, mScore);
	/*ifstream mif("parameter.txt");
	double a, b;
	mif >> a >> b;
	mif.close();*/


	//-----mDrawEndGameBlur = new DrawFullScreen::DrawEndGameBlur(resourceLoad, width, height, 0.5f, 2.0f);//0.4f, 0.6f);//0.7f);

	mDrawCookie = new DrawCookie::CookieDrawControl(resourceLoad, cCamera, mDrawEndGame->GetCookieDestroy(), mCookieZOffset, fCookieMinYOffset, (fCylinderRadius - abs(fCamOffset)));//0.18f
	mDrawEndGame->ReinitData();
	mTimer = new Timer::TimerSteady();//TimerSteady TimerHighResolution

	SetOpenGLFeature();

	delete resourceLoad;
	delete textureLoad;
}

GameEngine::Engine::~Engine()
{
	delete cCamera;
	//delete mDrawPipe;
	//delete mGlobalMove;
	delete mMapResource;
	delete mDrawPipe;
	delete mDrawCookie;
	delete mDrawEndGame;
	delete mScore;
	//-----delete mDrawEndGameBlur;
	delete mTimer;
}

void GameEngine::Engine::SetCookieDrawType(uint32_t mIndex, JNIEnv *env, jobject rmng)
{
	Resource::ResourceBase *resourceLoad;
#if defined(_WIN64) | defined(_WIN32)	
	resourceLoad = new Resource::FileResource(env, rmng);
#else
	resourceLoad = new Resource::AssetResource(env, rmng);
#endif

	mDrawCookie->SetCookieIndexDraw(mIndex, resourceLoad, mDrawEndGame->GetCookieDestroy(), fCamOffset, fCookieMinYOffset, (fCylinderRadius - abs(fCamOffset)));
	mDrawEndGame->ReinitData();

	delete resourceLoad;
}

void GameEngine::Engine::SetPipeDrawType(uint32_t mIndex, JNIEnv *env, jobject rmng)
{
	Resource::ResourceBase *resourceLoad;
#if defined(_WIN64) | defined(_WIN32)	
	resourceLoad = new Resource::FileResource(env, rmng);
#else
	resourceLoad = new Resource::AssetResource(env, rmng);
#endif

	Resource::TextureLoad *textureLoad = new Resource::TextureLoad(mMapResource, resourceLoad);

	mDrawPipe->SetCookieIndexDraw(mIndex, resourceLoad, textureLoad, mMapResource, fCylinderHeight,
		fCylinderRadius, 16, 8, fStartAttention, fEndAttention - fStartAttention, fFogColor);

	delete textureLoad;
	delete resourceLoad;
}

void GameEngine::Engine::PauseApplication(void)
{
}

void GameEngine::Engine::ResumeApplication(JNIEnv * env, jobject rmng)
{
}

void GameEngine::Engine::Tick(void)
{
	mTimer->Tick();
}

/*void GameEngine::Engine::PauseApplication(void)
{
	mSleepApplication = true;
	//ReleaseResource();
	mTimer->Pause();
}

void GameEngine::Engine::ResumeApplication(JNIEnv *env, jobject rmng) 
{
	ReCreateResource(env, rmng);
	mTimer->Resume();
	mSleepApplication = false;
}*/

void GameEngine::Engine::Resize(uint32_t width, uint32_t height) 
{
	width = glm::max(width, 1u);
	height = glm::max(height, 1u);

	this->width = width;
	this->height = height;

	//------mDrawEndGameBlur->Resize(width, height);

	cCamera->ReCreateProjMatrix(1.0f, 1.0, fEndAttention, width, height);

	glViewport(0, 0, width, height);
}

void GameEngine::Engine::SetOpenGLFeature(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClearColor(fFogColor[0], fFogColor[1], fFogColor[2], fFogColor[3]);
	glClearDepthf(1.0f);
}

void GameEngine::Engine::RotateLeft(void)
{
	if(!mIntersect) 
		cCamera->RotateLeft();
}

void GameEngine::Engine::RotateRight(void)
{
	if (!mIntersect)
		cCamera->RotateRight();
}

void GameEngine::Engine::Intersect(float fDeltaTime, float fGlobalTime)
{
	cCamera->Update(fDeltaTime, fGlobalTime);
	mDrawCookie->Update(fDeltaTime, fGlobalTime);
	mDrawPipe->Update(fDeltaTime, fGlobalTime);
	mScore->UpdateScore(mDrawPipe->GetDeltaDistance());

	mIntersect = mDrawPipe->Intersect(mDrawCookie->GetCookieCollision());//mDrawCookie->GetObjectData(), mDrawCookie->GetBoundingObject());
}

bool GameEngine::Engine::Vibrate(void)
{
	return mIntersect;
}

/*void GameEngine::Engine::ReleaseResource(void)
{
	delete mMapResource;

	mDrawPipe->ReleaseResource();
	mDrawCookie->ReleaseResource();
}

void GameEngine::Engine::ReCreateResource(JNIEnv *env, jobject rmng)
{
	SetOpenGLFeature();

	Resource::ResourceBase *resourceLoad;
#if defined(_WIN64) | defined(_WIN32)	
	resourceLoad = new Resource::FileResource(env, rmng);
#else
	resourceLoad = new Resource::AssetResource(env, rmng);
#endif

	mMapResource = new Resource::MapResource();
	Resource::TextureLoad *textureLoad = new Resource::TextureLoad(mMapResource, resourceLoad);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	mDrawPipe->ReCreateResource(resourceLoad, textureLoad, mMapResource);

	mDrawCookie->ReCreateResource(resourceLoad);
	mDrawEndGame->ReinitData();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete resourceLoad;
	delete textureLoad;
}
*/
bool GameEngine::Engine::EndGame(void)//float fDeltaTime, float fGlobalTime)
{
	//if (mEndGame)
	//	return false;
	//bool mCloseGame = mStopUpdate;// false;

	///static bool once = false;
	if (mSleepApplication)
		return mEndGame;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float fDeltaTime = mTimer->GetDelataTime();
	float fGlobalTime = mTimer->GetGlobalTime();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//if (mIntersect && !once) 
	//{
	//	once = true;
	//	mDrawEndGameBlur->ResetCameraFov(cCamera);
	//}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!mIntersect)
		Intersect(fDeltaTime, fGlobalTime);
	else
	{
		if (!mStopUpdate) 
		{
			cCamera->UpdateOnly(fDeltaTime, fGlobalTime);
			mDrawEndGame->Update(fDeltaTime, fGlobalTime);
			mEndGame = mDrawEndGame->CheckEndGame();

			//mCloseGame = mEndGame;
			//mCloseGame &= BlurEndGame();
			//mStopUpdate = mCloseGame;
			mStopUpdate = mEndGame;
		}
	}

	return mEndGame; //false;// mEndGame;mCloseGame
}

//bool GameEngine::Engine::BlurEndGame(void)
//{
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	float fDeltaTime = mTimer->GetDelataTime();
//	float fGlobalTime = mTimer->GetGlobalTime();
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	mDrawEndGameBlur->Update(fDeltaTime, fGlobalTime);
//	return mDrawEndGameBlur->IsEndBlur();
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//}

void GameEngine::Engine::Draw(void)//float fDeltaTime, float fGlobalTime)
{
	if (mSleepApplication)
		return;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//float fDeltaTime = mTimer->GetDelataTime();
	//float fGlobalTime = mTimer->GetGlobalTime();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	//Draw Block
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///////////////////////////////////////////////////////////////////////////////////////
	//mDrawPipe->Draw(mGlobalMove->GetMoveMatrix(), fDeltaTime, fGlobalTime);
	///////////////////////////////////////////////////////////////////////////////////////
	if (!mIntersect)
	{
		mDrawCookie->Draw();
		mDrawPipe->Draw();
		mScore->DrawScore();
	}
	else
	{
		////////////////////////////////////////////////////////////
		//if(mIntersect)//mIntersect mEndGame
		//	mDrawEndGameBlur->BeginDrawBlurredObject();
		////////////////////////////////////////////////////////////
		mDrawPipe->Draw();
		////////////////////////////////////////////////////////////
		mDrawEndGame->BeginDrawCookie();
		mDrawCookie->DrawDestroyCookie();
		mDrawEndGame->EndDrawCookie();
		////////////////////////////////////////////////////////////
		//mDrawEndGame->Draw();
		////////////////////////////////////////////////////////////
		//if(mIntersect)
		//	mDrawEndGameBlur->EndDrawBlurredObject();
		////////////////////////////////////////////////////////////
		//glViewport(0, 0, width, height);
		//if(mIntersect)
		//	mDrawEndGameBlur->ShowBlur();
		////////////////////////////////////////////////////////////
	}
	///////////////////////////////////////////////////////////////////////////////////////
}