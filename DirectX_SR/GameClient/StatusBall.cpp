#include "pch.h"
#include "StatusBall.h"
#include "Transform.h"
#include "Image.h"
#include "Text.h"
#include "Player.h"
using namespace ce::UI;

StatusBall::StatusBall(Player* player, bool isHP) noexcept
	:_pPlayer(player), _bHp(isHP) {}

void StatusBall::Start(void) noexcept
{
    if (_bHp)
    {
        _img = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\HPBall.png"));
    }
    else
    {
        _img = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\MPBall.png"));
    }
    _img->SetFillType(Image::FillType::VERTICAL);
    gameObject->AddComponent(_img);

   //if (_bHp) 
   //{
   //    GetTransform()->SetLocalPosition(50, 12, 0);
   //}
   //else
   //{
   //    GetTransform()->SetLocalPosition(1115, 12, 0);
   //}
   gameObject->SetSortOrder(3);

   _text = new Text("/");
   _txtObj = GameObject::Instantiate();
   _txtObj->AddComponent(_text);
   _txtObj->GetTransform()->SetParent(GetTransform());
   _txtObj->GetTransform()->SetLocalPosition(100, 300, 0);
   _txtObj->SetSortOrder(5);
   _txtObj->SetActive(false);

}

void StatusBall::Update(float fElapsedTime) noexcept
{
    if (_bHp)
    {
        _img->SetFillAmount(_pPlayer->GetHPPer());
    }
    else
        _img->SetFillAmount(_pPlayer->GetMPPer());
}

void StatusBall::OnMouseLeave(void) noexcept
{
    _txtObj->SetActive(false);
}

void StatusBall::OnMouseOver(void) noexcept
{
    _txtObj->SetActive(true);
}
