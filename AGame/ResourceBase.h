#include "MHeder.h"

#pragma once
namespace Resource
{
	class ResourceBase
	{
	protected:
		JNIEnv *env;
		jobject rmng;
	public:
		ResourceBase(JNIEnv *env, jobject rmng);
		virtual ~ResourceBase();

		virtual bool GetResourceFromName(const char *resouce_name, const char **resource, uint64_t &lenght) = 0;
	};
}

