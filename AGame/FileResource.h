#include "ResourceBase.h"

#pragma once
namespace Resource
{
	class FileResource : public ResourceBase
	{
	public:
		FileResource(JNIEnv *env, jobject rmng);
		~FileResource();

		virtual bool GetResourceFromName(const char *resouce_name, const char **resource, uint64_t &lenght);
	};
}

