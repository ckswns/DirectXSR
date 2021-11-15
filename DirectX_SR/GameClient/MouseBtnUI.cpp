#include "pch.h"
#include "MouseBtnUI.h"
#include "Transform.h"
#include "Image.h"
#include "Button.h"
#include "InputHandler.h"
using namespace ce::UI;

MouseBtnUI::MouseBtnUI(InputHandler* input, bool isLeft) noexcept
    :_pInputHandler(input), _bLeft(isLeft), _bBtn(false) { __noop;}

void MouseBtnUI::Start(void) noexcept
{
	_pImg = static_cast<Image*>(gameObject->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"))));
	Button<MouseBtnUI>* btn = static_cast<Button<MouseBtnUI>*>(gameObject->AddComponent(new Button<MouseBtnUI>(this)));
	btn->onMouseDown += &MouseBtnUI::BtnClick;
    gameObject->SetSortOrder(1);

    _pBtnAttack = GameObject::Instantiate();
    Image* img = static_cast<Image*>(_pBtnAttack->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"))));
    _pBtnAttack->GetTransform()->SetParent(gameObject->GetTransform());
    btn = static_cast<Button<MouseBtnUI>*>(_pBtnAttack->AddComponent(new Button<MouseBtnUI>(this)));
    btn->onMouseDown += &MouseBtnUI::SetAttack;
    _pBtnAttack->SetActive(false);
    _pBtnAttack->SetSortOrder(2);

    _pBtnRaise = GameObject::Instantiate();
    img = static_cast<Image*>(_pBtnRaise->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\21.png"))));
    _pBtnRaise->GetTransform()->SetParent(gameObject->GetTransform());
    btn = static_cast<Button<MouseBtnUI>*>(_pBtnRaise->AddComponent(new Button<MouseBtnUI>(this)));
    btn->onMouseUp += &MouseBtnUI::SetRaise;
    _pBtnRaise->SetActive(false);
    _pBtnRaise->SetSortOrder(2);

    _pBtnSpear = GameObject::Instantiate();
    img = static_cast<Image*>(_pBtnSpear->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\6.png"))));
    _pBtnSpear->GetTransform()->SetParent(gameObject->GetTransform());
    btn = static_cast<Button<MouseBtnUI>*>(_pBtnSpear->AddComponent(new Button<MouseBtnUI>(this)));
    btn->onMouseUp += &MouseBtnUI::SetSpear;
    _pBtnSpear->SetActive(false);
    _pBtnSpear->SetSortOrder(2);

    _pBtnPoison = GameObject::Instantiate();
    img = static_cast<Image*>(_pBtnPoison->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\8.png"))));
    _pBtnPoison->GetTransform()->SetParent(gameObject->GetTransform());
    btn = static_cast<Button<MouseBtnUI>*>(_pBtnPoison->AddComponent(new Button<MouseBtnUI>(this)));
    btn->onMouseUp += &MouseBtnUI::SetPoison;
    _pBtnPoison->SetActive(false);
    _pBtnPoison->SetSortOrder(2);

    if (!_bLeft)
    {
        _pBtnAttack->GetTransform()->SetLocalPosition(0, -47, 0);
        _pBtnRaise->GetTransform()->SetLocalPosition(-49, -47, 0);
        _pBtnSpear->GetTransform()->SetLocalPosition(-49, -94, 0);
        _pBtnPoison->GetTransform()->SetLocalPosition(0, -94, 0);
    }
    else
    {
        _pBtnAttack->GetTransform()->SetLocalPosition(0, -47, 0);
        _pBtnRaise->GetTransform()->SetLocalPosition(49, -47, 0);
        _pBtnSpear->GetTransform()->SetLocalPosition(49, -94, 0);
        _pBtnPoison->GetTransform()->SetLocalPosition(0, -94, 0);
    }

}

void MouseBtnUI::BtnClick()
{
    if (!_bBtn)
    {
        _bBtn = true;
        _pBtnAttack->SetActive(true);
        _pBtnRaise->SetActive(true);
        _pBtnSpear->SetActive(true);
        _pBtnPoison->SetActive(true);
    }
    else
    {
        _bBtn = false;
        _pBtnAttack->SetActive(false);
        _pBtnRaise->SetActive(false);
        _pBtnSpear->SetActive(false);
        _pBtnPoison->SetActive(false);
    }
}

void MouseBtnUI::SetAttack()
{
    BtnClick();
    _pImg->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\30.png"));
    _pInputHandler->SetMouseBtn(_bLeft, SKILL_END);
}

void MouseBtnUI::SetRaise()
{
    BtnClick();
    _pImg->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\21.png"));
    _pInputHandler->SetMouseBtn(_bLeft, SKILL_ID::RAISE_SKELETON);
}

void MouseBtnUI::SetSpear()
{
    BtnClick();
    _pImg->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\6.png"));
    _pInputHandler->SetMouseBtn(_bLeft, SKILL_ID::BONE_SPEAR);
}

void MouseBtnUI::SetPoison()
{
    BtnClick();
    _pImg->SetTexture(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Skill\\8.png"));
    _pInputHandler->SetMouseBtn(_bLeft, SKILL_ID::POISON_NOVA);
}
