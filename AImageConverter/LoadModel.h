#include "MeshObject.h"
#include "StoreTextureStream.h"

#pragma once
namespace MEngine
{
	struct MObjects
	{
		std::vector<MEngine::MeshObject> mEntries;//�������� ������ � ��������
	};

	class LoadModel
	{
		bool needWrite;
		/////////////////////////////////////////////////////////
		Resource::StoreTextureStream *mStoreTextureFormat;
		/////////////////////////////////////////////////////////
		MeshLoad::StandartMesh mesh_VNT;//���������� ������ ������ � �������� 
		/////////////////////////////////////////////////////////
		MObjects *VNT_object;
		/////////////////////////////////////////////////////////
		void InitScene(const aiScene* pScene, std::string mRelativePath);
		void InitMeshVNT(uint32_t base_vertex, uint32_t base_index, const aiMesh *paiMesh);//��������� ������ ���� ���� MeshLoad::ID_Face::TRIANGLE_NTEX
	public:
		LoadModel(std::string mRelativePath, std::string mFileName, std::string mImageFileName, bool needWrite = true);
		~LoadModel();
		/////////////////////////////////////////////////////////
		const Resource::StoreTextureStream *GetResource(void);
		const MEngine::MObjects *GetObjects(void);
		const MeshLoad::StandartMesh *GetMesh(void);
	};

	//������������� FreeImage �� ������ ����������
	//����� �� ���������� ��� �� ��� ������� ����������� ������� ����� ���� ������� � RGB � BRG � ������
	//���������� �������� �� DXTex
	//reflaction map - ��� ���������� �����!!!
	//specular map - ������ �������������� � reflaction map, ������ ���������� ������ red canal; -> R8
	//� �������� ������������ ������� specular map ������������ ��� ����� ����� ��������� ��������
	//��� ���� ������� ��� �������� ����� ���� ������������ �����, ��� ����� ������� ������� specular map ��������� � ������� r8
	//�� ��������� ��������� �������� ������������ ��� �� �������� ����� ����� ��� ��������� ��� ��� ���������
	//���� ��������� ��������� ��������� �������� � ������������� �� ���������� � ������ ���������� ���� ����

	//cubemap render one pass http://cg.siomax.ru/index.php/computer-graphics/10-one-pass-rendering-to-cube-map
	//multi pass http://stackoverflow.com/questions/28845375/rendering-a-dynamic-cubemap-opengl
}

