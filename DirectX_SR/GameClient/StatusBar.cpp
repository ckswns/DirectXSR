#include "pch.h"
#include "StatusBar.h"
#include "Transform.h"
#include "Image.h"

#include "Player.h"
#include "InputHandler.h"
#include "MouseBtnUI.h"
#include "StatusBall.h"
using namespace ce::UI;

StatusBar::StatusBar(Player* player) noexcept
    :_pPlayer(player) 
{
    _pInputHandler = _pPlayer->GetInpuHandler();
}

void StatusBar::Start(void) noexcept
{
    gameObject->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\StatusBar.png")));
    gameObject->SetSortOrder(2);
    gameObject->GetTransform()->SetWorldPosition(0,557, 0);

    InitUI();
}

void StatusBar::Update(float fElapsedTime) noexcept
{

    _imgStamina->SetFillAmount(_pPlayer->GetStaminaPer());
}

void StatusBar::InitUI() noexcept
{
    _imgStamina = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Stamina.png"));
    GameObject* pObj = GameObject::Instantiate();
    pObj->AddComponent(_imgStamina);
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(435, 118, 0);
    pObj->SetSortOrder(3);
    pObj->SetDontDestroy(true);

    pObj = GameObject::Instantiate();
    pObj->AddComponent(new StatusBall(_pPlayer,true));
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(50, 12, 0);
    pObj->SetDontDestroy(true);

    pObj = GameObject::Instantiate();
    pObj->AddComponent(new StatusBall(_pPlayer, false));
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(1115, 12, 0);
    pObj->SetDontDestroy(true);

    //LB
    pObj = GameObject::Instantiate();
    pObj->AddComponent(new MouseBtnUI(_pInputHandler, true));
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(190, 90, 0);
    pObj->SetDontDestroy(true);

    //RB
    pObj = GameObject::Instantiate();
    pObj->AddComponent(new MouseBtnUI(_pInputHandler, false));
    pObj->GetTransform()->SetParent(gameObject->GetTransform());
    pObj->GetTransform()->SetLocalPosition(1020, 90, 0);
    pObj->SetDontDestroy(true);
}