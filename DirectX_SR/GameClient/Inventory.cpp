#include "pch.h"
#include "Inventory.h"
#include "GameObject.h"
#include "pch.h"
#include "Inventory.h"
#include "GameObject.h"
#include "Image.h"
#include "Transform.h"
#include "TestItem.h"
#include "SpriteRenderer.h"

using namespace ce::UI;
using namespace ce::CE_MATH;

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
#ifdef _DEBUG
	for (auto& iter : _vecItemslot)
	{
		if (iter.second)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
#else
	for (auto& iter : _vecItemslot)
	{
		if (iter)
		{
			delete iter;
			iter = nullptr;
		}
	}
#endif // _DEBUG
	_vecItemslot.clear();

	if (_pExamine)
	{
		delete _pExamine;
		_pExamine = nullptr;
	}
}

void Inventory::Start(void) noexcept
{
	gameObject = GameObject::Instantiate();
	gameObject->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Inven.png")));
	gameObject->SetSortOrder(0);
	gameObject->GetTransform()->SetWorldPosition(WINCX >> 1, 0, 0);

	_pExamine = new Examine();

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
		_vecSlotGroup[i].emplace_back(new Slot((Slot::SLOTTYPE)i));

}

void Inventory::Update(float) noexcept
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (INPUT->GetKeyDown('o') || INPUT->GetKeyDown('O')) // L버튼이 잘 안먹어서 바꿔놓은거.
	{
		if (!_vecItem.empty())
		{
			_bItemCatchCheck = !_bItemCatchCheck;
			if (_bItemCatchCheck)
				ItemCatch(pt);
			else
				ItemDropAtMouse(pt);/*ItemDrop(pt);*/
		}
	}

	if (_bItemCatchCheck)
	{
		ItemMove();
	}

#ifdef _DEBUG
	if (INPUT->GetKeyDown('l') || INPUT->GetKeyDown('L'))
	{

		INVENITEMINFO* pInvenInfo = new INVENITEMINFO();

		int i = ce::CE_MATH::Random(1, 12);
		pInvenInfo->_eSlotType = i;

		GetItem(pInvenInfo);
	}
#endif // _DEBUG
}

void Inventory::ItemCatch(POINT pt)
{
	_pItem = nullptr;
	_pItemSlotInfo = nullptr;

	for (size_t t = 0; t < _vecItem.size(); ++t)
	{
		_vecItemslot = _vecItem[t].second->GetItemSlot();
		RECT rc = _vecItem[t].second->GetItemRect();

		if (PtInRect(&rc, pt))
		{
			_pItem = _vecItem[t].second;
#ifdef _DEBUG
			_pItemSlotInfo = _vecItemslot[0].second;
#else
			_pItemSlotInfo = _vecItemslot[0];
#endif // _DEBUG
			ItemCatchExamine(pt);
			return;
		}
	}
}

void Inventory::ItemCatchExamine(POINT pt)
{
	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
	{
		auto& iter = _vecSlotGroup[i];

		Slot::SLOTTYPE eSlottype = iter[0]->GetSlotType();
		std::vector<SLOTINFO*> vSlot = iter[0]->GetSlot();

		RECT	MaxRc = iter[0]->GetRect();

		if (PtInRect(&MaxRc, pt))
		{
			SLOTINFO* pItem = _pItem->GetItemInfo(0);
			ReCatchtoExamine(vSlot, pItem->_vPos);
			return;
		}
	}
}

