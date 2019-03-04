#include "AssetResource.h"



Resource::AssetResource::AssetResource(JNIEnv *env, jobject rmng) : ResourceBase(env, rmng)
{
}

Resource::AssetResource::~AssetResource()
{
}

bool Resource::AssetResource::GetResourceFromName(const char *resouce_name, const char **resource, uint64_t &lenght)
{
#if !(defined(_WIN64) | defined(_WIN32))
	
	bool res = true;

	std::string mName = resouce_name;
	const char mBegName[] = "resource";
	mName.erase(mName.begin(), mName.begin() + sizeof(mBegName));

	for (register uint32_t i = 0; i < mName.length(); i++)
		mName[i] = mName[i] == '\\' ? '.' : mName[i];

	AAssetManager *pAssetManager = AAssetManager_fromJava(env, rmng);
	AAsset  *file = AAssetManager_open(pAssetManager, mName.c_str(), AASSET_MODE_UNKNOWN);

	lenght = AAsset_getLength(file);

	*resource = new char[lenght];

	AAsset_read(file, const_cast<char *>(*resource), lenght);

	AAsset_close(file);

	mName.clear();
	mName.shrink_to_fit();

	return res;

#else
	throw L"Not defined method";
	return false;
#endif
	
}
