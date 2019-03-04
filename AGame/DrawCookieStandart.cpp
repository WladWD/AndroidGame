#include "DrawCookieStandart.h"


DrawCookie::DrawCookieStandart::DrawCookieStandart(Draw::Cookie *mCookie, Resource::ResourceBase *mResourceLoad, Camera::MCamera *cCamera,
	float fZOffset, float fYOffset, float fScale) :
	DrawCookieBase(mCookie, cCamera)
{
	Init(mResourceLoad);
	//InitAttrib();

	mRandomRotation = new Random::RandomRotation(0.0f, 0.2f, 0.2f, 1.0f, 
												0.0f, 0.0f, 1.0f, 4.0f,
												0.0f, 0.2f, 0.2f, 1.0f);
	mWorld = glm::mat4(1.0f);
	mTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, fYOffset, fZOffset)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.4f, 0.4f));//потом загружать модели без масштаба
}

DrawCookie::DrawCookieStandart::~DrawCookieStandart()
{
	delete mShader;
	delete mShaderDestroy;
	delete mRandomRotation;
}

void DrawCookie::DrawCookieStandart::Init(Resource::ResourceBase * mResourceLoad)
{
	mShader = new Shader::ShaderCookie1(mResourceLoad);
	mShaderDestroy = new Shader::ShaderCookieDestroy(mResourceLoad);
}

void DrawCookie::DrawCookieStandart::InitAttrib(void)
{
	glUseProgram(mShader->GetProgram());

	GLint sAttribLocationPosition = mShader->GetPositionAttrib();
	//GLint sAttribLocationNormal = mShader->GetNormalAttrib();
	GLint sAttribLocationTex = mShader->GetTexCoordAttrib();

	/*glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);*/
	
	mModelDraw->BindBuffers();
	
	int32_t stride = sizeof(Mesh::VTMesh);
	int32_t offset = 0;

	for (register uint32_t i = 0; i < 8; i++) glDisableVertexAttribArray(i);

	glVertexAttribPointer(sAttribLocationPosition, 3, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
	glEnableVertexAttribArray(sAttribLocationPosition);

	/*offset += sizeof(glm::vec3);
	glVertexAttribPointer(sAttribLocationNormal, 3, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
	glEnableVertexAttribArray(sAttribLocationNormal);*/

	offset += sizeof(glm::vec3);
	if (sAttribLocationTex != (-1)) 
	{
		glVertexAttribPointer(sAttribLocationTex, 2, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
		glEnableVertexAttribArray(sAttribLocationTex);
	}

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	mModelDraw->UnBindBuffers();

	mShader->BindTextureToSlot();

	glUseProgram(0);
	mShader->ResetProgram();
}

void DrawCookie::DrawCookieStandart::InitAttribDestroy(void)
{
	glUseProgram(mShaderDestroy->GetProgram());

	GLint sAttribLocationPosition = mShaderDestroy->GetPositionAttrib();
	//GLint sAttribLocationNormal = mShader->GetNormalAttrib();
	GLint sAttribLocationTex = mShaderDestroy->GetTexCoordAttrib();

	/*glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);*/
	mModelDraw->BindBuffers();

	int32_t stride = sizeof(Mesh::VTMesh);
	int32_t offset = 0;

	for (register uint32_t i = 0; i < 8; i++) glDisableVertexAttribArray(i);

	glVertexAttribPointer(sAttribLocationPosition, 3, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
	glEnableVertexAttribArray(sAttribLocationPosition);

	/*offset += sizeof(glm::vec3);
	glVertexAttribPointer(sAttribLocationNormal, 3, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
	glEnableVertexAttribArray(sAttribLocationNormal);*/

	offset += sizeof(glm::vec3);
	if (sAttribLocationTex != (-1))
	{
		glVertexAttribPointer(sAttribLocationTex, 2, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
		glEnableVertexAttribArray(sAttribLocationTex);
	}

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/
	mModelDraw->UnBindBuffers();

	mShaderDestroy->BindTextureToSlot();

	glUseProgram(0);
	mShaderDestroy->ResetProgram();
}

void DrawCookie::DrawCookieStandart::Update(float fDeltaTime, float fGlobalTime)
{
	mRandomRotation->Update(fDeltaTime, fGlobalTime);

	mWorld = cCamera->GetRotateMatrix() * mTranslate * mRandomRotation->GetTransormMatrix();
	//mBoundingSphere->Transform(mWorld);
	mSphere->SetWorld(mWorld);
	mLowpolyModel->SetWorld(mWorld);
}


void DrawCookie::DrawCookieStandart::DrawDestroyedCookie(void)
{
	InitAttribDestroy();
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShaderDestroy->GetProgram());

	/*glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);*/
	mModelDraw->BindBuffers();

	mShaderDestroy->SetProjViewMatrix(cCamera->GetProjViewMatrix());
	mShaderDestroy->SetWorldMatrix(mWorld);
	mShaderDestroy->SetGlobalData(glm::vec2(mCookieDestroy->mGlobalTime, mCookieDestroy->mVisibility));
	mShaderDestroy->SetMovePices(mCookieDestroy->mMoveDirections, mModelDraw->GetDrawObjectCount());//mDrawObjectCount);

	for (register uint32_t i = 0; i < mModelDraw->GetDrawObjectCount(); i++)
	{
		//Resource::GLTextureResource glTexRes = mImagesResource->GetTextureByID(mObjects[i].GetTextureID(0));
		//mShaderDestroy->SetPipeTexture();
		//glBindTexture(glTexRes.texture_target, glTexRes.texture);

		mShaderDestroy->SetDrawPiceID(i);

		mShaderDestroy->SetPipeTexture();
		mModelDraw->Draw(i);//перед вызовом установрить текущую текстуру
		//glDrawElements(GL_TRIANGLES, mObjects[i].GetIndexCount(), mIndexFormat, (const void *)(mObjects[i].GetIndexOffset()));//GL_TRIANGLES GL_LINES GL_UNSIGNED_SHORT 0x1403
	}
	//GLenum err = glGetError();
	///////////////////////////////////////////////////////////////////////////////
	mShaderDestroy->ResetProgram();
	glUseProgram(0);

	/*glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
	mModelDraw->UnBindBuffers();
}

void DrawCookie::DrawCookieStandart::Draw(void)
{
	InitAttrib();
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShader->GetProgram());

	/*glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);*/
	mModelDraw->BindBuffers();

	mShader->SetProjViewMatrix(cCamera->GetProjViewMatrix());

	for (register uint32_t i = 0; i < mModelDraw->GetDrawObjectCount(); i++)
	{
		mShader->SetWorldMatrix(mWorld);

		//Resource::GLTextureResource glTexRes = mImagesResource->GetTextureByID(mObjects[i].GetTextureID(0));
		//mShader->SetPipeTexture();
		//glBindTexture(glTexRes.texture_target, glTexRes.texture);

		//glDrawElements(GL_TRIANGLES, mObjects[i].GetIndexCount(), mIndexFormat, (const void *)(mObjects[i].GetIndexOffset()));//GL_TRIANGLES GL_LINES GL_UNSIGNED_SHORT 0x1403
		mShader->SetPipeTexture();
		mModelDraw->Draw(i);
	}
	//GLenum err = glGetError();
	///////////////////////////////////////////////////////////////////////////////
	mShader->ResetProgram();
	glUseProgram(0);

	/*glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
	mModelDraw->UnBindBuffers();
}
