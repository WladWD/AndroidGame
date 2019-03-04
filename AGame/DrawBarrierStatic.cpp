#include "DrawBarrierStatic.h"


Barrier::DrawBarrierStatic::DrawBarrierStatic(Draw::Barrier *mBarrier, Shader::ShaderBarrierBase *mShader, Camera::MCamera *cCamera,
	float fHeight, int32_t mSectorCount, float mBaseAngle, float mZoffset, glm::vec2 fFog, const float *fFogColor, 
	int32_t mRandomCounter, int32_t mMod) :
	BarrierBase(mBarrier, cCamera, fHeight), mShader(dynamic_cast<Shader::ShaderBarrierStatic *>(mShader)),
	fFog(fFog), fFogColor(fFogColor), mSectorCount(mSectorCount), mBaseAngle(mBaseAngle), mZoffset(mZoffset),
	mRandomCounter(mRandomCounter), mMod(mMod)
{
	Present(fHeight);
}

Barrier::DrawBarrierStatic::~DrawBarrierStatic() {

}

void Barrier::DrawBarrierStatic::InitAttrib(void)
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

void Barrier::DrawBarrierStatic::PresentSector(void)
{
	int32_t mlast = mCurSector;

	mRandomCounter = (mRandomCounter + rand()) % mMod;
	mCurSector = mRandomCounter % mSectorCount;
	if (mCurSector == mlast)
		mCurSector = (mCurSector + 1) % mSectorCount;
	
	fAngle = mBaseAngle * mCurSector;
	mRotateMatrix = glm::rotate(glm::mat4(), fAngle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Barrier::DrawBarrierStatic::Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight)
{
	fHeight += fDeltaHeight;
	mTranslateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, fHeight, mZoffset));

	mWorld = mRotateMatrix * mTranslateMatrix;

	mBounding->SetWorldMatrix(mWorld);
	mLowpolyModel->SetWorld(mWorld);
}

void Barrier::DrawBarrierStatic::Present(float fHeight)
{
	this->fHeight = fHeight;
	mTranslateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, fHeight, mZoffset));

	PresentSector();
	mWorld = mRotateMatrix * mTranslateMatrix;

	mBounding->SetWorldMatrix(mWorld);
	mLowpolyModel->SetWorld(mWorld);
}

void Barrier::DrawBarrierStatic::Draw(void)
{
	InitAttrib();
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShader->GetProgram());

	mModelDraw->BindBuffers();

	mShader->SetProjViewMatrix(cCamera->GetProjViewMatrix());
	mShader->SetFog(fFog);
	mShader->SetFogColor(fFogColor);

	for (register uint32_t i = 0; i < mModelDraw->GetDrawObjectCount(); i++)
	{
		mShader->SetWorldMatrix(mWorld);

		mShader->SetTexture();
		mModelDraw->Draw(i);
	}
	//GLenum err = glGetError();
	///////////////////////////////////////////////////////////////////////////////
	mShader->ResetProgram();
	glUseProgram(0);

	mModelDraw->UnBindBuffers();
}