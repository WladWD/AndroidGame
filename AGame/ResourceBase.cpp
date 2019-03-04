#include "ResourceBase.h"



Resource::ResourceBase::ResourceBase(JNIEnv *env, jobject rmng) : env(env), rmng(rmng)
{
}

Resource::ResourceBase::~ResourceBase()
{
}
