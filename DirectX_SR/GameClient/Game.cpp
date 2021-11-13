#include "pch.h"
#include "Game.h"
#include "GameObject.h"

#include "InputHandler.h"
#include "Player.h"
#include "Transform.h"

#include "NaviMesh.h"
#include "PathFinding.h"

#include "TargetCamera.h"
#include "Terrain.h"
#include "MeshRenderer.h"

#include "Image.h"
#include "Button.h"
using namespace ce::UI;
Game::Game(void) noexcept
{
}

bool Game::Init(void) noexcept
{
    InitUI();

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
    _pPlayer = new Player(pf);
    pPlayerObj->AddComponent(_pPlayer);
    pPlayerObj->GetTransform()->SetLocalPosition(0, 1, 0);

    //InputHandler
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new InputHandler(pPlayerObj, terrain));

    //TargetCamera
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new TargetCamera(pPlayerObj->GetTransform()));

    return false;
}

void Game::FixedUpdate(float fElapsedTime) noexcept
{
}

void Game::Update(float fElapsedTime) noexcept
{
    //세로로 변경해야함
    _imgHP->SetFillAmount(_pPlayer->GetHPPer());
    _imgMP->SetFillAmount(_pPlayer->GetMPPer());

    _imgStamina->SetFillAmount(_pPlayer->GetStaminaPer());
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
    GameObject* pObj = GameObject::Instantiate();
    pObj->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\StatusBar.png")));
    pObj->SetSortOrder(0);
    pObj->GetTransform()->SetWorldPosition(240, 617, 0);

    _imgStamina = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Stamina.png"));
    pObj = GameObject::Instantiate();
    pObj->AddComponent(_imgStamina);
    pObj->SetSortOrder(0);
    pObj->GetTransform()->SetWorldPosition(513, 694, 0);

    _imgHP = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\HPBall.png"));
    pObj = GameObject::Instantiate();
    pObj->AddComponent(_imgHP);
    pObj->SetSortOrder(0);
    pObj->GetTransform()->SetWorldPosition(270, 627, 0);

    _imgMP = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\MPBall.png"));
    pObj = GameObject::Instantiate();
    pObj->AddComponent(_imgMP);
    pObj->SetSortOrder(0);
    pObj->GetTransform()->SetWorldPosition(930, 627, 0);

    pObj = GameObject::Instantiate();
    Image* img = static_cast<Image*>(pObj->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"))));
    pObj->GetTransform()->SetWorldPosition(875, 675, 0);
    Button<Game>* btnR = static_cast<Button<Game>*>(pObj->AddComponent(new Button<Game>(this)));
    btnR->onMouseDown += &Game::RClick;
    pObj->SetName("test");

    btnTest = GameObject::Instantiate();
    img = static_cast<Image*>(btnTest->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"))));
    btnTest->GetTransform()->SetWorldPosition(875, 627, 0);
    //Button<Game>* btn = static_cast<Button<Game>*>(btnTest->AddComponent(new Button<Game>(this)));
    btnTest->SetActive(false);
}

void Game::RClick()
{
    btnTest->SetActive(true);
}
