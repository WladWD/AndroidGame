#include "ShaderCollectDefault.h"


Shader::ShaderCollectDefault::ShaderCollectDefault(Resource::ResourceBase *resourceLoad) : ShaderCollectBase(1)
{
	const uint32_t shader_count = 2;
	GLuint compile_shader[shader_count];

	const char *sShaders[shader_count] =
	{
		"resource\\shaders\\collect\\vertex.glsl",
		"resource\\shaders\\collect\\fragment.glsl"
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


	mTexSlot = 0;

	MInitShaderVariable();

	program_mid = -1;
}

Shader::ShaderCollectDefault::~ShaderCollectDefault() { }

void Shader::ShaderCollectDefault::InitVariable(GLuint program)
{
	correct_programm

		mProjView[program] = glGetUniformLocation(programs[program], to_shader_name(mProjView));
	mWorld[program] = glGetUniformLocation(programs[program], to_shader_name(mWorld));
	gFog[program] = glGetUniformLocation(programs[program], to_shader_name(gFog));
	gFogColor[program] = glGetUniformLocation(programs[program], to_shader_name(gFogColor));
	mDiffuse[program] = glGetUniformLocation(programs[program], to_shader_name(mDiffuse));
}

GLint Shader::ShaderCollectDefault::GetProgram(void)
{
	program_mid = 0;
	return programs[0];
}

void Shader::ShaderCollectDefault::SetProjViewMatrix(glm::mat4 matrix)
{
	correct_programm

		mcheck(mProjView) glUniformMatrix4fv(mProjView[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderCollectDefault::SetWorldMatrix(glm::mat4 matrix)
{
	correct_programm

		mcheck(mWorld) glUniformMatrix4fv(mWorld[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderCollectDefault::SetFog(glm::vec2 fog)
{
	correct_programm
		mcheck(gFog) glUniform2fv(gFog[program_mid], 1, glm::value_ptr(fog));
}

void Shader::ShaderCollectDefault::SetTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + mTexSlot);
}

void Shader::ShaderCollectDefault::SetFogColor(const float *color)
{
	correct_programm
		mcheck(gFogColor) glUniform4fv(gFogColor[program_mid], 1, color);
}

GLint Shader::ShaderCollectDefault::GetPositionAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldPos");
}

GLint Shader::ShaderCollectDefault::GetTexCoordAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gTexCoord");
}

void Shader::ShaderCollectDefault::BindTextureToSlot(void)
{
	correct_programm

		mcheck(mDiffuse) glUniform1i(mDiffuse[program_mid], mTexSlot);
}
