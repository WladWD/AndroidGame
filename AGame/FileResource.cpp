#include "FileResource.h"



Resource::FileResource::FileResource(JNIEnv *env, jobject rmng) : ResourceBase(env, rmng)
{
}

Resource::FileResource::~FileResource()
{
}

bool Resource::FileResource::GetResourceFromName(const char *resouce_name, const char **resource, uint64_t &lenght)
{
#if (defined(_WIN64) | defined(_WIN32))
	bool res = true;

	HANDLE file_map = CreateFileA(resouce_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE file_maping = CreateFileMapping(file_map, NULL, PAGE_READONLY, 0, 0, NULL);
	DWORD hw, lw;
	lw = GetFileSize(file_map, &hw);
	lenght = hw << 32;
	lenght += lw;
	CloseHandle(file_map);

	*resource = new const char[lenght];

	const char * resource_tmp = (const char *)MapViewOfFile(file_maping, FILE_MAP_READ, 0, 0, 0);
	memcpy(const_cast<char *>(*resource), resource_tmp, lenght);
	
	CloseHandle(file_maping);

	return res;
#else
	throw L"Not defined method";
	return false;
#endif
}