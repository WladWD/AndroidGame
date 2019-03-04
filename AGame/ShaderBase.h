#include "MHeder.h"
#include "FileResource.h"
#include "AssetResource.h"
#include "TextureLoad.h"

#pragma once
namespace Shader
{
#define to_shader_name(s) #s
#define correct_programm  if(program_mid == (-1)) throw std::runtime_error("Program is not bind!!!");//MessageBox(NULL, L"Program is not bind!!!", L"Error", MB_OK);
#define mcheck(p) if(p[program_mid] >= 0)

	class ShaderBase
	{
	protected:
		/////////////////////////////////////////////////////////////////////////////////
		GLuint *programs;
		int32_t program_mid;
		const uint32_t program_count;
		/////////////////////////////////////////////////////////////////////////////////
		bool BuildShader(Resource::ResourceBase *resourceLoad, const char **mShaderNames, GLenum *shader_types, uint32_t shader_count, GLuint *compiled_shader);
		bool LinkProgram(GLuint vs, GLuint ps, uint32_t mProgramIndex);
		/////////////////////////////////////////////////////////////////////////////////
		void MInitShaderVariable(void);
		virtual void InitVariable(GLuint program) = 0;
		/////////////////////////////////////////////////////////////////////////////////
		bool ReadShaderFrom(Resource::ResourceBase *resourceLoad, GLenum mShaderType, GLuint &mShader, const char *ResourceName);
	public:
		ShaderBase(uint32_t mProgramCount);
		virtual ~ShaderBase();
		/////////////////////////////////////////////////////////////////////////////////
		void ResetProgram(void);//set program to -1
	};
}

