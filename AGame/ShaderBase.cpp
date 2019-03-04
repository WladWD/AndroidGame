#include "ShaderBase.h"

Shader::ShaderBase::ShaderBase(uint32_t mProgramCount) : program_count(mProgramCount)
{
	programs = new GLuint[mProgramCount];
}

Shader::ShaderBase::~ShaderBase()
{
	for (uint32_t i = 0; i < program_count; i++)glDeleteProgram(programs[i]);
	delete[] programs;
}

bool Shader::ShaderBase::BuildShader(Resource::ResourceBase *resourceLoad, const char **mShaderNames, GLenum *shader_types, uint32_t shader_count, GLuint *compiled_shader)
{
	bool res = true;

	for (register uint32_t i = 0; i < shader_count; i++)
	{
		res = res && ReadShaderFrom(resourceLoad, shader_types[i], compiled_shader[i], mShaderNames[i]);
	}

	return res;
}

bool Shader::ShaderBase::LinkProgram(GLuint vs, GLuint ps, uint32_t mProgramIndex)
{
	programs[mProgramIndex] = glCreateProgram();

	if (!programs[mProgramIndex])
		return false;

	glAttachShader(programs[mProgramIndex], vs);
	glAttachShader(programs[mProgramIndex], ps);

	glLinkProgram(programs[mProgramIndex]);

	GLint bLinkStatus;
	glGetProgramiv(programs[mProgramIndex], GL_LINK_STATUS, &bLinkStatus);
	if (bLinkStatus != GL_TRUE) 
	{
		GLint mInfoLogLength;
		glGetProgramiv(programs[mProgramIndex], GL_INFO_LOG_LENGTH, &mInfoLogLength);

		if (mInfoLogLength > 0) 
		{
			GLchar *eLogMessage = new GLchar[mInfoLogLength];
			glGetProgramInfoLog(programs[mProgramIndex], mInfoLogLength, NULL, eLogMessage);

			throw std::runtime_error(eLogMessage);

			delete[] eLogMessage;
		}

		programs[mProgramIndex] = -1;
		return false;
	}
	return true;
}

void Shader::ShaderBase::ResetProgram(void)
{
	program_mid = -1;
}

void Shader::ShaderBase::MInitShaderVariable(void)
{
	for (register uint32_t i = 0; i < program_count; i++)
	{
		program_mid = i;
		InitVariable(i);
	}
	program_mid = -1;
}

bool Shader::ShaderBase::ReadShaderFrom(Resource::ResourceBase *resourceLoad, GLenum mShaderType, GLuint &mShader, const char *ResourceName)
{
	mShader = glCreateShader(mShaderType);

	if (!mShader) return false;

	const char *shader;
	uint64_t mShaderLength;

	bool res = resourceLoad->GetResourceFromName(ResourceName, &shader, mShaderLength);
	if (!res)
		return false;

	const int count = 1;
	const char *shader_code[count] = { shader };
	int32_t code_lengths[count] = { (int32_t)mShaderLength };

	glShaderSource(mShader, count, shader_code, code_lengths);
	glCompileShader(mShader);

	delete[] shader;

	GLint status;
	glGetShaderiv(mShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		GLint sInfoLog;
		glGetShaderiv(mShader, GL_INFO_LOG_LENGTH, &sInfoLog);
		if (sInfoLog > 0)
		{
			GLchar *eMessage = new GLchar[sInfoLog];
			glGetShaderInfoLog(mShader, sInfoLog, NULL, eMessage);

			throw std::runtime_error(eMessage);

			delete[] eMessage;
		}

		mShader = -1;
		return false;
	}

	return res;
}

