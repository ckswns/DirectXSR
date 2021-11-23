#include "pch.h"
#include "StatusBall.h"
#include "Transform.h"
#include "RectTransform.h"
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
   gameObject->SetSortOrder(3);

   _text = new Text("/",D3DXCOLOR(0.5f,0.5f,0.5f,1));
   _txtObj = GameObject::Instantiate();
   _txtObj->AddComponent(_text);
   RectTransform* rt = _txtObj->GetComponent<RectTransform>(COMPONENT_ID::RECT_TRANSFORM);
   rt->SetPivot(D3DXVECTOR2(0.5f, 0.5f));

   _txtObj->GetTransform()->SetParent(GetTransform());
   _txtObj->GetTransform()->SetLocalPosition(0, -30, 0);
   _txtObj->SetDontDestroy(true);
   _txtObj->SetSortOrder(5);
   _txtObj->SetActive(false);

}

void StatusBall::Update(float fElapsedTime) noexcept
{
    if (_bHp)
    {
        _fPer = _pPlayer->GetHPPer();
    }
    else
    {
        _fPer = _pPlayer->GetMPPer();
    }
    _img->SetFillAmount(_fPer);
}

void StatusBall::OnMouseLeave(void) noexcept
{
    _txtObj->SetActive(false);
}

void StatusBall::OnMouseOver(void) noexcept
{
    float max;
    if(_bHp)
        max= _pPlayer->GetMaxHP();
    else
        max = _pPlayer->GetMaxMP();

    float cur = max * _fPer;

    char str[256];
    sprintf_s(str, 256, "%.f/%.f", cur, max);

    _text->SetText(str);
    _txtObj->SetActive(true);
}
