#include "DrawFullScreenQuad.h"


DrawFullScreen::DrawFullScreenQuad::DrawFullScreenQuad(Resource::ResourceBase *resourceLoad, GLuint mSourceTextureID, FullScreenBuffer::FullScreenQuadBuffer *mFullScreenBuffer) : mSourceTextureID(mSourceTextureID)
{
	mShaderDrawFullScreenQuad = new Shader::ShaderDrawFullScreenQuad(resourceLoad);
	vbBuffer = mFullScreenBuffer->GetArrayBuffer();
	ibBuffer = mFullScreenBuffer->GetElementArrayBuffer();
}

DrawFullScreen::DrawFullScreenQuad::~DrawFullScreenQuad()
{
	delete mShaderDrawFullScreenQuad;
}

void DrawFullScreen::DrawFullScreenQuad::InitAttrib(void)
{
	if (!mShaderDrawFullScreenQuad)
		throw std::runtime_error("Program is not!!!");

	glUseProgram(mShaderDrawFullScreenQuad->GetProgram());

	GLint sAttribLocationTex = mShaderDrawFullScreenQuad->GetTexCoordAttrib();

	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);
	int32_t stride = sizeof(glm::vec2);
	int32_t offset = 0;

	for (register uint32_t i = 0; i < 8; i++) glDisableVertexAttribArray(i);

	if (sAttribLocationTex != (-1))
	{
		glVertexAttribPointer(sAttribLocationTex, 2, GL_FLOAT, GL_FALSE, stride, (void *)(offset));
		glEnableVertexAttribArray(sAttribLocationTex);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mShaderDrawFullScreenQuad->BindTextureToSlot();

	glUseProgram(0);
	mShaderDrawFullScreenQuad->ResetProgram();
}

void DrawFullScreen::DrawFullScreenQuad::ResetSourceTexture(GLuint mSourceTextureID)
{
	this->mSourceTextureID = mSourceTextureID;
}

void DrawFullScreen::DrawFullScreenQuad::Draw(void)
{
	///////////////////////////////////////////////////////////////////////////////
	InitAttrib();
	///////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShaderDrawFullScreenQuad->GetProgram());

	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);
	///////////////////////////////////////////////////////////////////////////////
	mShaderDrawFullScreenQuad->SetSourceTexture();
	glBindTexture(GL_TEXTURE_2D, mSourceTextureID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);//GL_TRIANGLES GL_LINES GL_UNSIGNED_SHORT 0x1403
	//GLenum err = glGetError();
	///////////////////////////////////////////////////////////////////////////////
	mShaderDrawFullScreenQuad->ResetProgram();
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	///////////////////////////////////////////////////////////////////////////////
}
