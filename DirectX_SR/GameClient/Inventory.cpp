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

	GameObject* pobj = GameObject::Instantiate();
	ItemSlot* pSlot = new ItemSlot(pobj, Slot::SLOTTYPE::HEAD, 100.f, 100.f);
	_vecItem.emplace_back(pSlot);

	pobj = GameObject::Instantiate();
	pSlot = new ItemSlot(pobj, Slot::SLOTTYPE::BODY, 100.f, 200.f);
	_vecItem.emplace_back(pSlot);

	pobj = GameObject::Instantiate();
	pSlot = new ItemSlot(pobj, Slot::SLOTTYPE::MAINWP, 100.f, 300.f);
	_vecItem.emplace_back(pSlot);

	pobj = GameObject::Instantiate();
	pSlot = new ItemSlot(pobj, Slot::SLOTTYPE::RING1, 100.f, 400.f);
	_vecItem.emplace_back(pSlot);

	pobj = GameObject::Instantiate();
	pSlot = new ItemSlot(pobj, Slot::SLOTTYPE::HEAD, 100.f, 500.f);
	_vecItem.emplace_back(pSlot);
}

void Inventory::Update(float) noexcept
{
	if (INPUT->GetKeyDown('o') || INPUT->GetKeyDown('O')) // 키다운 이슈
	{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		_bItemCatchCheck = !_bItemCatchCheck;

		if (_bItemCatchCheck)
			ItemCatch(pt);
		else
			ItemDrop(pt);
	}

	if (_bItemCatchCheck)
		ItemMove();
}

void Inventory::ItemCatch(POINT pt)
{
	_pItem = nullptr;
	_pItemSlotInfo = nullptr;
	for (auto& iter : _vecItem)
	{
		_vecItemslot = iter->GetItemSlot();
		RECT rc = iter->GetItemRect();
		if (PtInRect(&rc, pt))
		{
			_pItem = iter;
			_pItemSlotInfo = _vecItemslot[0].second;
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
			CatchtoExamine(vSlot, pItem->_vPos);
			return;
		}
	}
}

void Inventory::ItemMove()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (_pItem != nullptr)
		_pItem->setMousePosition(D3DXVECTOR3(pt.x, pt.y, 0));

	//_bSlotCheck = true;
}

void Inventory::ItemDrop(POINT pt) // 이름 변경 해야함
{
	if (_pItemSlotInfo == nullptr)
		return;

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
	{
		auto& iter = _vecSlotGroup[i];

		Slot::SLOTTYPE eSlottype = iter[0]->GetSlotType();
		std::vector<SLOTINFO*> vSlot = iter[0]->GetSlot();

		RECT	MaxRc = iter[0]->GetRect();

		if (PtInRect(&MaxRc, pt))
		{
			for (int i = 0; i < (int)vSlot.size(); ++i)
			{
				if (vSlot[i]->_iFlag & _pItemSlotInfo->_iFlag || eSlottype == Slot::SLOTTYPE::NORMAL)
				{
					if (eSlottype == Slot::SLOTTYPE::NORMAL)
					{
						// 아이템 위치 변경 시켜주기전에 해당 슬롯의 칸이 비여있는지 확인해야함.

						SLOTINFO* pslot = ItemExamine(vSlot); // 드랍했을때 아이템이 들어갈 칸이있는지 검사
						if (pslot == nullptr)
							return;

						D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
						_pItem->SetInvenPosition(vpos);
						return;
					}
					else
					{
						SLOTINFO* pslot = ItemExamine(vSlot); // 드랍했을때 아이템이 들어갈 칸이있는지 검사
						if (pslot == nullptr)
							return;

						D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
						//D3DXVECTOR3 vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };
						_pItem->SetInvenPosition(vpos);
						return;
					}
				}
			}
		}
	}
	_bItemCatchCheck = true;
}

void Inventory::ItemDroponMouse(POINT pt)
{
	if (_pItemSlotInfo == nullptr)
		return;

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
	{
		auto& iter = _vecSlotGroup[i];

		Slot::SLOTTYPE eSlottype = iter[0]->GetSlotType();
		std::vector<SLOTINFO*> vSlot = iter[0]->GetSlot();

		RECT	MaxRc = iter[0]->GetRect();

		if (PtInRect(&MaxRc, pt))
		{
			for (int i = 0; i < (int)vSlot.size(); ++i)
			{
				if (vSlot[i]->_iFlag & _pItemSlotInfo->_iFlag || eSlottype == Slot::SLOTTYPE::NORMAL)
				{
					if (eSlottype == Slot::SLOTTYPE::NORMAL)
					{
						// 아이템 위치 변경 시켜주기전에 해당 슬롯의 칸이 비여있는지 확인해야함.

						SLOTINFO* pslot = ItemExamine(vSlot); // 드랍했을때 아이템이 들어갈 칸이있는지 검사
						if (pslot == nullptr)
							return;

						D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
						_pItem->SetInvenPosition(vpos);
						return;
					}
					else
					{
						SLOTINFO* pslot = ItemExamine(vSlot); // 드랍했을때 아이템이 들어갈 칸이있는지 검사
						if (pslot == nullptr)
							return;

						D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
						//D3DXVECTOR3 vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };
						_pItem->SetInvenPosition(vpos);
						return;
					}
				}
			}
		}
	}
	_bItemCatchCheck = true;
}

