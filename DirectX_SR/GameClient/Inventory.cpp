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

	for (auto& iter : _vecItem)
	{
		if (iter)
		{
			delete iter;
			iter = nullptr;
		}
	}
	_vecItem.clear();

	for (auto& iter : _vecItemslot)
	{
		if (iter.second)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	_vecItemslot.clear();
}
void Inventory::Start(void) noexcept
{
	gameObject = GameObject::Instantiate();
	gameObject->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Inven.png")));
	gameObject->SetSortOrder(0);
	gameObject->GetTransform()->SetWorldPosition(WINCX >> 1, 0, 0);

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
		_vecSlotGroup[i].emplace_back(new Slot((Slot::SLOTTYPE)i));

	//_pTestItem = GameObject::Instantiate();
	//_pTestItem->AddComponent(new TestItem(_pTestItem,Slot::SLOTTYPE::HEAD));
	GameObject* pobj = GameObject::Instantiate();
	ItemSlot* pSlot = new ItemSlot(pobj,Slot::SLOTTYPE::HEAD, 100.f, 100.f);
	//pobj->AddComponent(pSlot);
	_vecItem.emplace_back(pSlot);
	/*_VecItem.emplace_back(pobj);*/

	pobj = GameObject::Instantiate();
	pSlot = new ItemSlot(pobj,Slot::SLOTTYPE::BODY, 100.f, 200.f);
	//pobj->AddComponent(pSlot);
	_vecItem.emplace_back(pSlot);
	//_VecItem.emplace_back(pobj);
}

void Inventory::Update(float) noexcept
{
	if (_bInvenCheck)
	{
		gameObject->SetActive(true);

		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		if (INPUT->GetKeyDown(KEY_LBUTTON))
			_bItemCatchCheck = !_bItemCatchCheck;

		if (_bItemCatchCheck)
		{
			if (ItemCatch(pt))
				ItemMove(pt);
		}
		//else
		//{
		//	ItemDrop(pt);
		//	//if (ItemDrop(pt))
		//	//{

		//	//}
		//}

		if (!_bItemCatchCheck)
		{
			if(_bSlotCheck)
				SettingItem();
		}
	}
	else
		gameObject->SetActive(false);
}

bool Inventory::ItemDrop(POINT pt)
{
	if (_bCatch)
	{
		for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
		{
			auto& iter = _vecSlotGroup[i];

			Slot::SLOTTYPE eSlottype = iter[0]->GetSlotType();
			std::vector<SLOTINFO*> vSlot = iter[0]->GetSlot();
			
			for (size_t t = 0; t < vSlot.size(); ++t)
			{
				if (_pItemSlotInfo->_iFlag & vSlot[t]->_iFlag)
				{
					D3DXVECTOR3 vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };
					_pItem->SetInvenPosition(vpos);
				}
				else if(eSlottype == Slot::SLOTTYPE::NORMAL)
				{
					D3DXVECTOR3 vpos = { (float)vSlot[i]->_tRect.left, (float)vSlot[i]->_tRect.top, 0 };
					_pItem->SetInvenPosition(vpos);
				}
			}
		}
	}
	_bCatch = false;
	return true;
}

bool Inventory::ItemCatch(POINT pt)
{
	for (auto& iter : _vecItem)
	{
		_vecItemslot = iter->GetItemSlot();
		for (auto& src : _vecItemslot)
		{
			if (PtInRect(&(src.second->_tRect), pt))
			{
				_pItem = iter;
				_pItemSlotInfo = src.second;
				_bCatch = true;
				return true;
			}
			else
			{
				_bCatch = false;
				return false;
			}
		}
	}
	return false;
}

void Inventory::ItemMove(POINT pt)
{
	_pItem->setMousePosition(D3DXVECTOR3(pt.x, pt.y, 0));
	_bSlotCheck = true;
}

void Inventory::InvenslotCheck(POINT pt)
{
}

void Inventory::SettingItem()
{
	if (_pItemSlotInfo == nullptr)
		return;

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
	{
		auto& iter = _vecSlotGroup[i];
		
		Slot::SLOTTYPE eSlottype = iter[0]->GetSlotType();
		std::vector<SLOTINFO*> vSlot = iter[0]->GetSlot();

		for (int i = 0; i < (int)(iter[0]->GetSlot().size()) ; ++i)
		{
			RECT rc = {};
			if (IntersectRect(&rc, &vSlot[i]->_tRect, &_pItemSlotInfo->_tRect))
			{
				//Equip
				if (eSlottype == Slot::SLOTTYPE::NORMAL || _pItemSlotInfo->_iFlag & vSlot[i]->_iFlag)
				{
					if (!vSlot[i]->_bSlotCheck)
					{
						if (eSlottype == Slot::SLOTTYPE::NORMAL)
						{
							D3DXVECTOR3 vpos = { (float)vSlot[i]->_tRect.left, (float)vSlot[i]->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
						}
						else
						{
							D3DXVECTOR3 vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
						}
						_bSlotCheck = false;
						SlotCheck(vSlot, _vecItemslot);
						return;
					}
					else
					{
						/*ItemSlotCheck();*/
						_bItemCatchCheck = true;
						return;
					}
				}
				else
				{
					_bItemCatchCheck = true;
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

void Inventory::ItemSlotCheck()
{
	for (auto& iter : _vecItem)
	{
		_vecItemslot = iter->GetItemSlot();
		for (auto& src : _vecItemslot)
		{
			RECT rc;
			if (IntersectRect(&rc ,&src.second->_tRect,&_pItemSlotInfo->_tRect))
			{
				_pItem = iter;
				_pItemSlotInfo = src.second;
				return;
			}
		}
	}
}
