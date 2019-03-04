#include "DrawFlashBase.h"


DrawFlash::DrawFlashBase::DrawFlashBase(Shader::ShaderDrawFlash * mShader, FlashResourceBuffer * mResourceBuffer, 
	FlashResourceTexture * mFlashTexture, Interpolate::InterpolateData mScale, Interpolate::InterpolateData mAlpha, 
	float fYOffset, float fZOffset,
	Camera::MCamera *mCamera) : mShader(mShader), mResourceBuffer(mResourceBuffer),
	mFlashTexture(mFlashTexture), mCamera(mCamera), once(false), mDelta(1.2f), mZDelta(0.2f)
{
	this->mScale = new Interpolate::LinearInterpolateData(mScale);
	this->mAlpha = new Interpolate::LinearInterpolateData(mAlpha);

	mTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, fYOffset - mDelta, fZOffset + mZDelta));
	Present();
}

DrawFlash::DrawFlashBase::~DrawFlashBase()
{
	delete mScale;
	delete mAlpha;
}

void DrawFlash::DrawFlashBase::Present(void)
{
	mWorld = mCamera->GetRotateMatrix() * mTranslate;
	mScale->Present();
	mAlpha->Present();
	once = false;
}

void DrawFlash::DrawFlashBase::Update(float mDtMs)
{
	mWorld = mCamera->GetRotateMatrix() * mTranslate;
	mScale->Update(mDtMs);
	mAlpha->Update(mDtMs);
}

void DrawFlash::DrawFlashBase::InitAttrib(void)
{
	//programm mast binding!!!

	/*attribute vec3 gWorldPos;
attribute vec4 gOffset_Tex;*/

	mResourceBuffer->BindBuffer();

	GLint gWorldPos = mShader->GetPositionAttrib();
	GLint gOffset_Tex = mShader->GetOffsetTexAttrib();

	uint32_t mStride = sizeof(glm::vec3) + sizeof(glm::vec4);
	uint32_t offset = 0;
	if (gWorldPos != (-1)) 
	{
		glVertexAttribPointer(gWorldPos, 3, GL_FLOAT, GL_FALSE, mStride, (const void *)offset);
		glEnableVertexAttribArray(gWorldPos);
	}

	offset += sizeof(glm::vec3);
	if (gOffset_Tex != (-1))
	{
		glVertexAttribPointer(gOffset_Tex, 4, GL_FLOAT, GL_FALSE, mStride, (const void *)offset);
		glEnableVertexAttribArray(gOffset_Tex);
	}

	mShader->BindTextureToSlot();
}

void DrawFlash::DrawFlashBase::Draw(void)
{
	if (once)
		return;
	mWorld = mCamera->GetRotateMatrix() * mTranslate;
	//Update(16.0);
	//////////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShader->GetProgram());
	InitAttrib();
	//////////////////////////////////////////////////////////////////////////////////
	mShader->SetFlashTexture();
	auto mTex = mFlashTexture->GetTexture();
	glBindTexture(mTex.texture_target, mTex.texture);
	
	mShader->SetCamPos(glm::vec4(mCamera->GetCameraPosition(), 1.0f));//glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));//
	mShader->SetProjViewMatrix(mCamera->GetProjViewMatrix());
	mShader->SetUpVector(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	mShader->SetScaleAlpha(glm::vec2(mScale->GetValue(), mAlpha->GetValue()));
	mShader->SetWorldMatrix(mWorld);
	//////////////////////////////////////////////////////////////////////////////////
	glEnable(GL_BLEND);

	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glDisable(GL_DEPTH_TEST);
	//////////////////////////////////////////////////////////////////////////////////
	mResourceBuffer->Draw();
	//////////////////////////////////////////////////////////////////////////////////
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	//////////////////////////////////////////////////////////////////////////////////
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	//////////////////////////////////////////////////////////////////////////////////
	mResourceBuffer->UnbindBuffer();
	mShader->ResetProgram();
	glUseProgram(0);
	//////////////////////////////////////////////////////////////////////////////////
	once = mAlpha->EndLerp();
}

bool DrawFlash::DrawFlashBase::EndFlash(void)
{
	return once;
}
