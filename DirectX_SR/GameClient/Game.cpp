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

#include "Skeleton.h"
using namespace ce::UI;
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
    _pPlayer = new Player(pf);
    pPlayerObj->AddComponent(_pPlayer);
    pPlayerObj->GetTransform()->SetLocalPosition(0, 1, 0);

    //InputHandler
    pGameObj = GameObject::Instantiate();
    _pInputHandler = new InputHandler(pPlayerObj, terrain);
    pGameObj->AddComponent(_pInputHandler);

    //TargetCamera
    pGameObj = GameObject::Instantiate();
    pGameObj->AddComponent(new TargetCamera(pPlayerObj->GetTransform()));

    //for (int i = 0; i < 20; i++)
    //{
    //    pGameObj = GameObject::Instantiate();
    //    pGameObj->AddComponent(new Skeleton());
    //}


    InitUI();

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

    //RB
    _bRChk = false;
    pObj = GameObject::Instantiate();
    _pImgR = static_cast<Image*>(pObj->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"))));
    pObj->GetTransform()->SetWorldPosition(875, 675, 0);
    Button<Game>* btn = static_cast<Button<Game>*>(pObj->AddComponent(new Button<Game>(this)));
    btn->onMouseDown += &Game::RClick;

    _pBtnRAttack = GameObject::Instantiate();
    Image* img = static_cast<Image*>(_pBtnRAttack->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"))));
    _pBtnRAttack->GetTransform()->SetWorldPosition(875, 628, 0);
    btn = static_cast<Button<Game>*>(_pBtnRAttack->AddComponent(new Button<Game>(this)));
    btn->onMouseUp += &Game::SetRAttack;
    _pBtnRAttack->SetActive(false);

    _pBtnRRaise = GameObject::Instantiate();
    img = static_cast<Image*>(_pBtnRRaise->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\21.png"))));
    _pBtnRRaise->GetTransform()->SetWorldPosition(827, 628, 0);
    btn = static_cast<Button<Game>*>(_pBtnRRaise->AddComponent(new Button<Game>(this)));
    btn->onMouseUp += &Game::SetRRaise;
    _pBtnRRaise->SetActive(false);

    _pBtnRSpear = GameObject::Instantiate();
    img = static_cast<Image*>(_pBtnRSpear->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\6.png"))));
    _pBtnRSpear->GetTransform()->SetWorldPosition(827, 581, 0);
    btn = static_cast<Button<Game>*>(_pBtnRSpear->AddComponent(new Button<Game>(this)));
    btn->onMouseUp += &Game::SetRSpear;
    _pBtnRSpear->SetActive(false);

    // LB
    _bLChk = false;
    pObj = GameObject::Instantiate();
    _pImgL = static_cast<Image*>(pObj->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"))));
    pObj->GetTransform()->SetWorldPosition(358, 675, 0);
    btn = static_cast<Button<Game>*>(pObj->AddComponent(new Button<Game>(this)));
    btn->onMouseDown += &Game::LClick;

    _pBtnLAttack = GameObject::Instantiate();
    img = static_cast<Image*>(_pBtnLAttack->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"))));
    _pBtnLAttack->GetTransform()->SetWorldPosition(358, 628, 0);
    btn = static_cast<Button<Game>*>(_pBtnLAttack->AddComponent(new Button<Game>(this)));
    btn->onMouseUp += &Game::SetLAttack;
    _pBtnLAttack->SetActive(false);

    _pBtnLRaise = GameObject::Instantiate();
    img = static_cast<Image*>(_pBtnLRaise->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\21.png"))));
    _pBtnLRaise->GetTransform()->SetWorldPosition(407, 628, 0);
    btn = static_cast<Button<Game>*>(_pBtnLRaise->AddComponent(new Button<Game>(this)));
    btn->onMouseUp += &Game::SetLRaise;
    _pBtnLRaise->SetActive(false);

    _pBtnLSpear = GameObject::Instantiate();
    img = static_cast<Image*>(_pBtnLSpear->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\6.png"))));
    _pBtnLSpear->GetTransform()->SetWorldPosition(407, 581, 0);
    btn = static_cast<Button<Game>*>(_pBtnLSpear->AddComponent(new Button<Game>(this)));
    btn->onMouseUp += &Game::SetLSpear;
    _pBtnLSpear->SetActive(false);
}

void Game::RClick()
{
    if (!_bRChk) 
    {
        _bRChk = true;
        _pBtnRAttack->SetActive(true);
        _pBtnRRaise->SetActive(true);
        _pBtnRSpear->SetActive(true);
    }
    else
    { 
        _bRChk = false;
        _pBtnRAttack->SetActive(false);
        _pBtnRRaise->SetActive(false);
        _pBtnRSpear->SetActive(false);
    }
}

void Game::SetRAttack() noexcept
{
    RClick();
    _pImgR->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"));
    _pInputHandler->SetRB(SKILL_END);
}

void Game::SetRRaise() noexcept
{
    RClick();
    _pImgR->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\21.png"));
    _pInputHandler->SetRB(SKILL_ID::RAISE_SKELETON);
}

void Game::SetRSpear() noexcept
{
    RClick();
    _pImgR->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\6.png"));
    _pInputHandler->SetRB(SKILL_ID::BONE_SPEAR);
}

void Game::LClick()
{
    if (!_bLChk)
    {
        _bLChk = true;
        _pBtnLAttack->SetActive(true);
        _pBtnLRaise->SetActive(true);
        _pBtnLSpear->SetActive(true);
    }
    else
    {
        _bLChk = false;
        _pBtnLAttack->SetActive(false);
        _pBtnLRaise->SetActive(false);  
        _pBtnLSpear->SetActive(false);
    }
}

void Game::SetLAttack() noexcept
{
    LClick();
    _pImgL->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"));
    _pInputHandler->SetLB(SKILL_END);
}

void Game::SetLRaise() noexcept
{
    LClick();
    _pImgL->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\21.png"));
    _pInputHandler->SetLB(RAISE_SKELETON);
}

void Game::SetLSpear() noexcept
{
    LClick();
    _pImgL->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\6.png"));
    _pInputHandler->SetLB(BONE_SPEAR);
}
