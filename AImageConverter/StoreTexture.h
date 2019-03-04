#include "ResourceStruct.h"
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include <vector>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include <string>
#include "DirectXTex.h"
#include <FreeImage.h>
#include "GLI_Include.h"
#include <fstream>

#pragma once
using namespace std;
namespace RIF
{
	class StoreTexture
	{
		bool cur_use_alpha;
		////////////////////////////////////////////////////////////////////////////////
	/*	void LoadMapFromFileDirectXTex(string texture_name, string mWriteName);
		RIF::GLTextureResource LoadTexture2DArrayFromFileDirectXTex(string texture_name, uint32_t max_count);
		GLenum GetExtermalFormat(DXGI_FORMAT dxgi_format);
		void GetInteralFormat(DXGI_FORMAT dxgi_format, GLenum &format, GLenum &type_pixel);*/
		void LoadMapFromFileFreeImage(string texture_name, string mWriteName);
		void LoadMapFromFileGLI(string texture_name, string mWriteName);
	public:
		StoreTexture(void);
		~StoreTexture();
		////////////////////////////////////////////////////////////////////////////////
		void LoadResource(string texture_name, string mWriteName);
		void LoadTexture2DArray(string texture_name, uint32_t max_count);
		////////////////////////////////////////////////////////////////////////////////
	};
}
//класс загружаем материалы и сохраняет их в класс MapResource