#include "pch.h"
#include "TownScene_01.h"
#include "Terrain.h"
#include "TerrainRenderer.h"
#include "EditorCamera.h"
#include "AudioListener.h"
#include "Transform.h"
#include "CubeObject.h"

TownScene_01::TownScene_01(void) noexcept
{
}

bool TownScene_01::Init(void) noexcept
{
	Terrain* terrain = new Terrain(51, 51, 1);
	terrain->Open(D3D9DEVICE->GetDevice());

	GameObject* obj;
	obj = GameObject::Instantiate();
	TerrainRenderer* tr = static_cast<TerrainRenderer*>(obj->AddComponent(new TerrainRenderer(D3D9DEVICE->GetDevice(), terrain)));
	Material* mat = tr->GetAlphaMaterial();
	obj->SetLayer(GameObjectLayer::BACKGROUND);

	std::vector<Texture*> vt;

	for (int i = 1; i <= 4; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Terrain\\AlphaMap\\AlphaMap%d.png", i);
		vt.push_back(ASSETMANAGER->GetTextureData(str));
	}

	mat->SetTextures(vt);
	vt.clear();

	mat = tr->GetMaterialPTR();

	for (int i = 0; i < 4; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Terrain\\Tile\\Tile%d.png", i);
		vt.push_back(ASSETMANAGER->GetTextureData(str));
	}
	mat->SetTextures(vt);
	vt.clear();

	int cubeCnt = INIMANAGER->LoadDataInteger("Asset\\Scene\\Town_01\\PickingCube", "Start", "CubeCnt");

	for (int i = 0; i < cubeCnt; i++)
	{
		obj = GameObject::Instantiate();
		std::string sectionName = "PickingCube" + std::to_string(i);
		std::string filePath = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\PickingCube", sectionName.c_str(), "filePath");
		filePath = filePath.substr(filePath.find('\\'));
		filePath = "Asset\\Terrain\\Box" + filePath;

		std::string sx = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\PickingCube", sectionName.c_str(), "scaleX");
		std::string sy = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\PickingCube", sectionName.c_str(), "scaleY");
		std::string sz = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\PickingCube", sectionName.c_str(), "scaleZ");

		std::string px = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\PickingCube", sectionName.c_str(), "worldposX");
		std::string py = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\PickingCube", sectionName.c_str(), "worldposY");
		std::string pz = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\PickingCube", sectionName.c_str(), "worldposZ");

		obj->AddComponent(new CubeObject(ASSETMANAGER->GetTextureData(filePath.c_str())));
		Transform* tr = obj->GetTransform();
		tr->SetLocalScale(stof(sx), stof(sy), stof(sz));
		tr->SetWorldPosition(stof(px), stof(py), stof(pz));
		obj->SetLayer(GameObjectLayer::BACKGROUND);
	}

	obj = GameObject::Instantiate();
	obj->AddComponent(new EditorCamera(g_hWnd));
	obj->AddComponent(new AudioListener());
	obj->GetTransform()->SetWorldPosition(0, 10, 0);
	obj->GetTransform()->SetLocalEulerAngle(45, 0, 0);

	return true;
}

void TownScene_01::FixedUpdate(float fElapsedTime) noexcept
{

}

void TownScene_01::Update(float fElapsedTime) noexcept
{

}

void TownScene_01::LateUpdate(float fElapsedTime) noexcept
{

}

void TownScene_01::Render(float fElapsedTime) noexcept
{

}

void TownScene_01::Release(void) noexcept
{

}
