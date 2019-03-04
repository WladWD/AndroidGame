#include "DrawBlur.h"



DrawFullScreen::DrawBlur::DrawBlur(Resource::ResourceBase *resourceLoad, GLuint mSourceTextureID, FullScreenBuffer::FullScreenQuadBuffer *mFullScreenBuffer) : mSourceTextureID(mSourceTextureID)
{
	mShaderBlur = new Shader::ShaderBlur(resourceLoad);

	vbBuffer = mFullScreenBuffer->GetArrayBuffer();
	ibBuffer = mFullScreenBuffer->GetElementArrayBuffer();
}

DrawFullScreen::DrawBlur::~DrawBlur()
{
	delete mShaderBlur;
}

void DrawFullScreen::DrawBlur::InitAttrib(void)
{
	if (!mShaderBlur)
		throw std::runtime_error("Program is not!!!");

	glUseProgram(mShaderBlur->GetProgram());

	//GLint sAttribLocationPosition = mShaderBlur->GetPositionAttrib();
	GLint sAttribLocationTex = mShaderBlur->GetTexCoordAttrib();

	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);
	int32_t stride = sizeof(glm::vec2);//Mesh::VTMesh);
	int32_t offset = 0;

	for (register uint32_t i = 0; i < 8; i++) glDisableVertexAttribArray(i);

	/*if (sAttribLocationPosition != (-1))
	{
		glVertexAttribPointer(sAttribLocationPosition, 3, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
		glEnableVertexAttribArray(sAttribLocationPosition);
	}

	offset += sizeof(glm::vec3);*/
	if (sAttribLocationTex != (-1))
	{
		glVertexAttribPointer(sAttribLocationTex, 2, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
		glEnableVertexAttribArray(sAttribLocationTex);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mShaderBlur->BindTextureToSlot();

	glUseProgram(0);
	mShaderBlur->ResetProgram();
}

void DrawFullScreen::DrawBlur::ResetSourceTexture(GLuint mSourceTextureID)
{
	this->mSourceTextureID = mSourceTextureID;
}

void DrawFullScreen::DrawBlur::Draw(glm::vec4 mParam)
{
	///////////////////////////////////////////////////////////////////////////////
	InitAttrib();
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShaderBlur->GetProgram());

	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);
	///////////////////////////////////////////////////////////////////////////////
	mShaderBlur->SetStepData(mParam);

	mShaderBlur->SetSourceTexture();
	glBindTexture(GL_TEXTURE_2D, mSourceTextureID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);//GL_TRIANGLES GL_LINES GL_UNSIGNED_SHORT 0x1403
	//GLenum err = glGetError();
	///////////////////////////////////////////////////////////////////////////////
	mShaderBlur->ResetProgram();
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	///////////////////////////////////////////////////////////////////////////////
}
