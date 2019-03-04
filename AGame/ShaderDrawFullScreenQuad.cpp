#include "ShaderDrawFullScreenQuad.h"



Shader::ShaderDrawFullScreenQuad::ShaderDrawFullScreenQuad(Resource::ResourceBase *resourceLoad) : ShaderBase(1)
{
	const uint32_t shader_count = 2;
	GLuint compile_shader[shader_count];

	const char *sShaders[shader_count] =
	{
		"resource\\shaders\\\fullscreenquad\\vertex.glsl",
		"resource\\shaders\\\fullscreenquad\\fragment.glsl"
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

Shader::ShaderDrawFullScreenQuad::~ShaderDrawFullScreenQuad() { }

void Shader::ShaderDrawFullScreenQuad::InitVariable(GLuint program)
{
	correct_programm

	mTexture[program] = glGetUniformLocation(programs[program], to_shader_name(mTexture));
}

GLint Shader::ShaderDrawFullScreenQuad::GetProgram(void)
{
	program_mid = 0;
	return programs[0];
}

void Shader::ShaderDrawFullScreenQuad::SetSourceTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + mTexSlot);
}

GLint Shader::ShaderDrawFullScreenQuad::GetTexCoordAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gTexCoord");
}

void Shader::ShaderDrawFullScreenQuad::BindTextureToSlot(void)
{
	correct_programm
		mcheck(mTexture) glUniform1i(mTexture[program_mid], mTexSlot);
}