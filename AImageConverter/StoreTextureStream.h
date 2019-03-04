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

#include <fstream>
#include <map>
#include <sstream>
#include <FreeImage.h>

#pragma once
namespace Resource
{
	class StoreTextureStream
	{
		bool cur_use_alpha;
		////////////////////////////////////////////////////////////////////////////////
		std::string mFileName;
		std::ofstream *data;
		GLuint mGlobalTextureID;
		std::map<std::string, GLuint> *mMapTexture;
		////////////////////////////////////////////////////////////////////////////////
		void LoadMapFromFileFreeImage(std::string texture_name);
	public:
		StoreTextureStream(std::string mFileName);
		~StoreTextureStream();
		////////////////////////////////////////////////////////////////////////////////
		GLuint LoadResource(std::string texture_name);
		GLuint LoadTexture2DArray(std::string texture_name);
		////////////////////////////////////////////////////////////////////////////////
		std::string GetWriterData(void);
		////////////////////////////////////////////////////////////////////////////////
		void SetEnd(void);
		////////////////////////////////////////////////////////////////////////////////
	};
}
