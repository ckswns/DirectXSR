#include "pch.h"
#include "InfoBox.h"
#include "Image.h"
#include "GameDataManager.h"
#include "Text.h"
#include "RectTransform.h"
#include "Transform.h"

using namespace ce::UI;

InfoBox::InfoBox(Slot::SLOTTYPE eType)
	: _eType(eType)
{
}

InfoBox::~InfoBox()
{
}

void InfoBox::Awake(void) noexcept
{
	switch (_eType)
	{
	case Slot::SLOTTYPE::HEAD:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("BoneHelm"), sizeof(ITEMDATA));
		break;
	case Slot::SLOTTYPE::BODY:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("HardArmor"), sizeof(ITEMDATA));
		break;
	case Slot::SLOTTYPE::MAINWP:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("GrimWand"), sizeof(ITEMDATA));
		break;
	case Slot::SLOTTYPE::SECONDWP:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("TowerShield"), sizeof(ITEMDATA));
		break;
	case Slot::SLOTTYPE::GLOVES:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("LightGauntlets"), sizeof(ITEMDATA));
		break;
	case Slot::SLOTTYPE::LEGS:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("Greaves"), sizeof(ITEMDATA));
		break;
	case Slot::SLOTTYPE::BELT:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("PlatedBelt"), sizeof(ITEMDATA));
		break;
	case Slot::SLOTTYPE::RING1:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("JordanRing"), sizeof(ITEMDATA));
		break;
	case Slot::SLOTTYPE::RING2:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("NagelRing"), sizeof(ITEMDATA));
		break;
	case Slot::SLOTTYPE::NECKLACE:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("NokozanRelic"), sizeof(ITEMDATA));
		break;
	}

	gameObject->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\ItemInfoBox.png")));
	gameObject->SetSortOrder(200);
	gameObject->SetActive(false);
	gameObject->SetDontDestroy(true);
}

void InfoBox::Start(void) noexcept
{
	D3DXVECTOR3 vpos = gameObject->GetTransform()->GetWorldPosition();
	
	GameObject* obj = GameObject::Instantiate();
	_pTex[0] = static_cast<Text*>(obj->AddComponent(new UI::Text(_data.name, D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
	RectTransform* rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(200);
	rt->SetHeight(30);
	obj->SetSortOrder(300);
	obj->GetTransform()->SetParent(gameObject->GetTransform());

	obj = GameObject::Instantiate();
	obj->GetTransform()->SetParent(gameObject->GetTransform());
	if (_eType == Slot::SLOTTYPE::MAINWP)
	{
		std::string strAttak = "공격력 : ";
		strAttak += std::to_string(_data.damagemin) + "~" + std::to_string(_data.damagemax);
		_pTex[1] = static_cast<Text*>(obj->AddComponent(new UI::Text(strAttak.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
	}
	else if (_eType == Slot::SLOTTYPE::RING1 || _eType == Slot::SLOTTYPE::RING2)
	{
		std::string strAttak = "착용레벨 : ";
		strAttak += std::to_string(_data.needlevel);
		_pTex[1] = static_cast<Text*>(obj->AddComponent(new UI::Text(strAttak.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
	}
	else
	{
		std::string strAttak = "방어력 : ";
		strAttak += std::to_string(_data.defense);
		_pTex[1] = static_cast<Text*>(obj->AddComponent(new UI::Text(strAttak.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
	}
	rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(200);
	rt->SetHeight(30);
	obj->SetSortOrder(300);
	vpos.y += 30.f;
	obj->GetTransform()->SetWorldPosition(vpos);
}

void InfoBox::Update(float) noexcept
{
}

void InfoBox::SetPosition(float x, float y)
{
	gameObject->GetTransform()->SetWorldPosition(x, y, 0);
}

void InfoBox::MissingItem()
{
	gameObject->SetDontDestroy(true);
	gameObject->Destroy();
}

