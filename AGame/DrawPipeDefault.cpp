#include "DrawPipeDefault.h"

GameEngine::DrawPipeDefault::DrawPipeDefault(Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource, Camera::MCamera *cCamera,
	float fOffset, float fRadius, uint32_t V_Count, uint32_t U_Count,
	float fFogStart, float fFogRadius, const float *fFogColor) : DrawPipeBase(cCamera, fOffset, fRadius, V_Count, U_Count, fFogStart, fFogRadius, fFogColor),
	mPipeTextureName("resource\\textures\\pipe\\1x.rif")
{

	glTexRes = mMapResource->GetResourceByID(textureLoad->LoadFromResource(mPipeTextureName));// "resource\\textures\\pipe\\1.rif"));
	mShaderPipe = new Shader::ShaderPipeDefault(resourceLoad);

	//InitAttrib();
}

GameEngine::DrawPipeDefault::~DrawPipeDefault()
{
	delete mShaderPipe;
}

void GameEngine::DrawPipeDefault::ReleaseResource(void)
{
	DeleteResources();
	delete mShaderPipe;
	mShaderPipe = 0;
}

void GameEngine::DrawPipeDefault::ReCreateResource(Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource)
{
	CreateResources();

	glTexRes = mMapResource->GetResourceByID(textureLoad->LoadFromResource(mPipeTextureName)); //("resource\\textures\\pipe\\1.rif"));
	mShaderPipe = new Shader::ShaderPipeDefault(resourceLoad);

	//InitAttrib();
}

void GameEngine::DrawPipeDefault::InitAttrib(void)
{
	if(!mShaderPipe)
		throw std::runtime_error("Program is not!!!");

	glUseProgram(mShaderPipe->GetProgram());

	GLint sAttribLocationPosition = mShaderPipe->GetPositionAttrib();
	GLint sAttribLocationTex = mShaderPipe->GetTexCoordAttrib();

	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);
	int32_t stride = sizeof(Mesh::VTMesh);
	int32_t offset = 0;

	for (register uint32_t i = 0; i < 8; i++) glDisableVertexAttribArray(i);

	if (sAttribLocationTex != (-1)) 
	{
		glVertexAttribPointer(sAttribLocationPosition, 3, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
		glEnableVertexAttribArray(sAttribLocationPosition);
	}

	offset += sizeof(glm::vec3);
	if (sAttribLocationTex != (-1))
	{
		glVertexAttribPointer(sAttribLocationTex, 2, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
		glEnableVertexAttribArray(sAttribLocationTex);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mShaderPipe->BindTextureToSlot();

	glUseProgram(0);
	mShaderPipe->ResetProgram();
}

void GameEngine::DrawPipeDefault::Draw(const glm::mat4 *mWorld)
{
	InitAttrib();
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShaderPipe->GetProgram());

	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);

	mShaderPipe->SetProjViewMatrix(cCamera->GetProjViewMatrix());
	mShaderPipe->SetFogColor(fFogColor);
	mShaderPipe->SetFog(glm::vec2(fFogStart, fFogRadius));

	for (register uint32_t i = 0; i < 2; i++)
	{
		mShaderPipe->SetWorldMatrix(mWorld[i]);

		mShaderPipe->SetPipeTexture();
		glBindTexture(glTexRes.texture_target, glTexRes.texture);

		glDrawElements(GL_TRIANGLES, uCountCylinder, GL_UNSIGNED_SHORT, 0);//GL_TRIANGLES GL_LINES
	}

	//GLenum err = glGetError();
	///////////////////////////////////////////////////////////////////////////////
	mShaderPipe->ResetProgram();
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}