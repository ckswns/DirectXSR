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
		memcpy(&_data, &GAMEDATAMANAGER->GetItemData("Gauntlets"), sizeof(ITEMDATA));
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
	RectTransform* rt = static_cast<RectTransform*>(gameObject->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetInteractive(false);
}

void InfoBox::Start(void) noexcept
{
	D3DXVECTOR3 vpos = gameObject->GetTransform()->GetWorldPosition();
	_pTextObject[0] = GameObject::Instantiate();
	_pTextObject[0]->GetTransform()->SetParent(gameObject->GetTransform());
	_pTextObject[0]->SetDontDestroy(true);
	if (_eType == Slot::SLOTTYPE::RING1 || _eType == Slot::SLOTTYPE::RING2 || _eType == Slot::SLOTTYPE::NECKLACE)
		_pTex[0] = static_cast<Text*>(_pTextObject[0]->AddComponent(new UI::Text(_data.name, D3DCOLOR_ARGB(255, 50, 50, 255), DT_CENTER)));
	else
		_pTex[0] = static_cast<Text*>(_pTextObject[0]->AddComponent(new UI::Text(_data.name, D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
	RectTransform* rt = static_cast<RectTransform*>(_pTextObject[0]->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(200);
	rt->SetHeight(30);
	_pTextObject[0]->SetSortOrder(300);
	vpos.y += 10.f;
	_pTextObject[0]->GetTransform()->SetWorldPosition(vpos);

	if (_eType != Slot::SLOTTYPE::POTION)
	{
		_pTextObject[1] = GameObject::Instantiate();
		_pTextObject[1]->GetTransform()->SetParent(gameObject->GetTransform());
		_pTextObject[1]->SetDontDestroy(true);
		if (_eType == Slot::SLOTTYPE::MAINWP)
		{
			std::string strAttak = "?????? : ";
			strAttak += std::to_string(_data.damagemin) + "~" + std::to_string(_data.damagemax);
			_pTex[1] = static_cast<Text*>(_pTextObject[1]->AddComponent(new UI::Text(strAttak.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
		}
		else if(_eType != Slot::SLOTTYPE::RING1 && _eType != Slot::SLOTTYPE::RING2 && _eType != Slot::SLOTTYPE::NECKLACE)
		{
			std::string strDef = "?????? : ";
			strDef += std::to_string(_data.defense);
			_pTex[1] = static_cast<Text*>(_pTextObject[1]->AddComponent(new UI::Text(strDef.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
		}
		rt = static_cast<RectTransform*>(_pTextObject[1]->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
		if (rt != nullptr)
		{
			rt->SetWidth(200);
			rt->SetHeight(30);
			_pTextObject[1]->SetSortOrder(300);
			vpos.y += 30.f;
			_pTextObject[1]->GetTransform()->SetWorldPosition(vpos);

			_pTextObject[5] = GameObject::Instantiate();
			_pTextObject[5]->GetTransform()->SetParent(gameObject->GetTransform());
			_pTextObject[5]->SetDontDestroy(true);
			std::string strMaxhp = "???????? +";
			strMaxhp += std::to_string(_data.iMaxhp);
			_pTex[4] = static_cast<Text*>(_pTextObject[5]->AddComponent(new UI::Text(strMaxhp.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
			rt = static_cast<RectTransform*>(_pTextObject[5]->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
			rt->SetWidth(200);
			rt->SetHeight(30);
			_pTextObject[5]->SetSortOrder(300);
			vpos.y += 30.f;
			_pTextObject[5]->GetTransform()->SetWorldPosition(vpos);
		}

		_pTextObject[2] = GameObject::Instantiate();
		_pTextObject[2]->GetTransform()->SetParent(gameObject->GetTransform());
		_pTextObject[2]->SetDontDestroy(true);
		std::string strneed = "???????? : ";
		strneed += std::to_string(_data.needlevel);
		_pTex[2] = static_cast<Text*>(_pTextObject[2]->AddComponent(new UI::Text(strneed.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
		rt = static_cast<RectTransform*>(_pTextObject[2]->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
		rt->SetWidth(200);
		rt->SetHeight(30);
		_pTextObject[2]->SetSortOrder(300);
		vpos.y += 30.f;
		_pTextObject[2]->GetTransform()->SetWorldPosition(vpos);

		if (_eType == Slot::SLOTTYPE::RING1 || _eType == Slot::SLOTTYPE::RING2 || _eType == Slot::SLOTTYPE::NECKLACE)
		{
			_pTextObject[3] = GameObject::Instantiate();
			_pTextObject[3]->GetTransform()->SetParent(gameObject->GetTransform());
			_pTextObject[3]->SetDontDestroy(true);
			std::string strability;
			switch (_eType)
			{
			case  Slot::SLOTTYPE::RING1:
				strability = "???? ?????? ";
				strability += std::to_string(_data.ability);
				break;
			case Slot::SLOTTYPE::RING2:
				strability = "???? ?????? ";
				strability += std::to_string(_data.ability);
				break;
			case Slot::SLOTTYPE::NECKLACE:
				strability = "???? ???? ";
				strability += std::to_string(_data.ability) + "%";
				break;
			}
			_pTex[3] = static_cast<Text*>(_pTextObject[3]->AddComponent(new UI::Text(strability.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
			rt = static_cast<RectTransform*>(_pTextObject[3]->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
			rt->SetWidth(200);
			rt->SetHeight(30);
			_pTextObject[3]->SetSortOrder(300);
			vpos.y += 60.f;
			_pTextObject[3]->GetTransform()->SetWorldPosition(vpos);
		}
	}
	else
	{
		_pTextObject[3] = GameObject::Instantiate();
		_pTextObject[3]->GetTransform()->SetParent(gameObject->GetTransform());
		_pTextObject[3]->SetDontDestroy(true);
		int i = ce::CE_MATH::Random(0, 3);
		std::string strability = std::to_string(_data.ability) + "% ????????";
		_pTex[3] = static_cast<Text*>(_pTextObject[3]->AddComponent(new UI::Text(strability.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
		rt = static_cast<RectTransform*>(_pTextObject[3]->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
		rt->SetWidth(200);
		rt->SetHeight(30);
		_pTextObject[3]->SetSortOrder(300);
		vpos.y += 60.f;
		_pTextObject[3]->GetTransform()->SetWorldPosition(vpos);
	}
	_pTextObject[4] = GameObject::Instantiate();
	_pTextObject[4]->GetTransform()->SetParent(gameObject->GetTransform());
	_pTextObject[4]->SetDontDestroy(true);
	int i = ce::CE_MATH::Random(0, 3);
	std::string strGold;
	if (_bStore)
	{
		strGold = "????????: " + std::to_string(_data.buygold) + 'G';
	}
	else
	{
		strGold = "????????: " + std::to_string(_data.sellgold) + 'G';
	}
	_pTex[4] = static_cast<Text*>(_pTextObject[4]->AddComponent(new UI::Text(strGold.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER)));
	rt = static_cast<RectTransform*>(_pTextObject[4]->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(200);
	rt->SetHeight(30);
	_pTextObject[4]->SetSortOrder(300);
	vpos.y += 60.f;
	_pTextObject[4]->GetTransform()->SetWorldPosition(vpos);
	rt->SetInteractive(false);
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
	gameObject->SetDontDestroy(false);
	gameObject->Destroy();
	for (int i = 0; i < 6; ++i)
	{
		if (_pTextObject[i] != nullptr)
		{
			_pTextObject[i]->SetDontDestroy(false);
			_pTextObject[i]->Destroy();
		}
	}
}

void InfoBox::SetStoreItem(bool b)
{
	if (_bStore == b) return;

	_bStore = b;
	std::string strGold;
	if (_bStore)
	{
		strGold = "????????: " + std::to_string(_data.buygold) + 'G';
	}
	else
	{
		strGold = "????????: " + std::to_string(_data.sellgold) + 'G';
	}
	_pTex[4]->SetText(strGold.c_str());
}

void InfoBox::OnDestroy(void) noexcept
{
	gameObject->SetDontDestroy(false);
	gameObject->Destroy();
	for (int i = 0; i < 6; ++i)
	{
		if (_pTextObject[i] != nullptr)
		{
			_pTextObject[i]->SetDontDestroy(false);
			_pTextObject[i]->Destroy();
		}
	}
}
