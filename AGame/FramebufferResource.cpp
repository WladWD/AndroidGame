#include "FramebufferResource.h"


Framebuffer::FramebufferResource::FramebufferResource(uint32_t mDimX, uint32_t mDimY)
{
	InitFramebuffer(mDimX, mDimY);
}

Framebuffer::FramebufferResource::~FramebufferResource()
{
	glDeleteFramebuffers(1, &mFramebuffer);
	glDeleteTextures(1, &mFramebufferTexture);
	glDeleteRenderbuffers(1, &mRenderBufferDepth);
}

void Framebuffer::FramebufferResource::Resize(uint32_t mDimX, uint32_t mDimY)
{
	glDeleteTextures(1, &mFramebufferTexture);
	glDeleteRenderbuffers(1, &mRenderBufferDepth);
	glDeleteFramebuffers(1, &mFramebuffer);

	InitFramebuffer(mDimX, mDimY);
}

void Framebuffer::FramebufferResource::InitFramebuffer(uint32_t mDimX, uint32_t mDimY)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glGenTextures(1, &mFramebufferTexture);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, mFramebufferTexture);
#define GL_OES_rgb8_rgba8
#ifdef GL_OES_rgb8_rgba8
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mDimX, mDimY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
#else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mDimX, mDimY, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, NULL);
#endif
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//GL_REPEAT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glGenRenderbuffers(1, &mRenderBufferDepth);

	glBindRenderbuffer(GL_RENDERBUFFER, mRenderBufferDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, mDimX, mDimY);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glGenFramebuffers(1, &mFramebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mFramebufferTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderBufferDepth);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GLenum status;
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("Framebuffer is Not complete !!!");
	if(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT == status)
		throw std::runtime_error("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT !!!");
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Framebuffer::FramebufferResource::GetFramebufferTexture(void)
{
	return mFramebufferTexture;
}

void Framebuffer::FramebufferResource::SetFramebufferToDraw(void)
{
	/////////////////////////////////////////////////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
	/////////////////////////////////////////////////////////////////////////////
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/////////////////////////////////////////////////////////////////////////////
}

void Framebuffer::FramebufferResource::SetScreenFramebuffer(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	/////////////////////////////////////////////////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, mFramebufferTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	/////////////////////////////////////////////////////////////////////////////
}
