#include <stdint.h>
#include <glew.h>
#include <wglew.h>
#pragma once

namespace TextureStruct 
{
	struct Dim 
	{
		GLuint width;
		GLuint height;
	};

	struct MainTextureStruct 
	{
		GLenum target;
		GLuint mipLevels;
		GLenum internalFormat;
		GLenum externalFormat;
		GLenum pixelType;
		//Dim dimention[mipLevels];
		//GLuint textureSize[mipLevels];
		//pixels [mipLevels];
	};
}

