#include "DrawBarrierRotor.h"


Barrier::DrawBarrierRotor::DrawBarrierRotor(Draw::Barrier *mBarrier, Shader::ShaderBarrierBase *mShader,
	Camera::MCamera *cCamera, float fHeight, float fVelMin, float fVelMax, glm::vec2 fFog, const float *fFogColor) :
	BarrierBase(mBarrier, cCamera, fHeight), mShader(dynamic_cast<Shader::ShaderBarrierRotor *>(mShader)),
	fFog(fFog), fFogColor(fFogColor), fVelMin(fVelMin / 1000.0f), fVelMax(fVelMax / 1000.0f)
{
	//Init();
	//InitAttrib();
	//fVel(fVel / 1000.0f),

	//fVel = glm::mix(this->fVelMin, this->fVelMax, (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));

	mRotateMatrix = glm::rotate(glm::mat4(), fAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	/*mTranslateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, fHeight, 0.0f));
	mWorld = mTranslateMatrix * mRotateMatrix;

	mBounding->SetWorldMatrix(mWorld);
	mLowpolyModel->SetWorld(mWorld);*/


	Present(fHeight);

#ifdef Test
	InitTMP();
#endif
}

Barrier::DrawBarrierRotor::~DrawBarrierRotor()
{
	//delete mShader;
#ifdef Test
	glDeleteBuffers(1, &vb);
	glDeleteBuffers(1, &ib);
#endif
}


void Barrier::DrawBarrierRotor::InitAttrib(void)
{
	glUseProgram(mShader->GetProgram());

	GLint sAttribLocationPosition = mShader->GetPositionAttrib();
	GLint sAttribLocationTex = mShader->GetTexCoordAttrib();

	//glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
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

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	mModelDraw->UnBindBuffers();

	mShader->BindTextureToSlot();

	glUseProgram(0);
	mShader->ResetProgram();
}

void Barrier::DrawBarrierRotor::UpdateRotate(float fDeltaTime, float fGlobalTime)
{
	fAngle += fDeltaTime * fVel * mDeltaConst;
	mRotateMatrix = glm::rotate(glm::mat4(), fAngle, glm::vec3(0.0f, 1.0f, 0.0f));

	//if (fAngle >= 2.0f * PI) fAngle -= 2.0f * PI;
	if (fAngle >= 2.0f * PI) fAngle -= 2.0f * PI;
	else if (fAngle <= -2.0f * PI) fAngle += 2.0f * PI;
}

void Barrier::DrawBarrierRotor::Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight)
{
	fHeight += fDeltaHeight;
	mTranslateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, fHeight, 0.0f));

	UpdateRotate(fDeltaTime, fGlobalTime);

	mWorld = mTranslateMatrix * mRotateMatrix;

	mBounding->SetWorldMatrix(mWorld);
	mLowpolyModel->SetWorld(mWorld);

	//mWorld_OOBB = mWorldMatrix * mRotateMatrix;
	//mBounding->SetWorldMatrix(mWorldMatrix * mRotateMatrix);
}

