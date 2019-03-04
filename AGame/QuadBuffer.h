#include "MHeder.h"
#include "ModelObject.h"
#include "ImageResource.h"
#include "Mesh.h"

#pragma once
namespace DrawScore
{
	class QuadBuffer
	{
		////////////////////////////////////////////////////////////////////////////////////
		GLuint mElementArray;
		GLuint mVertexArray;
		////////////////////////////////////////////////////////////////////////////////////
		GLuint mElementArrayFormat;
		////////////////////////////////////////////////////////////////////////////////////
		void Init(void);
	public:
		QuadBuffer();
		~QuadBuffer();
		////////////////////////////////////////////////////////////////////////////////////
		void BindBuffer(void);
		void UnbindBuffer(void);
		////////////////////////////////////////////////////////////////////////////////////
		void Draw(void);
		////////////////////////////////////////////////////////////////////////////////////
	};
}

