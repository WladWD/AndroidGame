#include "ShaderBlur.h"


Shader::ShaderBlur::ShaderBlur(Resource::ResourceBase *resourceLoad) : ShaderBase(1)
{
	const uint32_t shader_count = 2;
	GLuint compile_shader[shader_count];

	const char *sShaders[shader_count] =
	{
		"resource\\shaders\\end_game\\vertex.glsl",
		"resource\\shaders\\end_game\\fragment.glsl"
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

Shader::ShaderBlur::~ShaderBlur() { }

void Shader::ShaderBlur::InitVariable(GLuint program)
{
	correct_programm

	mStep[program] = glGetUniformLocation(programs[program], to_shader_name(mStep));
	mTexture[program] = glGetUniformLocation(programs[program], to_shader_name(mTexture));
}

GLint Shader::ShaderBlur::GetProgram(void)
{
	program_mid = 0;
	return programs[0];
}

void Shader::ShaderBlur::SetStepData(glm::vec4 mStepData)
{
	correct_programm
	mcheck(mStep) glUniform4fv(mStep[program_mid], 1, glm::value_ptr(mStepData));
}

void Shader::ShaderBlur::SetSourceTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + mTexSlot);
}

/*GLint Shader::ShaderBlur::GetPositionAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldPos");
}*/

GLint Shader::ShaderBlur::GetTexCoordAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gTexCoord");
}

void Shader::ShaderBlur::BindTextureToSlot(void)
{
	correct_programm
	mcheck(mTexture) glUniform1i(mTexture[program_mid], mTexSlot);
}