#ifdef Test
void Barrier::DrawBarrierRotor::InitTMP()
{
	float min_x, min_y, min_z;
	float max_x, max_y, max_z;

	glm::vec3 mc = mAABB->GetCenter();
	glm::vec3 me = mAABB->GetExtent();
	min_x = mc.x - me.x;
	min_y = mc.y - me.y;
	min_z = mc.z - me.z;

	max_x = mc.x + me.x;
	max_y = mc.y + me.y;
	max_z = mc.z + me.z;

	Mesh::VTMesh mv[8];
	GLushort ind_buffer[24];
	ind_buffer[0] = 0;
	ind_buffer[1] = 1;

	ind_buffer[2] = 1;
	ind_buffer[3] = 2;

	ind_buffer[4] = 2;
	ind_buffer[5] = 3;

	ind_buffer[6] = 3;
	ind_buffer[7] = 0;


	ind_buffer[8] = 0;
	ind_buffer[9] = 4;

	ind_buffer[10] = 1;
	ind_buffer[11] = 5;

	ind_buffer[12] = 2;
	ind_buffer[13] = 6;

	ind_buffer[14] = 3;
	ind_buffer[15] = 7;


	ind_buffer[16] = 4;
	ind_buffer[17] = 5;

	ind_buffer[18] = 5;
	ind_buffer[19] = 6;

	ind_buffer[20] = 6;
	ind_buffer[21] = 7;

	ind_buffer[22] = 7;
	ind_buffer[23] = 4;

	for (int i = 0; i < 8; i++)mv[i].gTexCoord = glm::vec2(0.0f, 0.0f);

	mv[0].gWorldPos = glm::vec3(min_x, min_y, min_z);
	mv[1].gWorldPos = glm::vec3(min_x, min_y, max_z);
	mv[2].gWorldPos = glm::vec3(max_x, min_y, max_z);
	mv[3].gWorldPos = glm::vec3(max_x, min_y, min_z);

	mv[4].gWorldPos = glm::vec3(min_x, max_y, min_z);
	mv[5].gWorldPos = glm::vec3(min_x, max_y, max_z);
	mv[6].gWorldPos = glm::vec3(max_x, max_y, max_z);
	mv[7].gWorldPos = glm::vec3(max_x, max_y, min_z);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);

	glBufferData(GL_ARRAY_BUFFER, sizeof(mv), mv, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind_buffer), ind_buffer, GL_STATIC_DRAW);
	//////////////////////////////////////////////////////////////////////////////////////
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
#endif

void Barrier::DrawBarrierRotor::Present(float fHeight)
{
	this->fHeight = fHeight;
	mTranslateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, fHeight, 0.0f));
	mWorld = mTranslateMatrix * mRotateMatrix;

	fVel = glm::mix(fVelMin, fVelMax, (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));

	mBounding->SetWorldMatrix(mWorld);
	mLowpolyModel->SetWorld(mWorld);
}

void Barrier::DrawBarrierRotor::Draw(void)
{
	InitAttrib();
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShader->GetProgram());

	//glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	mModelDraw->BindBuffers();

	mShader->SetProjViewMatrix(cCamera->GetProjViewMatrix());
	mShader->SetFog(fFog);
	mShader->SetFogColor(fFogColor);

	for (register uint32_t i = 0; i < mModelDraw->GetDrawObjectCount(); i++)
	{
		mShader->SetWorldMatrix(mWorld);

		//Resource::GLTextureResource glTexRes = mImagesResource->GetTextureByID(mObjects[i].GetTextureID(0));
		//mShader->SetTexture();
		//glBindTexture(glTexRes.texture_target, glTexRes.texture);

		mShader->SetTexture();
		mModelDraw->Draw(i);
		//glDrawElements(GL_TRIANGLES, mObjects[i].GetIndexCount(), mIndexFormat, (const void *)(mObjects[i].GetIndexOffset()));//GL_TRIANGLES GL_LINES GL_UNSIGNED_SHORT 0x1403
	}
	//GLenum err = glGetError();
	///////////////////////////////////////////////////////////////////////////////
	mShader->ResetProgram();
	glUseProgram(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	mModelDraw->UnBindBuffers();

#ifdef Test
	///
	//
	InitAttrib(vb, ib);
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShader->GetProgram());

	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

	mShader->SetProjViewMatrix(cCamera->GetProjViewMatrix());
	mShader->SetFog(fFog);
	mShader->SetFogColor(fFogColor);

	for (register uint32_t i = 0; i < mDrawObjectCount; i++)
	{
		mShader->SetWorldMatrix(mWorldTransform);

		Resource::GLTextureResource glTexRes = mImagesResource->GetTextureByID(mObjects[i].GetTextureID(0));
		mShader->SetTexture();
		glBindTexture(glTexRes.texture_target, glTexRes.texture);

		glDrawElements(GL_TRIANGLES, mObjects[i].GetIndexCount(), mIndexFormat, (const void *)(mObjects[i].GetIndexOffset()));//GL_TRIANGLES GL_LINES GL_UNSIGNED_SHORT 0x1403
	}
	//GLenum err = glGetError();
	///////////////////////////////////////////////////////////////////////////////
	mShader->ResetProgram();
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
}