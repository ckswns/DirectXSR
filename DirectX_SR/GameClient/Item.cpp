#include "pch.h"
#include "Item.h"
#include "Text.h"
#include "Transform.h"
#include "RectTransform.h"
void Item::Start(void) noexcept
{
//	_pTxtName = GameObject::Instantiate();
//	_pTxtName->AddComponent(new UI::Text(_tInvenItem._strName.c_str(), D3DCOLOR_ARGB(255,255,0, 0)));
////	UI::RectTransform* rt = static_cast<UI::RectTransform*>(_pTxtName->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
////	rt->SetWidth(100);
////	rt->SetHeight(100);
//	_pTxtName->GetTransform()->SetParent(gameObject->GetTransform());
//	_pTxtName->GetTransform()->SetWorldPosition(2,2,2);
////	_pTxtName->SetActive(false);
//	_bLook = false;
}
void Item::Update(float) noexcept
{
	/*if (INPUT->GetKeyStay('X'))
	{
		_bLook = true;
		_pTxtName->SetActive(true);
	}
	else if (_bLook)
	{
		_bLook = false;
		_pTxtName->SetActive(false);
	}*/

}
