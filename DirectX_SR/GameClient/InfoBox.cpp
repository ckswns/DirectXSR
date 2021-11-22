#include "pch.h"
#include "InfoBox.h"
#include "Image.h"
#include "GameDataManager.h"
#include "Text.h"
#include "RectTransform.h"
#include "Transform.h"

using namespace ce::UI;
using namespace ce::CE_MATH;

InfoBox::InfoBox(Slot::SLOTTYPE eType, bool isStoreItem)
	: _eType(eType), _bStore(isStoreItem)
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
	case Slot::SLOTTYPE::POTION:
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("Potion"), sizeof(ITEMDATA));
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
	obj->GetTransform()->SetParent(gameObject->GetTransform());
	if (_eType == Slot::SLOTTYPE::RING1 || _eType == Slot::SLOTTYPE::RING2 || _eType == Slot::SLOTTYPE::NECKLACE)
		_pTex[0] = static_cast<Text*>(obj->AddComponent(new UI::Text(_data.name, D3DCOLOR_ARGB(255, 50, 50, 255), DT_CENTER)));
	else
		_pTex[0] = static_cast<Text*>(obj->AddComponent(new UI::Text(_data.name, D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
	RectTransform* rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(200);
	rt->SetHeight(30);
	obj->SetSortOrder(300);
	vpos.y += 10.f;
	obj->GetTransform()->SetWorldPosition(vpos);

	if (_eType != Slot::SLOTTYPE::POTION)
	{
		obj = GameObject::Instantiate();
		obj->GetTransform()->SetParent(gameObject->GetTransform());
		if (_eType == Slot::SLOTTYPE::MAINWP)
		{
			std::string strAttak = "공격력 : ";
			strAttak += std::to_string(_data.damagemin) + "~" + std::to_string(_data.damagemax);
			_pTex[1] = static_cast<Text*>(obj->AddComponent(new UI::Text(strAttak.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
		}
		else if(_eType != Slot::SLOTTYPE::MAINWP && _eType != Slot::SLOTTYPE::RING1 && _eType != Slot::SLOTTYPE::RING2 && _eType != Slot::SLOTTYPE::NECKLACE)
		{
			std::string strDef = "방어력 : ";
			strDef += std::to_string(_data.defense);
			_pTex[1] = static_cast<Text*>(obj->AddComponent(new UI::Text(strDef.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
		}
		rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
		rt->SetWidth(200);
		rt->SetHeight(30);
		obj->SetSortOrder(300);
		vpos.y += 30.f;
		obj->GetTransform()->SetWorldPosition(vpos);

		obj = GameObject::Instantiate();
		obj->GetTransform()->SetParent(gameObject->GetTransform());
		std::string strneed = "착용레벨 : ";
		strneed += std::to_string(_data.needlevel);
		_pTex[2] = static_cast<Text*>(obj->AddComponent(new UI::Text(strneed.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
		rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
		rt->SetWidth(200);
		rt->SetHeight(30);
		obj->SetSortOrder(300);
		vpos.y += 30.f;
		obj->GetTransform()->SetWorldPosition(vpos);

		if (_eType == Slot::SLOTTYPE::RING1 || _eType == Slot::SLOTTYPE::RING2 || _eType == Slot::SLOTTYPE::NECKLACE)
		{
			obj = GameObject::Instantiate();
			obj->GetTransform()->SetParent(gameObject->GetTransform());
			std::string strability;
			switch (_eType)
			{
			case  Slot::SLOTTYPE::RING1:
				strability = "추가 공격력 ";
				strability += std::to_string(_data.ability);
				break;
			case Slot::SLOTTYPE::RING2:
				strability = "추가 방어력 ";
				strability += std::to_string(_data.ability);
				break;
			case Slot::SLOTTYPE::NECKLACE:
				strability = "모든 저항 ";
				strability += std::to_string(_data.ability) + "%";
				break;
			}
			_pTex[3] = static_cast<Text*>(obj->AddComponent(new UI::Text(strability.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
			rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
			rt->SetWidth(200);
			rt->SetHeight(30);
			obj->SetSortOrder(300);
			vpos.y += 60.f;
			obj->GetTransform()->SetWorldPosition(vpos);
		}
	}
	else
	{
		obj = GameObject::Instantiate();
		obj->GetTransform()->SetParent(gameObject->GetTransform());
		int i = ce::CE_MATH::Random(0, 3);
		std::string strability = std::to_string(_data.ability) + "% 즉시회복";
		_pTex[3] = static_cast<Text*>(obj->AddComponent(new UI::Text(strability.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
		rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
		rt->SetWidth(200);
		rt->SetHeight(30);
		obj->SetSortOrder(300);
		vpos.y += 60.f;
		obj->GetTransform()->SetWorldPosition(vpos);
	}
	obj = GameObject::Instantiate();
	obj->GetTransform()->SetParent(gameObject->GetTransform());
	int i = ce::CE_MATH::Random(0, 3);
	std::string strGold;
	if (_bStore)
	{
		strGold = "구매가격: " + std::to_string(_data.buygold) + 'G';
	}
	else
	{
		strGold = "판매가격: " + std::to_string(_data.sellgold) + 'G';
	}
	_pTex[4] = static_cast<Text*>(obj->AddComponent(new UI::Text(strGold.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
	rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(200);
	rt->SetHeight(30);
	obj->SetSortOrder(300);
	vpos.y += 60.f;
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

void InfoBox::SetStoreItem(bool b)
{
	if (_bStore == b) return;

	_bStore = b;
	std::string strGold;
	if (_bStore)
	{
		strGold = "구매가격: " + std::to_string(_data.buygold) + 'G';
	}
	else
	{
		strGold = "판매가격: " + std::to_string(_data.sellgold) + 'G';
	}
	_pTex[4]->SetText(strGold.c_str());
}
