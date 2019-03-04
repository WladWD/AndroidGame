#include "CollectStandart.h"


Draw::CollectStandart::CollectStandart(Draw::Collect * mCollect, Camera::MCamera * cCamera, float mHeight, 
	float mAngle, float fZOffset, glm::vec2 fFog, const float * fFogColor, float mRotateVel,
	Shader::ShaderCollectBase * mShaderCollect, float mRotateVal, float HeightShowConst, DrawFlash::DrawFlashCreator *mDrawFlash) :
	CollectBase(mCollect, cCamera, mHeight, mAngle), mShader(mShaderCollect), fFog(fFog), fFogColor(fFogColor),
	mRotateVel(mRotateVel), fZOffset(fZOffset), mRotateVal(mRotateVal), HeightShowConst(HeightShowConst)
{
	mRandom = new Engine::RandomNormal();

	mRotateGlobal = glm::rotate(glm::mat4(), mAngle, glm::vec3(0.0f, 1.0f, 0.0f));

	RandomizeAngle();
	float mTime = 200.0;
	this->mDrawFlash = mDrawFlash->CreateDrawFlash({ 0.4f, 1.4f, mTime }, { 0.4f, 1.0f, mTime });//1.2f
	Present(mHeight, mAngle, mRotateVel);
}

Draw::CollectStandart::~CollectStandart()
{
	delete mRandom;
	delete mDrawFlash;
}

void Draw::CollectStandart::InitAttrib(void)
{
	glUseProgram(mShader->GetProgram());

	GLint sAttribLocationPosition = mShader->GetPositionAttrib();
	GLint sAttribLocationTex = mShader->GetTexCoordAttrib();

	mModelDraw->BindBuffers();

	int32_t stride = sizeof(Mesh::VTMesh);
	int32_t offset = 0;

	for (register uint32_t i = 0; i < 8; i++) glDisableVertexAttribArray(i);

	glVertexAttribPointer(sAttribLocationPosition, 3, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
	glEnableVertexAttribArray(sAttribLocationPosition);

	offset += sizeof(glm::vec3);
	if (sAttribLocationTex != (-1))
	{
		glVertexAttribPointer(sAttribLocationTex, 2, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
		glEnableVertexAttribArray(sAttribLocationTex);
	}

	mModelDraw->UnBindBuffers();

	mShader->BindTextureToSlot();

	glUseProgram(0);
	mShader->ResetProgram();
}

void Draw::CollectStandart::RandomizeAngle(void)
{
	//mDeltaConst = std::rand() & 1 ? 1.0f : -1.0f;
	const double mRotateConst = 0.082f;
	mRotateVal += mRandom->GetNextDouble() * mDeltaConst * PI * 2.0f * mRotateConst;
}

bool Draw::CollectStandart::Intersect(const Draw::CookieCollisionStruct & mCookieCollision)
{
	if (!mIntersect)
	{
		mIntersect = Bounding::SphereSphereIntersect(mSphere, mCookieCollision.mBoundingCookie);
		return mIntersect;
		//if (mIntersect)
			//score->Inc;
		//	;
	}

	
	return false;
}

void Draw::CollectStandart::Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight)
{
	if (mIntersect )//&& !mDrawFlash->EndFlash())
	{
		/*update draw collection method*/;
		mHeight = HeightShowConst;
		mDrawFlash->Update(fDeltaTime);
		return;
	}

	if (mHeight >= HeightShowConst)
		return;

	UpdateRotate(fDeltaTime, fGlobalTime);
	mHeight += fDeltaHeight;
	mTranslateGlobal = glm::translate(glm::mat4(), glm::vec3(0.0f, mHeight, fZOffset));
	mWorld = mRotateGlobal * mTranslateGlobal * mRotateLocal;

	mSphere->SetWorld(mWorld);
}

void Draw::CollectStandart::UpdateRotate(float fDeltaTime, float fGlobalTime)
{
	mRotateVal += fDeltaTime * mRotateVel * mDeltaConst;
	mRotateLocal = glm::rotate(glm::mat4(), mRotateVal, glm::vec3(0.0f, 1.0f, 0.0f));

	if (mRotateVal >= 2.0f * glm::pi<float>()) mRotateVal -= 2.0f * glm::pi<float>();
	else if(mRotateVal <= -2.0f * glm::pi<float>()) mRotateVal += 2.0f * glm::pi<float>();
}

void Draw::CollectStandart::DrawEvent(void)
{
	//mDrawFlash->Update(16);// fDeltaTime);
	mDrawFlash->Draw();
}

void Draw::CollectStandart::Draw(void)
{
	if (mIntersect){
		//DrawEvent();
		return;
	}
	else if (mHeight >= HeightShowConst)
		return;

	InitAttrib();
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShader->GetProgram());
	///////////////////////////////////////////////////////////////////////////////
	mModelDraw->BindBuffers();

	mShader->SetProjViewMatrix(cCamera->GetProjViewMatrix());
	mShader->SetFog(fFog);
	mShader->SetFogColor(fFogColor);
	///////////////////////////////////////////////////////////////////////////////
	for (register uint32_t i = 0; i < mModelDraw->GetDrawObjectCount(); i++)
	{
		mShader->SetWorldMatrix(mWorld);

		mShader->SetTexture();
		mModelDraw->Draw(i);
	}
	///////////////////////////////////////////////////////////////////////////////
	mShader->ResetProgram();
	glUseProgram(0);

	mModelDraw->UnBindBuffers();
}

void Draw::CollectStandart::DrawFlash(void) 
{
	if (mIntersect)
		mDrawFlash->Draw();
}

bool Draw::CollectStandart::IsCollected(void)
{
	return mIntersect;
}

bool Draw::CollectStandart::Present(float mHeight, float mAngle, float mRotateVel)
{
	if (mIntersect && !mDrawFlash->EndFlash())
		return false;
	mIntersect = mPicked = false;
	this->mRotateVel = mRotateVel;
	this->mHeight = mHeight;
	this->mAngle = mAngle;

	//mDeltaConst = std::rand() & 1 ? 1.0f : -1.0f;
	//const double mRotateConst = 0.2f;
	//mRotateVal += mRandom->GetNextDouble() * mDeltaConst * PI * 2.0f * mRotateConst;

	mRotateLocal = glm::rotate(glm::mat4(), mRotateVal, glm::vec3(0.0f, 1.0f, 0.0f));
	mTranslateGlobal = glm::translate(glm::mat4(), glm::vec3(0.0f, mHeight, fZOffset));
	mWorld = mRotateGlobal * mTranslateGlobal * mRotateLocal;
	mSphere->SetWorld(mWorld);

	mDrawFlash->Present();
	return true;
}
