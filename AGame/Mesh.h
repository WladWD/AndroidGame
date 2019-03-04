#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#pragma once
namespace Mesh 
{
	struct VNTMesh 
	{
		glm::vec3 gWorldPos;
		glm::vec3 gWorldNorm;
		glm::vec2 gTexCoord;
	};

	struct VTMesh
	{
		glm::vec3 gWorldPos;
		glm::vec2 gTexCoord;
	};

	struct OOBB
	{
		glm::vec4 mCenter;
		glm::vec4 mDim;


	};

	struct VFlash 
	{
		glm::vec3 gWorldPos;
		glm::vec4 gOffset_Tex;
	};
};
