#include "pch.h"
#include "Inventory.h"
#include "GameObject.h"
#include "Image.h"
#include "Transform.h"
#include "TestItem.h"
#include "SpriteRenderer.h"

using namespace ce::UI;

Inventory::Inventory() noexcept
{
}
Inventory::~Inventory() noexcept
{
	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
	{
		for (auto& iter : _vecSlotGroup[i])
		{
			if (iter)
			{
				delete iter;
				iter = nullptr;
			}
			_vecSlotGroup[i].clear();
		}
	}
}
void Inventory::Start(void) noexcept
{
	Image* Inven = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Inven.png"));
	_pInven = GameObject::Instantiate();
	_pInven->AddComponent(Inven);
	_pInven->SetSortOrder(0);
	_pInven->GetTransform()->SetWorldPosition(WINCX >> 1, 0, 0);

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
		_vecSlotGroup[i].emplace_back(new Slot((Slot::SLOTTYPE)i));

	_pTestItem = GameObject::Instantiate();
	_pTestItem->AddComponent(new TestItem(_pTestItem,Slot::SLOTTYPE::HEAD));
}

void Inventory::Update(float) noexcept
{
	if (_bInvenCheck)
	{
		_pInven->SetActive(true);
		_pTestItem->SetActive(true);

		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		if (INPUT->GetKeyDown(KEY_LBUTTON))
		{
			if (ItemClicked(pt))
				_bItemMoveCheck = !_bItemMoveCheck;
		}

		if (_bItemMoveCheck)
			ItemMove(pt);

		if (!_bItemMoveCheck)
			 SettingItem();
	}
	else
	{
		_pInven->SetActive(false);
		_pTestItem->SetActive(false);
	}
}

bool Inventory::ItemClicked(POINT pt) 
{
	std::vector<std::pair<GameObject*, SLOTINFO*>> vslot = static_cast<TestItem*>(_pTestItem->GetComponent(COMPONENT_ID::BEHAVIOUR))->GetItemSlot();
	for (auto& iter : vslot)
	{
		if (PtInRect(&(iter.second->_tRect), pt))
			return true;
	}
	return false;
}

void Inventory::ItemMove(POINT pt)
{
	static_cast<TestItem*>(_pTestItem->GetComponent(COMPONENT_ID::BEHAVIOUR))->setTestPosition(D3DXVECTOR3(pt.x, pt.y, 0)); // 수정해야함
	_bSlotCheck = true;
}

void Inventory::SettingItem()
{
	std::vector<std::pair<GameObject*,SLOTINFO*>> vItemSlot = static_cast<TestItem*>(_pTestItem->GetComponent(COMPONENT_ID::BEHAVIOUR))->GetItemSlot();
	Slot::SLOTTYPE eItmetype = static_cast<TestItem*>(_pTestItem->GetComponent(COMPONENT_ID::BEHAVIOUR))->GetItemType();

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
	{
		auto& iter = _vecSlotGroup[i];

		Slot::SLOTTYPE eSlottype = iter[0]->GetSlotType();
		std::vector<SLOTINFO*> vSlot = iter[0]->GetSlot();

		for (int i = 0; i < (int)(iter[0]->GetSlot().size()) ; ++i)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &vSlot[i]->_tRect, &vItemSlot[0].second->_tRect))
			{
				if (eItmetype == eSlottype || eSlottype == Slot::SLOTTYPE::NORMAL)
				{
					if (!vSlot[i]->_bSlotCheck)
					{
						D3DXVECTOR3 vpos = { (float)vSlot[i]->_tRect.left, (float)vSlot[i]->_tRect.top, 0 };
						static_cast<TestItem*>(_pTestItem->GetComponent(COMPONENT_ID::BEHAVIOUR))->SetPosition(vpos);
						_bSlotCheck = false;
						SlotCheck(vSlot,vItemSlot);
						return;
					}
					else
					{
						_bItemMoveCheck = false;
						return;
					}
				}
				else
				{
					_bItemMoveCheck = true;
					return;
				}
			}
		}
	}
}

void Inventory::SlotCheck(std::vector<SLOTINFO*> pSlot, std::vector<std::pair<GameObject*,SLOTINFO*>> pitemSlot)
{
	for (auto& pDes : pSlot)
	{
		for (auto& pSrc : pitemSlot)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &pDes->_tRect, &pSrc.second->_tRect))
				pDes->_bSlotCheck = true;
			else
				pDes->_bSlotCheck = false;
		}
	}
}