SLOTINFO* Inventory::ItemExamine(std::vector<SLOTINFO*> InvenSlot) // 수정 해야함.
{
	int InvenCntX = InvenSlot[0]->_iSlotCntX;
	int InvenCntY = InvenSlot[0]->_iSlotCntY;

	int ItemCntX = _pItemSlotInfo->_iSlotCntX;
	int ItemCntY = _pItemSlotInfo->_iSlotCntY;

	switch (ItemCntX * ItemCntY)
	{
	case 1:
		return Examine1X1(InvenSlot, InvenCntX, InvenCntY);
	case 2:
		return Examine2X1(InvenSlot, InvenCntX, InvenCntY);
	case 3:
		return Examine1X3(InvenSlot, InvenCntX, InvenCntY);
	case 4:
		return Examine2X2(InvenSlot, InvenCntX, InvenCntY);
	case 6:
		return Examine2X3(InvenSlot, InvenCntX, InvenCntY);
	}
}

void Inventory::CatchtoExamine(std::vector<SLOTINFO*> InvenSlot, D3DXVECTOR3 vpos) // 수정해야함
{
	int InvenCntX = InvenSlot[0]->_iSlotCntX;
	int InvenCntY = InvenSlot[0]->_iSlotCntY;

	int ItemCntX = _pItemSlotInfo->_iSlotCntX;
	int ItemCntY = _pItemSlotInfo->_iSlotCntY;

	int ChageIndex;
	int Index = 0;
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
					InvenSlot[ChageIndex]->_bSlotCheck = false;
					return;
				case 2:
					InvenSlot[ChageIndex]->_bSlotCheck = false;
					InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
					return;
				case 3:
					InvenSlot[ChageIndex]->_bSlotCheck = false;
					InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
					InvenSlot[ChageIndex + (InvenCntX * 2)]->_bSlotCheck = false;
					return;
				case 4:
					InvenSlot[ChageIndex]->_bSlotCheck = false;
					InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
					InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
					InvenSlot[ChageIndex + InvenCntX + 1]->_bSlotCheck = false;
					return;
				case 6:
					InvenSlot[ChageIndex]->_bSlotCheck = false;
					InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
					InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
					InvenSlot[ChageIndex + InvenCntX + 1]->_bSlotCheck = false;
					InvenSlot[ChageIndex + (InvenCntX * 2)]->_bSlotCheck = false;
					InvenSlot[ChageIndex + (InvenCntX * 2) + 1]->_bSlotCheck = false;
					return;
				}
			}
		}
	}
}

SLOTINFO* Inventory::Examine1X1(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY)
{
	int Index = 0;
	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (MaxIndex >= Index)
			{
				if (!InvenSlot[Index]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
			else
				return nullptr;
		}
	}
	return nullptr;
}

SLOTINFO* Inventory::Examine1X3(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY)
{
	int Index = 0;
	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;
			if (MaxIndex >= Index && MaxIndex >= (Index + iInvenCntX) && MaxIndex >= (Index + (iInvenCntX * 2)))
			{
				if (!InvenSlot[Index]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck
					&& !InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
					InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
			else
				return nullptr;
		}
	}
	return nullptr;
}

SLOTINFO* Inventory::Examine2X1(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY)
{
	int Index = 0;
	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (MaxIndex >= Index && MaxIndex >= (Index + 1))
			{
				if (!InvenSlot[Index]->_bSlotCheck
					&& !InvenSlot[Index + 1]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					InvenSlot[Index + 1]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
		}
	}
	return nullptr;
}

SLOTINFO* Inventory::Examine2X2(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY)
{
	int Index = 0;
	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (MaxIndex >= Index && MaxIndex >= Index + 1 && MaxIndex >= Index + iInvenCntX && MaxIndex >= Index + iInvenCntX + 1)
			{
				if (!InvenSlot[Index]->_bSlotCheck
					&& !InvenSlot[Index + 1]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					InvenSlot[Index + 1]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
			else
				return nullptr;
		}
	}
	return nullptr;
}

SLOTINFO* Inventory::Examine2X3(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY)
{
	int Index = 0;
	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;
	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (MaxIndex >= Index && MaxIndex >= Index + 1 && MaxIndex >= Index + iInvenCntX && MaxIndex >= Index + iInvenCntX + 1
				&& MaxIndex >= Index + (iInvenCntX * 2) && MaxIndex >= Index + (iInvenCntX * 2) + 1)
			{
				if (!InvenSlot[Index]->_bSlotCheck
					&& !InvenSlot[Index + 1]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck
					&& !InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck
					&& !InvenSlot[Index + (iInvenCntX * 2) + 1]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					InvenSlot[Index + 1]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck = true;
					InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck = true;
					InvenSlot[Index + (iInvenCntX * 2) + 1]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
			else
				return nullptr;
		}
	}
	return nullptr;
}
