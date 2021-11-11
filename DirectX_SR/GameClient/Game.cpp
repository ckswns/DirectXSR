#include "pch.h"
#include "Game.h"
#include "GameObject.h"

#include "InputHandler.h"
#include "Player.h"
#include "Transform.h"

#include "NeviMesh.h"
#include "PathFinding.h"

#include "EditorCamera.h"
#include "Terrain.h"
#include "Texture.h"
#include "MeshRenderer.h"

#include "Skeleton.h"

Game::Game(void) noexcept
{
}

bool Game::Init(void) noexcept
{
    Texture* _pTexture = new Texture();
    _pTexture->Init(D3D9DEVICE->GetDevice(), "Asset/Tile.png");

    //Terrain
    GameObject*  pGameObj = GameObject::Instantiate();
    Terrain* terrain = new Terrain(20,20);
    terrain->Open(D3D9DEVICE->GetDevice());

    MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), terrain);
    pGameObj->AddComponent(mr);

    std::vector<Texture*> TList;
    TList.push_back(_pTexture);
    mr->GetMaterialPTR()->SetTextures(TList);
    pGameObj->GetTransform()->SetLocalPosition(-2, 0, -1);

    _pNeviMesh = new NeviMesh(terrain->Get_VtxPos(), terrain->Get_VtxCntX(), terrain->Get_VtxCntZ());
    _pNeviMesh->Init();

    //Player
    GameObject* pPlayer = GameObject::Instantiate();
    PathFinding* pf = new PathFinding(_pNeviMesh);
    pPlayer->AddComponent(new Player(pf));
    //pPlayer->GetTransform()->SetLocalPosition(0, 1, 0);

    //GameObject* pSkeleton = GameObject::Instantiate();
    //pSkeleton->AddComponent(new Skeleton(pPlayer->GetTransform()));
    //pSkeleton->GetTransform()->SetWorldPosition(1,1,0);

    //InputHandler
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new InputHandler(pPlayer, terrain));

    //EditorCamera
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new EditorCamera(g_hWnd));
    pGameObj->GetTransform()->SetLocalPosition(3, 3, -3);
    pGameObj->GetTransform()->SetLocalEulerAngle(0, 0, 0);

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
