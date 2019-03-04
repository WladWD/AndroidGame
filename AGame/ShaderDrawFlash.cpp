#include "ShaderDrawFlash.h"


Shader::ShaderDrawFlash::ShaderDrawFlash(Resource::ResourceBase *resourceLoad) : ShaderBase(1)
{
	const uint32_t shader_count = 2;
	GLuint compile_shader[shader_count];

	const char *sShaders[shader_count] =
	{
		"resource\\shaders\\collect\\flash\\vertex.glsl",
		"resource\\shaders\\collect\\flash\\fragment.glsl"
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

Shader::ShaderDrawFlash::~ShaderDrawFlash() { }

void Shader::ShaderDrawFlash::InitVariable(GLuint program)
{
	correct_programm

	mProjView[program] = glGetUniformLocation(programs[program], to_shader_name(mProjView));
	mWorld[program] = glGetUniformLocation(programs[program], to_shader_name(mWorld));
	mDiffuse[program] = glGetUniformLocation(programs[program], to_shader_name(mDiffuse));
	mCamPosition[program] = glGetUniformLocation(programs[program], to_shader_name(mCamPosition));
	mUpVec[program] = glGetUniformLocation(programs[program], to_shader_name(mUpVec));
	mScaleAlpha[program] = glGetUniformLocation(programs[program], to_shader_name(mScaleAlpha));
}

GLint Shader::ShaderDrawFlash::GetProgram(void)
{
	program_mid = 0;
	return programs[0];
}

void Shader::ShaderDrawFlash::SetFlashTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + mTexSlot);
}

GLint Shader::ShaderDrawFlash::GetPositionAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gWorldPos");
}

GLint Shader::ShaderDrawFlash::GetOffsetTexAttrib(void)
{
	return glGetAttribLocation(programs[program_mid], "gOffset_Tex");
}

void Shader::ShaderDrawFlash::SetProjViewMatrix(glm::mat4 matrix)
{
	correct_programm
		glUniformMatrix4fv(mProjView[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderDrawFlash::SetWorldMatrix(glm::mat4 matrix)
{
	correct_programm
		glUniformMatrix4fv(mWorld[program_mid], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::ShaderDrawFlash::SetCamPos(glm::vec4 mCamPos)
{
	correct_programm
		glUniform4fv(this->mCamPosition[program_mid], 1, glm::value_ptr(mCamPos));
}

void Shader::ShaderDrawFlash::SetScaleAlpha(glm::vec2 mScaleAlpha)
{
	correct_programm
		glUniform2fv(this->mScaleAlpha[program_mid], 1, glm::value_ptr(mScaleAlpha));
}

void Shader::ShaderDrawFlash::SetUpVector(glm::vec4 mUp)
{
	correct_programm
		glUniform4fv(this->mUpVec[program_mid], 1, glm::value_ptr(mUp));
}

void Shader::ShaderDrawFlash::BindTextureToSlot(void)
{
	correct_programm
		mcheck(mDiffuse) glUniform1i(mDiffuse[program_mid], mTexSlot);
}