#include "ShaderBase.h"

#pragma once
namespace Shader
{
#define DPROGRAM_COUNT 1
	class ShaderDrawFullScreenQuad : public ShaderBase
	{
		////////////////////////////////////////////////////////////////////////////////////////////////
		GLint mTexture[DPROGRAM_COUNT];
		////////////////////////////////////////////////////////////////////////////////////////////////
		uint32_t mTexSlot;
		////////////////////////////////////////////////////////////////////////////////////////////////
		void InitVariable(GLuint program);
		////////////////////////////////////////////////////////////////////////////////////////////////
	public:
		ShaderDrawFullScreenQuad(Resource::ResourceBase *resourceLoad);
		~ShaderDrawFullScreenQuad();
		////////////////////////////////////////////////////////////////////////////////////////////////
		GLint GetProgram(void);
		////////////////////////////////////////////////////////////////////////////////////////////////
		GLint GetTexCoordAttrib(void);
		////////////////////////////////////////////////////////////////////////////////////////////////
		void SetSourceTexture(void);
		////////////////////////////////////////////////////////////////////////////////////////////////
		void BindTextureToSlot(void);
	};
#undef DPROGRAM_COUNT
}
