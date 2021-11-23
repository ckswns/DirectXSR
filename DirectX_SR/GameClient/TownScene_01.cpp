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
#include "BillboardSprite.h"
#include "Cow.h"

#include "Player.h"
#include "NaviMesh.h"
#include "PathFinding.h"
#include "TargetCamera.h"
#include "StatusBar.h"
#include "Light.h"

#include "SpriteRenderer.h"
#include "PlaneRenderer.h"
#include "BoxCollider.h"
#include "ParticleRenderer.h"
#include "BillboardObj.h"
#include "BGMPlayer.h"
#include "Portal.h"

#include "StoreNPC.h"
#include "FadeController.h"
#include "Witch.h"

TownScene_01::TownScene_01(void) noexcept
{
}

bool TownScene_01::Init(void) noexcept
{
	NaviMesh* _pNaviMesh;
	FadeController::FadeIn(5);

	Terrain* terrain = new Terrain(INIMANAGER->LoadDataInteger("Asset\\Scene\\Town_01\\Terrain", "Terrain", "MapWidth") + 1,
		INIMANAGER->LoadDataInteger("Asset\\Scene\\Town_01\\Terrain", "Terrain", "MapHeight") + 1, 1);
	{
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
			sprintf_s(str, 256, "Asset\\Scene\\Town_01\\AlphaMap\\AlphaMap%d.png", i);
			vt.push_back(ASSETMANAGER->GetTextureData(str));
		}

		mat->SetTextures(vt);
		vt.clear();

		mat = tr->GetMaterialPTR();

		for (int i = 1; i <= 5; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Terrain\\Tile\\Tile%d.png", i);
			vt.push_back(ASSETMANAGER->GetTextureData(str));
		}

		mat->SetTextures(vt);
		vt.clear();

		_pNaviMesh = new NaviMesh(terrain->Get_VtxPos(), terrain->Get_VtxCntX(), terrain->Get_VtxCntZ());
		_pNaviMesh->Init();

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

			if (stof(py) > 1)
				continue;

			//obj->AddComponent(new CubeObject(ASSETMANAGER->GetTextureData(filePath.c_str())));

			if (stof(sz) < stof(sx))
			{
				obj->AddComponent(new PlaneRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Terrain\\barricade.png"), stof(sx), 1));
				obj->AddComponent(new BoxCollider(D3DXVECTOR3(stof(sx), 1, 1)));
			}
			else
			{
				obj->AddComponent(new BoxCollider(D3DXVECTOR3(1, 1, stof(sz))));
				obj->AddComponent(new PlaneRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Terrain\\barricade.png"), stof(sz), 1));
			}
			Transform* tr = obj->GetTransform();
			//tr->SetLocalScale(stof(sx), stof(sy), stof(sz));
			tr->SetWorldPosition(stof(px), stof(py), stof(pz));
			if (stof(sz) > stof(sx))
			{
				if (INIMANAGER->LoadDataInteger("Asset\\Scene\\Town_01\\Terrain", "Terrain", "MapWidth") / 2 < stof(px))
					tr->SetLocalEulerAngle(0, D3DXToRadian(90), 0);
				else
					tr->SetLocalEulerAngle(0, D3DXToRadian(-90), 0);
			}

			_pNaviMesh->SetWalkAbleFromPosition(D3DXVECTOR3(stof(px), 0, stof(pz)), false);

			for (int i = 0; i < (int)stof(sx) / 2; i++)
			{
				_pNaviMesh->SetWalkAbleFromPosition(D3DXVECTOR3(stof(px) - i, 0, stof(pz)), false);
				_pNaviMesh->SetWalkAbleFromPosition(D3DXVECTOR3(stof(px) + i, 0, stof(pz)), false);
			}

			for (int i = 0; i < (int)stof(sz) / 2; i++)
			{
				_pNaviMesh->SetWalkAbleFromPosition(D3DXVECTOR3(stof(px), 0, stof(pz) - i), false);
				_pNaviMesh->SetWalkAbleFromPosition(D3DXVECTOR3(stof(px), 0, stof(pz) + i), false);
			}

			obj->SetLayer(GameObjectLayer::BACKGROUND);
			obj->SetTag(GameObjectTag::OBSTACLE);
		}

		std::string name = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\Object", "SectionNames", "Names");

		std::vector<std::string> names = Util::Split(name, ',');

		for (int i = 0; i < names.size(); i++)
		{
			if (names[i].find("Tree") != std::string::npos)
			{
				std::string fileName = names[i].substr(0, 5);
				fileName += ".png";
				obj = GameObject::Instantiate();
				obj->AddComponent(new BillboardSprite(ASSETMANAGER->GetTextureData("Asset\\Terrain\\Tree\\" + fileName)));

				std::string px = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\Object", names[i].c_str(), "worldX");
				std::string py = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\Object", names[i].c_str(), "worldY");
				std::string pz = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\Object", names[i].c_str(), "worldZ");

				obj->GetTransform()->SetWorldPosition(stof(px), stof(py), stof(pz));
				_pNaviMesh->SetWalkAbleFromPosition(D3DXVECTOR3(stof(px), 0, stof(pz)), false);
			}

			if (names[i].find("Portal") != std::string::npos)
			{
				std::string sceneKey = Util::Split(names[i], '@')[1];
				GameObject* obj = GameObject::Instantiate();
				obj->AddComponent(new Portal(sceneKey.c_str()));

				std::string px = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\Object", names[i].c_str(), "worldX");
				std::string py = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\Object", names[i].c_str(), "worldY");
				std::string pz = INIMANAGER->LoadDataString("Asset\\Scene\\Town_01\\Object", names[i].c_str(), "worldZ");
				obj->GetTransform()->SetWorldPosition(stof(px), 1, stof(pz));
			}
		}
	}

	D3DCOLORVALUE c;
	c.a = 1;
	c.r = 0.25f;
	c.g = 0.25f;
	c.b = 0.25f;

	GameObject* obj = GameObject::Instantiate();
	obj->GetTransform()->SetWorldPosition(0, -3, 0);
	obj->GetTransform()->SetLocalEulerAngle(120, 0, 0);
	obj->AddComponent(new Light(Light::Type::DIRECTIONAL, D3D9DEVICE->GetDevice(), c, 1000));

	obj = GameObject::Instantiate();
	obj->AddComponent(new ParticleRenderer(D3D9DEVICE->GetDevice(), "Asset\\Data\\healing_spot.dat"));
	obj->GetTransform()->SetWorldPosition(10, 0, 10);
	obj->AddComponent(new BillboardObj());
	//Player
	PathFinding* pf = new PathFinding(_pNaviMesh);

	GameObject* playerObj = GameObject::FindObjectByTag(GameObjectTag::PLAYER);
	if (playerObj == nullptr)
	{
		playerObj = GameObject::Instantiate();
		Player* player = new Player(pf);
		playerObj->AddComponent(player);
		playerObj->GetTransform()->SetLocalPosition(
			INIMANAGER->LoadDataInteger("Asset\\Scene\\Town_01\\Object", "Player", "worldX"),
			0.5f,
			INIMANAGER->LoadDataInteger("Asset\\Scene\\Town_01\\Object", "Player", "worldZ"));

		//TargetCamera
		GameObject* pGameObj = GameObject::Instantiate();
		pGameObj->AddComponent(new TargetCamera(playerObj->GetTransform()));
		pGameObj->GetTransform()->SetLocalPosition(playerObj->GetTransform()->GetLocalPosition());
		pGameObj->SetDontDestroy(true);
		//UI
		pGameObj = GameObject::Instantiate();
		pGameObj->AddComponent(new StatusBar(player));
		pGameObj->SetDontDestroy(true);
	}
	else
	{
		Player* player = playerObj->GetComponent<Player>(COMPONENT_ID::BEHAVIOUR);
		player->SetMap(pf);
		player->SetState(PLAYER_STAND, FRONT);
		playerObj->GetTransform()->SetLocalPosition(
			INIMANAGER->LoadDataInteger("Asset\\Scene\\Town_01\\Object", "Player", "worldX"),
			0.5f,
			INIMANAGER->LoadDataInteger("Asset\\Scene\\Town_01\\Object", "Player", "worldZ"));
	}

	GameObject* pGameObj = GameObject::Instantiate();
	pGameObj->AddComponent(new StoreNPC());
	pGameObj->GetTransform()->SetWorldPosition(10, 0.5, 10);

	//for (int i = 0; i < 10; i++)
	//{
	//	obj = GameObject::Instantiate();

	//	D3DXVECTOR3 pos = playerObj->GetTransform()->GetWorldPosition();

	//	pos.x += Random::GetValue(20, 3);
	//	pos.x -= Random::GetValue(20, 3);
	//	pos.y = 0.7f;
	//	pos.z += Random::GetValue(20, 3);
	//	pos.z -= Random::GetValue(20, 3);
	//	obj->AddComponent(new Witch(new PathFinding(_pNaviMesh), pos));
	//}

	BGMPlayer::Instance()->SetBGM(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\TownBGM.mp3"));

	return true;
}

void TownScene_01::FixedUpdate(float fElapsedTime) noexcept
{

}

void TownScene_01::Update(float fElapsedTime) noexcept
{
	//if (INPUT->GetKeyDown(VK_LBUTTON))
	//{
	//	if (Camera::GetMainCamera() == nullptr)
	//		CE_ASSERT("ckswns", "main camera does not exits");
	//	Ray ray = Camera::GetMainCamera()->ScreenPointToRay(INPUT->GetMousePosition());
	//	RaycastHit hit;

	//	if (Physics::Raycast(ray, hit, GameObjectLayer::OBJECT))
	//	{
	//		hit.collider->GetGameObject()->Destroy();
	//	}

	//	//if (Physics::Raycast(ray, hit, GameObjectLayer::BACKGROUND))
	//	//{
	//	//	GameObject* obj = GameObject::Instantiate();
	//	//	obj->AddComponent(new CubeObject);
	//	//	obj->GetTransform()->SetWorldPosition(hit.point);
	//	//}
	//}
}

void TownScene_01::LateUpdate(float fElapsedTime) noexcept
{

}

void TownScene_01::Render(float fElapsedTime) noexcept
{
	auto device = D3D9DEVICE->GetDevice();

	device->SetRenderState(D3DRS_FOGENABLE, false);
}

void TownScene_01::Release(void) noexcept
{

}
