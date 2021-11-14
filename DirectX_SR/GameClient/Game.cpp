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
#include "MeshRenderer.h"

Game::Game(void) noexcept
{
}

bool Game::Init(void) noexcept
{
    //Terrain
    GameObject*  pGameObj = GameObject::Instantiate();
    Terrain* terrain = new Terrain(20,20);
    terrain->Open(D3D9DEVICE->GetDevice());

    MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), terrain);
    pGameObj->AddComponent(mr);

    std::vector<Texture*> TList;
    TList.push_back(ASSETMANAGER->GetTextureData("Asset\\Tile.png"));
    mr->GetMaterialPTR()->SetTextures(TList);
    pGameObj->GetTransform()->SetLocalPosition(-2, 0, -1);

    NaviMesh* _pNaviMesh = new NaviMesh(terrain->Get_VtxPos(), terrain->Get_VtxCntX(), terrain->Get_VtxCntZ());
    _pNaviMesh->Init();

    //Player
    GameObject* pPlayerObj = GameObject::Instantiate();
    pPlayerObj = GameObject::Instantiate();
    PathFinding* pf = new PathFinding(_pNaviMesh);
    Player* player = new Player(pf);
    pPlayerObj->AddComponent(player);
    pPlayerObj->GetTransform()->SetLocalPosition(0, 1, 0);

    //TargetCamera
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new TargetCamera(pPlayerObj->GetTransform()));

    //InputHandler
    pGameObj = GameObject::Instantiate();
    InputHandler* pInputHandler = new InputHandler(pPlayerObj, terrain);
    pGameObj->AddComponent(pInputHandler);

    //UI
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new StatusBar(pInputHandler, player));

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

