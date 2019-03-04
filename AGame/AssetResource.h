#include "ResourceBase.h"
#include <string>

#pragma once
namespace Resource
{
	class AssetResource : public ResourceBase
	{
	public:
		AssetResource(JNIEnv *env, jobject rmng);
		~AssetResource();

		virtual bool GetResourceFromName(const char *resouce_name, const char **resource, uint64_t &lenght);
	};
}

