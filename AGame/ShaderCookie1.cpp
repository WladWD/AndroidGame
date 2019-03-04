#include "ShaderCookie1.h"


Shader::ShaderCookie1::ShaderCookie1(Resource::ResourceBase *resourceLoad) : ShaderCookieBase(1)
{
	const uint32_t shader_count = 2;
	GLuint compile_shader[shader_count];

	const char *sShaders[shader_count] =
	{
		"resource\\shaders\\cookie\\1\\vertex1.glsl",
		"resource\\shaders\\cookie\\1\\fragment1.glsl"
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

Shader::ShaderCookie1::~ShaderCookie1() { }

void Shader::ShaderCookie1::InitVariable(GLuint program)
{
	correct_programm

	mProjView[program] = glGetUniformLocation(programs[program], to_shader_name(mProjView));
	mWorld[program] = glGetUniformLocation(programs[program], to_shader_name(mWorld));
	mTexture[program] = glGetUniformLocation(programs[program], to_shader_name(mTexture));
}

GLint Shader::ShaderCookie1::GetProgram(void)
{
	program_mid = 0;
	return programs[0];
}

void Shader::ShaderCookie1::SetProjViewMatrix(glm::mat4 matrix)
{
	correct_programm

	mcheck(mProjView) glUniformMatrix4fv(mProjView[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderCookie1::SetWorldMatrix(glm::mat4 matrix)
{
	correct_programm

		mcheck(mWorld) glUniformMatrix4fv(mWorld[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderCookie1::SetPipeTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + mPipeTexSlot);
}

GLint Shader::ShaderCookie1::GetPositionAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldPos");
}

/*GLint Shader::ShaderCookie1::GetNormalAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldNorm");
}*/

GLint Shader::ShaderCookie1::GetTexCoordAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gTexCoord");
}

void Shader::ShaderCookie1::BindTextureToSlot(void)
{
	correct_programm

		mcheck(mTexture) glUniform1i(mTexture[program_mid], mPipeTexSlot);
}