#include "ShaderDrawText.h"


Shader::ShaderDrawText::ShaderDrawText(Resource::ResourceBase *resourceLoad) : ShaderBase(1)
{
	const uint32_t shader_count = 2;
	GLuint compile_shader[shader_count];

	const char *sShaders[shader_count] =
	{
		"resource\\shaders\\draw_score\\draw_text\\vertex.glsl",
		"resource\\shaders\\draw_score\\draw_text\\fragment.glsl"
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

Shader::ShaderDrawText::~ShaderDrawText() { }

void Shader::ShaderDrawText::InitVariable(GLuint program)
{
	correct_programm

	mPackOffsetScaleTex[program] = glGetUniformLocation(programs[program], to_shader_name(mPackOffsetScaleTex));
	mWorld[program] = glGetUniformLocation(programs[program], to_shader_name(mWorld));
	mDiffuse[program] = glGetUniformLocation(programs[program], to_shader_name(mDiffuse));
}

GLint Shader::ShaderDrawText::GetProgram(void)
{
	program_mid = 0;
	return programs[0];
}

void Shader::ShaderDrawText::SetTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + mTexSlot);
}

GLint Shader::ShaderDrawText::GetPositionAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldPos");
}

void Shader::ShaderDrawText::SetWorldMatrix(glm::mat4 matrix)
{
	correct_programm
		glUniformMatrix4fv(mWorld[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderDrawText::SetPackOffsetScale(glm::vec4 mPack)
{
	correct_programm
		glUniform4fv(this->mPackOffsetScaleTex[program_mid], 1, glm::value_ptr(mPack));
}

void Shader::ShaderDrawText::BindTextureToSlot(void)
{
	correct_programm
		mcheck(mDiffuse) glUniform1i(mDiffuse[program_mid], mTexSlot);
}