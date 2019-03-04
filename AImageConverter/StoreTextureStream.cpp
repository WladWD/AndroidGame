#include "StoreTextureStream.h"

using namespace std;


Resource::StoreTextureStream::StoreTextureStream(std::string mFileName) : mGlobalTextureID(0), mFileName(mFileName)
{
	data = new std::ofstream(mFileName.c_str(), ios::binary | ios::out);
	mMapTexture = new std::map<std::string, GLuint>();

	GLuint mImageCount = 0;
	data->write(reinterpret_cast<const char *>(&mImageCount), sizeof(GLuint));
}

Resource::StoreTextureStream::~StoreTextureStream()
{
	data->close();

	delete mMapTexture;
	delete data;
}

void Resource::StoreTextureStream::LoadMapFromFileFreeImage(string texture_name)
{
	cur_use_alpha = false;

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *fib(0);

	fif = FreeImage_GetFileType(texture_name.c_str());
	if (fif == FIF_UNKNOWN)
	{
		MessageBoxA(NULL, texture_name.c_str(), "Unknow file format", MB_OK);
		throw 1;
	}

	if (FreeImage_FIFSupportsReading(fif))fib = FreeImage_Load(fif, texture_name.c_str());

	if (!fib)
	{
		MessageBoxA(NULL, texture_name.c_str(), "Unknow file format", MB_OK);
		throw 1;
	}

	BYTE *data_pointer = FreeImage_GetBits(fib);
	uint32_t width = FreeImage_GetWidth(fib);
	uint32_t height = FreeImage_GetHeight(fib);
	uint32_t BPP = FreeImage_GetBPP(fib);

	if (!width || !height || !BPP)
	{
		MessageBox(NULL, L"Ошибка чтения файла", L"Unknow file format", MB_OK);
		throw 1;
	}

	cur_use_alpha = FreeImage_IsTransparent(fib);

	HRESULT hr;
	GLuint format;

	GLenum internal_format;
	GLenum type_pixel;
	type_pixel = GL_UNSIGNED_BYTE;

	switch (BPP)
	{
	case 32: {internal_format = GL_RGBA; format = GL_RGBA; }break;
	case 24: {internal_format = GL_RGB; format = GL_RGB; }break;//GL_RGB
		//case 16: {internal_format = GL_RG; format = GL_RG; }break;
	case 8: {internal_format = GL_ALPHA; format = GL_ALPHA; }break;
	default:
	{
		MessageBox(NULL, L"Ошибка чтения файла", L"Unknow file format", MB_OK);
		throw 1;
	} break;
	}


	TextureStruct::MainTextureStruct mts;
	mts.target = GL_TEXTURE_2D;
	mts.externalFormat = internal_format;
	mts.internalFormat = format;
	mts.mipLevels = 1;
	mts.pixelType = type_pixel;

	//RIFOut.write((const char *)(&mts), sizeof(TextureStruct::MainTextureStruct));

	data->write((const char *)(&mGlobalTextureID), sizeof(GLuint));

	data->write((const char *)(&mts), sizeof(TextureStruct::MainTextureStruct));
	for (int i = 0; i < mts.mipLevels; i++)
	{
		TextureStruct::Dim dim;
		dim.height = height;
		dim.width = width;
		//RIFOut.write((const char *)(&dim), sizeof(TextureStruct::Dim));
		data->write((const char *)(&dim), sizeof(TextureStruct::Dim));
	}

	for (int i = 0; i < mts.mipLevels; i++)
	{
		GLuint size;

		size = height * width * BPP >> 3;

		//RIFOut.write((const char *)(&size), sizeof(GLuint));
		data->write((const char *)(&size), sizeof(GLuint));
	}
	//RIFOut.write((const char *)(data_pointer), height * width * BPP >> 3);
	data->write((const char *)(data_pointer), height * width * BPP >> 3);
	data->flush();
	FreeImage_Unload(fib);
}

GLuint Resource::StoreTextureStream::LoadResource(string texture_name)
{
	std::map<std::string, GLuint>::iterator mIT = mMapTexture->find(texture_name);

	if (mIT != mMapTexture->end())return mIT->second;

	mGlobalTextureID++;

	LoadMapFromFileFreeImage(texture_name);
	mMapTexture->insert(pair<std::string, GLuint>(texture_name, mGlobalTextureID));
	return mGlobalTextureID;
}

GLuint Resource::StoreTextureStream::LoadTexture2DArray(string texture_name)
{
	return (-1);
}

std::string Resource::StoreTextureStream::GetWriterData(void)
{
	return mFileName;
}

void Resource::StoreTextureStream::SetEnd(void)
{
	GLuint mImageCount = mGlobalTextureID;

	data->flush();

	std::streampos mOutPos = data->tellp();

	data->seekp(0);
	data->write(reinterpret_cast<const char *>(&mImageCount), sizeof(GLuint));
	data->seekp(mOutPos);

	data->flush();
}
