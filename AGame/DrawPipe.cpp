#include "DrawPipe.h"


GameEngine::DrawPipe::DrawPipe(Resource::ResourceBase *resourceLoad, Camera::MCamera *cCamera, float fOffset, float fRadius,
	float fFogStart, float fFogRadius, const float *fFogColor, Resource::GLTextureResource glTexRes) : 
	cCamera(cCamera), fFogStart(fFogStart), fFogRadius(fFogRadius), fFogColor(fFogColor), glTexRes(glTexRes)
{
	ShapeGenerator::MShapeGenerator::GenCylinder(16, 8, -fOffset, fRadius, fOffset, vbBuffer, ibBuffer, uCountCylinder);
	sShaderPipe = new Shader::ShaderPipe(resourceLoad);

	InitAttrib();
}

GameEngine::DrawPipe::~DrawPipe()
{
	glDeleteBuffers(1, &vbBuffer);
	glDeleteBuffers(1, &ibBuffer);

	delete sShaderPipe;
}

void GameEngine::DrawPipe::InitAttrib(void)
{
	glUseProgram(sShaderPipe->GetProgram());

	GLint sAttribLocationPosition = sShaderPipe->GetPositionAttrib();
	GLint sAttribLocationNormal = sShaderPipe->GetNormalAttrib();
	GLint sAttribLocationTex = sShaderPipe->GetTexCoordAttrib();

	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);
	int32_t stride = sizeof(Mesh::VNTMesh);
	int32_t offset = 0;

	for (register uint32_t i = 0; i < 8; i++) glDisableVertexAttribArray(i);

	glVertexAttribPointer(sAttribLocationPosition, 3, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
	glEnableVertexAttribArray(sAttribLocationPosition);

	offset += sizeof(glm::vec3);
	glVertexAttribPointer(sAttribLocationNormal, 3, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
	glEnableVertexAttribArray(sAttribLocationNormal);
	
	offset += sizeof(glm::vec3);
	glVertexAttribPointer(sAttribLocationTex, 2, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
	glEnableVertexAttribArray(sAttribLocationTex);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	sShaderPipe->BindTextureToSlot();

	glUseProgram(0);
	sShaderPipe->ResetProgram();
}

void GameEngine::DrawPipe::Draw(const glm::mat4 *mWorld, float fDeltaTime, float fGlobalTime)
{
	InitAttrib();
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(sShaderPipe->GetProgram());

	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);

	sShaderPipe->SetProjViewMatrix(cCamera->GetProjViewMatrix());
	sShaderPipe->SetFogColor(fFogColor);
	sShaderPipe->SetFog(glm::vec2(fFogStart, fFogRadius));


	for (register uint32_t i = 0; i < 2; i++)
	{
		sShaderPipe->SetWorldMatrix(mWorld[i]);
		sShaderPipe->SetWorldInvTrans(glm::transpose(glm::inverse(mWorld[i])));

		sShaderPipe->SetPipeTexture();
		glBindTexture(glTexRes.texture_target, glTexRes.texture);

		glDrawElements(GL_TRIANGLES, uCountCylinder, GL_UNSIGNED_SHORT, 0);//GL_TRIANGLES GL_LINES
	}
	
	//GLenum err = glGetError();
	///////////////////////////////////////////////////////////////////////////////
	sShaderPipe->ResetProgram();
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