void Inventory::ReCatchtoExamine(std::vector<SLOTINFO*> InvenSlot, D3DXVECTOR3 vpos) // 수정해야함
{
	int InvenCntX = InvenSlot[0]->_iSlotCntX;
	int InvenCntY = InvenSlot[0]->_iSlotCntY;

	int ItemCntX = _pItemSlotInfo->_iSlotCntX;
	int ItemCntY = _pItemSlotInfo->_iSlotCntY;

	int ChageIndex = 0;
	int Index = 0;
	int MaxIndex = (InvenCntX * InvenCntY) - 1;
	for (int i = 0; i < InvenCntY; ++i)
	{
		for (int j = 0; j < InvenCntX; ++j)
		{
			Index = i * InvenCntX + j;
			if (InvenSlot[Index]->_vPos == vpos)
			{
				ChageIndex = InvenSlot[Index]->_iIndex;
				switch (ItemCntX * ItemCntY)
				{
				case 1:
					if (MaxIndex >= Index)
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						return;
					}
					return;
				case 2:
					if (MaxIndex >= Index && MaxIndex >= (Index + 1))
					{
						if (MaxIndex >= Index && MaxIndex >= (Index + 1))
						{
							InvenSlot[ChageIndex]->_bSlotCheck = false;
							InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
							return;
						}
						return;
					}
					return;
				case 3:
					InvenSlot[ChageIndex]->_bSlotCheck = false;
					InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
					InvenSlot[ChageIndex + (InvenCntX * 2)]->_bSlotCheck = false;
					return;
				case 4:
					if (MaxIndex >= Index && MaxIndex >= Index + 1 && MaxIndex >= Index + InvenCntX && MaxIndex >= Index + InvenCntX + 1)
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX + 1]->_bSlotCheck = false;
						return;
					}
					return;
				case 6:
					if (MaxIndex >= Index && MaxIndex >= Index + 1 && MaxIndex >= Index + InvenCntX && MaxIndex >= Index + InvenCntX + 1
						&& MaxIndex >= Index + (InvenCntX * 2) && MaxIndex >= Index + (InvenCntX * 2) + 1)
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX + 1]->_bSlotCheck = false;
						InvenSlot[ChageIndex + (InvenCntX * 2)]->_bSlotCheck = false;
						InvenSlot[ChageIndex + (InvenCntX * 2) + 1]->_bSlotCheck = false;
						return;
					}
					return;
				}
			}
		}
	}
}

void Inventory::GetItem(INVENITEMINFO* pInvenInfo)
{
	GameObject* pobj = GameObject::Instantiate();
	float fx = UnsignedRandomf(400.f);
	float fy = UnsignedRandomf(700.f);
	ItemSlot* pSlot = new ItemSlot((Slot::SLOTTYPE)pInvenInfo->_eSlotType,fx,fy);
	pobj->AddComponent(pSlot);
	_vecItem.emplace_back(pInvenInfo,pSlot);
	_pItem = pSlot;
#ifdef _DEBUG
	_pItemSlotInfo = pSlot->GetItemSlot()[0].second;
#else
	_pItemSlotInfo = pSlot->GetItemInfo(0);
#endif // _DEBUG

	ItemEating();
}

void Inventory::ItemEating() // 이름 변경 해야함
{
	if (_pItem == nullptr || _pItemSlotInfo == nullptr)
		return;

	SLOTINFO* pslot = DropAtEtingExamine(_vecSlotGroup[0][0]->GetSlot()); // 아이템이 들어갈 칸이있는지 검사
	if (pslot == nullptr)
		return;

	D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
	_pItem->SetInvenPosition(vpos);
	_bItemCatchCheck = false;
}

SLOTINFO* Inventory::DropAtEtingExamine(std::vector<SLOTINFO*> InvenSlot) // 수정 해야함.
{
	int ItemCntX = _pItemSlotInfo->_iSlotCntX;
	int ItemCntY = _pItemSlotInfo->_iSlotCntY;

	switch (ItemCntX * ItemCntY)
	{
	case 1:
		return _pExamine->EatingExamine1X1(InvenSlot);
	case 2:
		return _pExamine->EatingExamine2X1(InvenSlot);
	case 3:
		return _pExamine->EatingExamine1X3(InvenSlot);
	case 4:
		return _pExamine->EatingExamine2X2(InvenSlot);
	case 6:
		return _pExamine->EatingExamine2X3(InvenSlot);
	}

	return nullptr;
}

