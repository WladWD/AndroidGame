#include "BoundingObjectInstance.h"
#include "BoundingAABB.h"

#pragma once
namespace Collision
{
	//��������������� ��������� ������ ���������� ��� ���� ����
	class BoundingAABBInstance : public BoundingObjectInstance
	{
		////////////////////////////////////////////////////////////////////
		glm::mat4 mWorld;
		////////////////////////////////////////////////////////////////////
		BoundingAABB *mBoundingAABB;
		////////////////////////////////////////////////////////////////////
	public:
		BoundingAABBInstance(BoundingAABB *mBoundingAABB, glm::mat4 mWorld);
		~BoundingAABBInstance();
		////////////////////////////////////////////////////////////////////
		glm::vec3 GetCenter(void) const;
		glm::vec3 GetExtent(void) const;
		////////////////////////////////////////////////////////////////////
		void SetWorldMatrix(glm::mat4 mWorld);
		////////////////////////////////////////////////////////////////////
		glm::mat4 GetWorldMatrix(void) const;
		////////////////////////////////////////////////////////////////////
	};
	//�������� ���������� ������ ������������ ��� � ��������, � �������� ������� �������
}

