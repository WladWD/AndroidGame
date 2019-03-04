#include "MeshObject.h"
#include "StoreTextureStream.h"

#pragma once
namespace MEngine
{
	struct MObjects
	{
		std::vector<MEngine::MeshObject> mEntries;//содержит записи о объектах
	};

	class LoadModel
	{
		bool needWrite;
		/////////////////////////////////////////////////////////
		Resource::StoreTextureStream *mStoreTextureFormat;
		/////////////////////////////////////////////////////////
		MeshLoad::StandartMesh mesh_VNT;//глобальные списки вершин и индексов 
		/////////////////////////////////////////////////////////
		MObjects *VNT_object;
		/////////////////////////////////////////////////////////
		void InitScene(const aiScene* pScene, std::string mRelativePath);
		void InitMeshVNT(uint32_t base_vertex, uint32_t base_index, const aiMesh *paiMesh);//загружает только меши вида MeshLoad::ID_Face::TRIANGLE_NTEX
	public:
		LoadModel(std::string mRelativePath, std::string mFileName, std::string mImageFileName, bool needWrite = true);
		~LoadModel();
		/////////////////////////////////////////////////////////
		const Resource::StoreTextureStream *GetResource(void);
		const MEngine::MObjects *GetObjects(void);
		const MeshLoad::StandartMesh *GetMesh(void);
	};

	//Использование FreeImage не всегда эффективно
	//однин из артефактов это то что форматы загружаемых текстур могут быть разными и RGB и BRG и другие
	//Необходимо заменить на DXTex
	//reflaction map - это кубическая карта!!!
	//specular map - должна использоваться с reflaction map, причем достаточно только red canal; -> R8
	//в релизной конфигурации следует specular map использовать как альфа канал диффузной текстуры
	//при этом следить что текстура может сама использовать альфа, для таких текстур следует specular map сохранить в формате r8
	//по умолчанию диффузные картинки загружаються или не испльзую альфа канал или используя его для отсечения
	//если необходмо загрузить диффузную картинку с прозрачностью то необходимо в ручную установить этот флаг

	//cubemap render one pass http://cg.siomax.ru/index.php/computer-graphics/10-one-pass-rendering-to-cube-map
	//multi pass http://stackoverflow.com/questions/28845375/rendering-a-dynamic-cubemap-opengl
}

