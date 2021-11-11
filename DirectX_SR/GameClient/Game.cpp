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

#include "Image.h"
#include "RectTransform.h"
using namespace ce::UI;
Game::Game(void) noexcept
{
}

bool Game::Init(void) noexcept
{
    InitUI();

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
    pPlayer->GetTransform()->SetLocalPosition(0, 1, 0);

    //GameObject* pSkeleton = GameObject::Instantiate();
    //pSkeleton->AddComponent(new Skeleton(pPlayer->GetTransform()));
    //pSkeleton->GetTransform()->SetWorldPosition(1,1,0);

    //InputHandler
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new InputHandler(pPlayer, terrain));

    //EditorCamera
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new EditorCamera(g_hWnd));
    pGameObj->GetTransform()->SetLocalPosition(7, 8, -8);
    pGameObj->GetTransform()->SetLocalEulerAngle(-50, 0, 0);

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

void Game::InitUI() noexcept
{
    Texture* texStatusBar = new Texture();
    texStatusBar->Init(D3D9DEVICE->GetDevice(), "Asset/UI/Game/StatusBar.png");

    GameObject* pObj = GameObject::Instantiate();
    pObj->AddComponent(new Image(texStatusBar));
   // RectTransform* rt = static_cast<RectTransform*>(pObj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
    pObj->SetSortOrder(0);
    pObj->GetTransform()->SetWorldPosition(240, 617, 0);

    Texture* texStamina = new Texture();
    texStamina->Init(D3D9DEVICE->GetDevice(), "Asset/UI/Game/Stamina.png");
    _imgStamina = new Image(texStamina);
    pObj = GameObject::Instantiate();
    pObj->AddComponent(_imgStamina);
    // RectTransform* rt = static_cast<RectTransform*>(pObj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
    pObj->SetSortOrder(0);
    pObj->GetTransform()->SetWorldPosition(513, 694, 0);
}
