#include "pch.h"
#include "TownScene_01.h"
#include "Terrain.h"
#include "TerrainRenderer.h"
#include "EditorCamera.h"
#include "AudioListener.h"
#include "Transform.h"
#include "CubeObject.h"
#include "SphereCollider.h"
#include "RigidBody.h"
#include "TerrainCollider.h"
#include "Camera.h"

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
	obj->AddComponent(new TerrainCollider(terrain));

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
		obj->SetLayer(GameObjectLayer::OBJECT);
	}

	obj = GameObject::Instantiate();
	obj->AddComponent(new EditorCamera(g_hWnd));
	obj->AddComponent(new AudioListener());
	obj->GetTransform()->SetWorldPosition(10, 10, 10);
	obj->GetTransform()->SetLocalEulerAngle(45, 0, 0);
	//obj->AddComponent(new SphereCollider(5));
	//obj->AddComponent(new Rigidbody());

	return true;
}

void TownScene_01::FixedUpdate(float fElapsedTime) noexcept
{

}

void TownScene_01::Update(float fElapsedTime) noexcept
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (Camera::GetMainCamera() == nullptr)
			CE_ASSERT("ckswns", "main camera does not exits");
		Ray ray = Camera::GetMainCamera()->ScreenPointToRay(INPUT->GetMousePosition());
		RaycastHit hit;

		if (Physics::Raycast(ray, hit, GameObjectLayer::OBJECT))
		{
			hit.collider->GetGameObject()->Destroy();
		}

		//if (Physics::Raycast(ray, hit, GameObjectLayer::BACKGROUND))
		//{
		//	GameObject* obj = GameObject::Instantiate();
		//	obj->AddComponent(new CubeObject);
		//	obj->GetTransform()->SetWorldPosition(hit.point);
		//}
	}
}

void TownScene_01::LateUpdate(float fElapsedTime) noexcept
{

}

void TownScene_01::Render(float fElapsedTime) noexcept
{
	//auto device = D3D9DEVICE->GetDevice();

	//float a = 0.f;
	//float b = 30.f;

	//device->SetRenderState(D3DRS_FOGENABLE, TRUE);
	//device->SetRenderState(D3DRS_RANGEFOGENABLE, true);
	//device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	//device->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	//device->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, 50, 50, 50));
	//device->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&a));
	//device->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&b));
}

void TownScene_01::Release(void) noexcept
{

}
