#include "MShapeGenerator.h"
#include "ShaderPipe.h"
#include "MCamera.h"

#pragma once
namespace GameEngine
{
	class DrawPipe
	{
		////////////////////////////////////////////////////////////////////////////////
		Resource::GLTextureResource glTexRes;
		////////////////////////////////////////////////////////////////////////////////
		const float *fFogColor;
		const float fFogStart, fFogRadius;
		////////////////////////////////////////////////////////////////////////////////
		Camera::MCamera *cCamera;
		////////////////////////////////////////////////////////////////////////////////
		Shader::ShaderPipe *sShaderPipe;
		////////////////////////////////////////////////////////////////////////////////
		GLuint vbBuffer, ibBuffer;
		uint32_t uCountCylinder;
		////////////////////////////////////////////////////////////////////////////////
		void InitAttrib(void);
	public:
		DrawPipe(Resource::ResourceBase *resourceLoad, Camera::MCamera *cCamera, float fOffset, float fRadius, float fFogStart, float fFogRadius, const float *fFogColor, Resource::GLTextureResource glTexRes);
		~DrawPipe();
		////////////////////////////////////////////////////////////////////////////////
		void Draw(const glm::mat4 *mWorld, float fDeltaTime, float fGlobalTime);
		////////////////////////////////////////////////////////////////////////////////
	};
}

