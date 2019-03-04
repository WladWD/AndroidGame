#include "MHeder.h"

#define MMAX_LENGTH 260

#pragma once
namespace Resource
{
	struct GLTextureResource
	{
		GLuint texture;
		GLenum texture_target;
	};

	struct ResourceName
	{
		char resource_name[MMAX_LENGTH];
	};
}
