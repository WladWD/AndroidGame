#include "ShaderDrawBitmap.h"


Shader::ShaderDrawBitmap::ShaderDrawBitmap(Resource::ResourceBase *resourceLoad) : ShaderBase(1)
{
	const uint32_t shader_count = 2;
	GLuint compile_shader[shader_count];

	const char *sShaders[shader_count] =
	{
		"resource\\shaders\\draw_score\\draw_bitmap\\vertex.glsl",
		"resource\\shaders\\draw_score\\draw_bitmap\\fragment.glsl"
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

Shader::ShaderDrawBitmap::~ShaderDrawBitmap() { }

void Shader::ShaderDrawBitmap::InitVariable(GLuint program)
{
	correct_programm

	mWorld[program] = glGetUniformLocation(programs[program], to_shader_name(mWorld));
	mDiffuse[program] = glGetUniformLocation(programs[program], to_shader_name(mDiffuse));
}

GLint Shader::ShaderDrawBitmap::GetProgram(void)
{
	program_mid = 0;
	return programs[0];
}

void Shader::ShaderDrawBitmap::SetTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + mTexSlot);
}

GLint Shader::ShaderDrawBitmap::GetPositionAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldPos");
}

void Shader::ShaderDrawBitmap::SetWorldMatrix(glm::mat4 matrix)
{
	correct_programm
		glUniformMatrix4fv(mWorld[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderDrawBitmap::BindTextureToSlot(void)
{
	correct_programm
		mcheck(mDiffuse) glUniform1i(mDiffuse[program_mid], mTexSlot);
}