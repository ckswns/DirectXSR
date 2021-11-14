#include "pch.h"
#include "StatusBar.h"
#include "Transform.h"
#include "Image.h"

#include "Player.h"
#include "InputHandler.h"
#include "MouseBtnUI.h"
using namespace ce::UI;

void StatusBar::Start(void) noexcept
{
    gameObject->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\StatusBar.png")));
    gameObject->SetSortOrder(0);
    gameObject->GetTransform()->SetWorldPosition(240, 617, 0);

    InitUI();
}

void StatusBar::Update(float fElapsedTime) noexcept
{
    _imgHP->SetFillAmount(_pPlayer->GetHPPer());
    _imgMP->SetFillAmount(_pPlayer->GetMPPer());

    _imgStamina->SetFillAmount(_pPlayer->GetStaminaPer());
}

void StatusBar::InitUI() noexcept
{
    _imgStamina = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Stamina.png"));
    GameObject* pObj = GameObject::Instantiate();
    pObj->AddComponent(_imgStamina);
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(273, 77, 0);
    pObj->SetSortOrder(1);

    _imgHP = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\HPBall.png"));
    pObj = GameObject::Instantiate();
    pObj->AddComponent(_imgHP);
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(30, 10, 0);    
    pObj->SetSortOrder(1);

    _imgMP = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\MPBall.png"));
    pObj = GameObject::Instantiate();
    pObj->AddComponent(_imgMP);
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(690, 10, 0);
    pObj->SetSortOrder(1);

    //LB
    pObj = GameObject::Instantiate();
    pObj->AddComponent(new MouseBtnUI(_pInputHandler, true));
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(116, 58, 0);

    //RB
    pObj = GameObject::Instantiate();
    pObj->AddComponent(new MouseBtnUI(_pInputHandler, false));
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(635, 58, 0);
}