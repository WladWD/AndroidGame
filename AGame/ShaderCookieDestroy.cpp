#include "ShaderCookieDestroy.h"


Shader::ShaderCookieDestroy::ShaderCookieDestroy(Resource::ResourceBase *resourceLoad) : ShaderCookieDestroyBase(1)
{
	const uint32_t shader_count = 2;
	GLuint compile_shader[shader_count];

	const char *sShaders[shader_count] =
	{
		"resource\\shaders\\cookie\\1\\vertex_destroy.glsl",
		"resource\\shaders\\cookie\\1\\fragment_destroy.glsl"
	};

	GLenum sTypes[shader_count] =
	{
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	};

	if (!BuildShader(resourceLoad, sShaders, sTypes, shader_count, compile_shader))
		throw std::runtime_error("Shader is not COMPILE !!!");;


	if (!LinkProgram(compile_shader[0], compile_shader[1], 0))
		throw std::runtime_error("Program is NOT LINKED !!!");

	for (register uint32_t i = 0; i < shader_count; i++) glDeleteShader(compile_shader[i]);


	mPipeTexSlot = 0;

	MInitShaderVariable();

	program_mid = -1;
}

Shader::ShaderCookieDestroy::~ShaderCookieDestroy() { }

void Shader::ShaderCookieDestroy::InitVariable(GLuint program)
{
	correct_programm

	mProjView[program] = glGetUniformLocation(programs[program], to_shader_name(mProjView));
	mWorld[program] = glGetUniformLocation(programs[program], to_shader_name(mWorld));
	mTexture[program] = glGetUniformLocation(programs[program], to_shader_name(mTexture));
	
	mMoving[program] = glGetUniformLocation(programs[program], to_shader_name(mMoving));
	mGlobalData[program] = glGetUniformLocation(programs[program], to_shader_name(mGlobalData));
	mDrawIndex[program] = glGetUniformLocation(programs[program], to_shader_name(mDrawIndex));
}

GLint Shader::ShaderCookieDestroy::GetProgram(void)
{
	program_mid = 0;
	return programs[0];
}

void Shader::ShaderCookieDestroy::SetProjViewMatrix(glm::mat4 matrix)
{
	correct_programm

		mcheck(mProjView) glUniformMatrix4fv(mProjView[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderCookieDestroy::SetWorldMatrix(glm::mat4 matrix)
{
	correct_programm

		mcheck(mWorld) glUniformMatrix4fv(mWorld[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderCookieDestroy::SetMovePices(glm::vec4 mVector[COOKIE_PICES_COUNT], uint32_t count)
{
	correct_programm

		mcheck(mMoving) glUniform4fv(mMoving[program_mid], count, glm::value_ptr(mVector[0]));
}

void Shader::ShaderCookieDestroy::SetGlobalData(glm::vec2 mData) 
{
	correct_programm

		mcheck(mGlobalData) glUniform2fv(mGlobalData[program_mid], 1, glm::value_ptr(mData));
}

void Shader::ShaderCookieDestroy::SetDrawPiceID(int32_t mID) 
{
	correct_programm

		mcheck(mDrawIndex) glUniform1i(mDrawIndex[program_mid], mID);
}

void Shader::ShaderCookieDestroy::SetPipeTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + mPipeTexSlot);
}

GLint Shader::ShaderCookieDestroy::GetPositionAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldPos");
}

GLint Shader::ShaderCookieDestroy::GetTexCoordAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gTexCoord");
}

void Shader::ShaderCookieDestroy::BindTextureToSlot(void)
{
	correct_programm

		mcheck(mTexture) glUniform1i(mTexture[program_mid], mPipeTexSlot);
}