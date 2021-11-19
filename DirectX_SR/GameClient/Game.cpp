#include "pch.h"
#include "Game.h"
#include "GameObject.h"

#include "InputHandler.h"
#include "NaviMesh.h"
#include "PathFinding.h"
#include "Player.h"
#include "TargetCamera.h"
#include "StatusBar.h"
#include "Transform.h"

#include "Terrain.h"
#include "TerrainRenderer.h"
#include "TerrainCollider.h"

#include "Mephisto.h"
Game::Game(void) noexcept
{
}

bool Game::Init(void) noexcept
{
    //Terrain
    GameObject*  pGameObj = GameObject::Instantiate();
    Terrain* terrain = new Terrain(20,20);
    terrain->Open(D3D9DEVICE->GetDevice());

    TerrainRenderer* tr = static_cast<TerrainRenderer*>(pGameObj->AddComponent(new TerrainRenderer(D3D9DEVICE->GetDevice(), terrain)));
    Material* mat = tr->GetAlphaMaterial();
    pGameObj->SetLayer(GameObjectLayer::BACKGROUND);
    pGameObj->AddComponent(new TerrainCollider(terrain));
    std::vector<Texture*> TList;
    TList.push_back(ASSETMANAGER->GetTextureData("Asset\\Tile.png"));
    tr->GetMaterialPTR()->SetTextures(TList);
    TList.clear();

    NaviMesh* _pNaviMesh = new NaviMesh(terrain->Get_VtxPos(), terrain->Get_VtxCntX(), terrain->Get_VtxCntZ());
    _pNaviMesh->Init();

    //Player
    GameObject* pPlayerObj = GameObject::Instantiate();
    pPlayerObj = GameObject::Instantiate();
    PathFinding* pf = new PathFinding(_pNaviMesh);
    Player* player = new Player(pf);
    pPlayerObj->AddComponent(player);
    pPlayerObj->GetTransform()->SetLocalPosition(0, 0.5f, 0);

    //TestCube

    //obj->GetTransform()->SetWorldPosition(5,1,5);

    //TargetCamera
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new TargetCamera(pPlayerObj->GetTransform()));

    //UI
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new StatusBar(player));

    return false;
}

void Game::FixedUpdate(float fElapsedTime) noexcept
{
}

void Game::Update(float fElapsedTime) noexcept
{
}

void Game::LateUpdate(float fElapsedTime) noexcept
{
}

void Game::Render(float fElapsedTime) noexcept
{
}

void Game::Release(void) noexcept
{
}