void Inventory::ItemDropAtMouse(POINT pt)
{
	if (_pItemSlotInfo == nullptr)
		return;

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
	{
		auto& iter = _vecSlotGroup[i];

		Slot::SLOTTYPE eSlottype = iter[0]->GetSlotType();
		Slot::SLOTTYPE eItemSlotType = _pItem->GetSlotType();
		std::vector<SLOTINFO*> vSlot = iter[0]->GetSlot();
		
		RECT	MaxRc = iter[0]->GetRect();

		if (PtInRect(&MaxRc, pt))
		{
			for (int i = 0; i < (int)vSlot.size(); ++i)
			{
				if (PtInRect(&vSlot[i]->_tRect, pt))
				{
					if (vSlot[i]->_iFlag & _pItemSlotInfo->_iFlag && eItemSlotType != Slot::SLOTTYPE::POTION)
					{
						// 아이템 위치 변경 시켜주기전에 해당 슬롯의 칸이 비여있는지 확인해야함.
						SLOTINFO* pslot = DropAtMouseExamine(vSlot,pt); // 드랍했을때 아이템이 들어갈 칸이있는지 검사
						if (pslot == nullptr)
						{
							_bItemCatchCheck = true;
							return;
						}

						if (_bSwitchingcheck)
						{
							D3DXVECTOR3 vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };
							_pPriveItem->SetInvenPosition(vpos);
							_bItemCatchCheck = true;
							_bSwitchingcheck = false;
							_pItem = _pPriveItem;
							_pPriveItem = nullptr;
						}
						else
						{
							D3DXVECTOR3 vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
						}
						return;
					}
					else if (eSlottype == Slot::SLOTTYPE::NORMAL)
					{
						SLOTINFO* pslot = DropAtMouseExamine(vSlot, pt); // 드랍했을때 아이템이 들어갈 칸이있는지 검사
						if (pslot == nullptr)
						{
							_bItemCatchCheck = true;
							return;
						}
						D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
						_pItem->SetInvenPosition(vpos);
						return;
					}
				}
			}
		}
	}

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
	{
		auto& iter = _vecSlotGroup[i];
		RECT	MaxRc = iter[0]->GetRect();
		if (!PtInRect(&MaxRc, pt))
		{
			float fx = UnsignedRandomf(400.f);
			float fy = UnsignedRandomf(700.f);
			D3DXVECTOR3 vPos = { fx, fy, 0.f };
			_pItem->SetInvenPosition(vPos);
			_bItemCatchCheck = false;
			return;
		}
		else
		{
			_bItemCatchCheck = true; // 중단점 확인해야함.
			return;
		}
	}
}

SLOTINFO* Inventory::DropAtMouseExamine(std::vector<SLOTINFO*> InvenSlot, POINT pt)
{
	int ItemCntX = _pItemSlotInfo->_iSlotCntX;
	int ItemCntY = _pItemSlotInfo->_iSlotCntY;
	SLOTINFO* pSlotinfo = nullptr;
	switch (ItemCntX * ItemCntY)
	{
	case 1:
		pSlotinfo = _pExamine->MouseExamine1X1(InvenSlot, pt);
		/*if (pSlotinfo == nullptr)
			return ItemSwitching(pt);
		else*/
			return pSlotinfo;
		break;
	case 2:
		return _pExamine->MouseExamine2X1(InvenSlot,pt);
		break;
	case 3:
		return _pExamine->MouseExamine1X3(InvenSlot,pt);
		break;
	case 4:
		return _pExamine->MouseExamine2X2(InvenSlot,pt);
		break;
	case 6:
		return _pExamine->MouseExamine2X3(InvenSlot,pt);
		break;
	}
	return nullptr;
}

void Inventory::ItemMove()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (_pPriveItem != nullptr)
	{
		_pPriveItem->setMousePosition(D3DXVECTOR3(pt.x, pt.y, 0));
	}
	else if (_pItem != nullptr)
	{
		_pItem->setMousePosition(D3DXVECTOR3(pt.x, pt.y, 0));
		return;
	}
}

SLOTINFO* Inventory::ItemSwitching(POINT pt) // 스위칭 수정해야함.
{
	//RECT rc = {};
	//if (_pItemSlotInfo != nullptr)
	//{
	//	for (size_t t = 0; t < _vecItem.size(); ++t)
	//	{
	//		for (size_t s = 0; s < _vecItem[t].second->GetItemSlot().size(); ++s)
	//		{
	//			if (IntersectRect(&rc, &_pItemSlotInfo->_tRect, &_vecItem[t].second->GetItemSlot()[s].second->_tRect));
	//			{
	//				_pPriveItem = _vecItem[t].second;
	//				_bSwitchingcheck = true;
	//				return _vecItem[t].second->GetItemSlot()[0].second;
	//			}
	//		}
	//	}
	//}
	return nullptr;
}