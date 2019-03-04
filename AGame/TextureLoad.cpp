#include "TextureLoad.h"


Resource::TextureLoad::TextureLoad(MapResource *mapResource, Resource::ResourceBase *resourceLoad) : mapResource(mapResource), Load::LoadImageBase(resourceLoad)
{
}

Resource::TextureLoad::~TextureLoad()
{
}

uint32_t Resource::TextureLoad::LoadFromResource(const char *ResourceName)
{
	uint32_t idResource = mapResource->MapFindResource(ResourceName);
	if (idResource)
	{
		mapResource->AddReference(idResource);
		return idResource;
	}
	else 
	{
		Resource::GLTextureResource textureData = LoadFromResourceImage(ResourceName);
		idResource = mapResource->AppendResource(textureData.texture, textureData.texture_target, ResourceName, false);
		return idResource;
	}
}

Resource::GLTextureResource Resource::TextureLoad::LoadFromResourceImage(const char *ResourceName)
{
	/*ofstream RIFOut(mRIFName.c_str(), ios::binary | ios::out);

	TextureStruct::MainTextureStruct mts;
	mts.target = GL_TEXTURE_2D;
	mts.externalFormat = internal_format;
	mts.internalFormat = format;
	mts.mipLevels = 1;
	mts.pixelType = type_pixel;

	RIFOut.write((const char *)(&mts), sizeof(TextureStruct::MainTextureStruct));
	for (int i = 0; i < mts.mipLevels; i++)
	{
		TextureStruct::Dim dim;
		dim.height = height;
		dim.width = width;
		RIFOut.write((const char *)(&dim), sizeof(TextureStruct::Dim));
	}

	for (int i = 0; i < mts.mipLevels; i++)
	{
		GLuint size;

		size = height * width * BPP >> 3;

		RIFOut.write((const char *)(&size), sizeof(GLuint));
	}
	RIFOut.write((const char *)(data_pointer), height * width * BPP >> 3);

	FreeImage_Unload(fib);
	RIFOut.close();*/

	const char *cpRes;
	char *Resource;
	uint64_t length;
	resourceLoad->GetResourceFromName(ResourceName, &cpRes, length);

	Resource = const_cast<char *>(cpRes);

	MeshLoad::MainTextureStruct *mts = reinterpret_cast<MeshLoad::MainTextureStruct *>(Resource);
	MeshLoad::Dim *mDim = reinterpret_cast<MeshLoad::Dim *>(Resource + sizeof(MeshLoad::MainTextureStruct));
	GLuint *mTexSize = reinterpret_cast<GLuint *>(Resource + sizeof(MeshLoad::MainTextureStruct) + sizeof(MeshLoad::Dim));
	uint8_t *pixels = reinterpret_cast<uint8_t *>(Resource + sizeof(MeshLoad::MainTextureStruct) + sizeof(MeshLoad::Dim) + sizeof(GLuint));

	Resource::GLTextureResource glTexRes;
	glTexRes.texture_target = mts->target;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &glTexRes.texture);
	glBindTexture(glTexRes.texture_target, glTexRes.texture);// mts->externalFormat GL_BGR
	glTexImage2D(glTexRes.texture_target, 0, mts->internalFormat, mDim->width, mDim->height, 0, mts->externalFormat, mts->pixelType, pixels);

	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT);// GL_MIRRORED_REPEAT GL_REPEAT
	glTexParameteri(glTexRes.texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(glTexRes.texture_target);

	glBindTexture(glTexRes.texture_target, 0);

	delete[] Resource;

	return glTexRes;
}