#include "ShaderPipe.h"


Shader::ShaderPipe::ShaderPipe(Resource::ResourceBase *resourceLoad) : ShaderBase(1)
{
	const uint32_t shader_count = 2;
	GLuint compile_shader[shader_count];

	const char *sShaders[shader_count] = 
	{
		"shaders\\pipe\\vertex.glsl",
		"shaders\\pipe\\fragment.glsl"
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

Shader::ShaderPipe::~ShaderPipe() { }

void Shader::ShaderPipe::InitVariable(GLuint program)
{
	correct_programm

	mProjView[program] = glGetUniformLocation(programs[program], to_shader_name(mProjView));
	mWorld[program] = glGetUniformLocation(programs[program], to_shader_name(mWorld));
	mWorldInvTrans[program] = glGetUniformLocation(programs[program], to_shader_name(mWorldInvTrans));
	gFog[program] = glGetUniformLocation(programs[program], to_shader_name(gFog));
	gFogColor[program] = glGetUniformLocation(programs[program], to_shader_name(gFogColor));
	mTexture[program] = glGetUniformLocation(programs[program], to_shader_name(mTexture));
}

GLint Shader::ShaderPipe::GetProgram(void) 
{
	program_mid = 0;
	return programs[0];
}

void Shader::ShaderPipe::SetProjViewMatrix(glm::mat4 matrix) 
{
	correct_programm

	mcheck(mProjView) glUniformMatrix4fv(mProjView[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderPipe::SetWorldMatrix(glm::mat4 matrix) 
{
	correct_programm

		mcheck(mWorld) glUniformMatrix4fv(mWorld[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderPipe::SetWorldInvTrans(glm::mat4 matrix) 
{
	correct_programm

		mcheck(mWorldInvTrans) glUniformMatrix4fv(mWorldInvTrans[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderPipe::SetFog(glm::vec2 fog)
{
	correct_programm

		mcheck(gFog) glUniform2fv(gFog[program_mid], 1, glm::value_ptr(fog));
}

void Shader::ShaderPipe::SetPipeTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + mPipeTexSlot);
}

void Shader::ShaderPipe::SetFogColor(const float *color)
{
	correct_programm

		mcheck(gFogColor) glUniform4fv(gFogColor[program_mid], 1, color);
}

GLint Shader::ShaderPipe::GetPositionAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldPos");
}

GLint Shader::ShaderPipe::GetNormalAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldNorm");
}

GLint Shader::ShaderPipe::GetTexCoordAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gTexCoord");
}

void Shader::ShaderPipe::BindTextureToSlot(void)
{
	correct_programm

	mcheck(mTexture) glUniform1i(mTexture[program_mid], mPipeTexSlot);
}