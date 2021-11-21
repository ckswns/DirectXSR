#include "pch.h"
#include "Inventory.h"
#include "GameObject.h"
#include "pch.h"
#include "Inventory.h"
#include "GameObject.h"
#include "Image.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "RectTransform.h"
#include "Text.h"
#include "Player.h"
#include "Button.h"

using namespace ce::UI;
using namespace ce::CE_MATH;

Inventory::Inventory(Player* player) noexcept
	:_pPlayer(player)
{
}

Inventory::~Inventory() noexcept
{
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
	gameObject->SetDontDestroy(true);

	_pExamine = new Examine();

	GameObject* obj = nullptr;

	for (int i = 0; i < (int)Slot::SLOTTYPE::POTION; ++i)
	{
		obj = GameObject::Instantiate();
		Slot* pSlot = new Slot((Slot::SLOTTYPE)i);
		obj->AddComponent(pSlot);
		_vecSlotGroup[i].emplace_back(pSlot);
		obj->SetDontDestroy(true);
	}

	_iGold = 1000;

	obj = GameObject::Instantiate();
	obj->SetDontDestroy(true);
	_pTexGold = new UI::Text(std::to_string(_iGold).c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_RIGHT);
	obj->AddComponent(_pTexGold);
	RectTransform* rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(70);
	rt->SetHeight(50);
	obj->SetSortOrder(1);
	obj->GetTransform()->SetParent(gameObject->GetTransform());
	obj->GetTransform()->SetWorldPosition(885, 525, 0);

	GameObject* CloseBtn = GameObject::Instantiate();
	CloseBtn->GetTransform()->SetParent(gameObject->GetTransform());
	CloseBtn->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Close_0.png")));
	Button<Inventory>* btn = static_cast<Button<Inventory>*>(CloseBtn->AddComponent(new Button<Inventory>(this)));
	btn->onMouseDown += &Inventory::Close;
	btn->SetTexture(nullptr, nullptr, ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Close_1.png"), nullptr);
	CloseBtn->SetSortOrder(50);
	CloseBtn->GetTransform()->SetWorldPosition(670, 520, 0);
}

void Inventory::Update(float) noexcept
{
	_pTexGold->SetText(std::to_string(_iGold).c_str());

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (pt.x >= WINCX >> 1)
		{
			if (!_vecItem.empty())
			{
				_bMovecheck = false;
				_bItemCatchCheck = !_bItemCatchCheck;
				if (_bItemCatchCheck)
					ItemCatch(pt);
				else
					_bDropCheck = ItemDropAtMouse(pt);
			}
		}
		else
		{
			if (_bItemCatchCheck)
				_bDropCheck = ItemDropAtMouse(pt);
		}
	}
	//else if (INPUT->GetKeyDown(VK_RBUTTON) && !_bItemCatchCheck) // 커밋하기전 주석 처리
	//	ITEMDATA* pItemInfo = UsingItem(pt);

	if (_bItemCatchCheck)
		ItemMove();

	if (_bDropCheck)
		Dropitem();

	if (!_vecItem.empty())
		ItemInfoBoxCheck(pt);

#ifdef _DEBUG
	if (INPUT->GetKeyDown('l') || INPUT->GetKeyDown('L'))
	{
		ITEMDATA* pInvenInfo = new ITEMDATA();

		/*int i = ce::CE_MATH::Random(1, 12);*/
		int i = rand() % 11 + 1;
		pInvenInfo->itype = i;

		PickUpItems(pInvenInfo);
	}
	if (INPUT->GetKeyDown('K') || INPUT->GetKeyDown('k'))
		BuyItem(10);
	if (INPUT->GetKeyDown('j') || INPUT->GetKeyDown('J'))
		PickUpGold(10);

#endif // _DEBUG
}

void Inventory::Close()
{
	gameObject->SetActive(false);
}

bool Inventory::BuyItem(int Gold)
{
	if (_iGold < Gold)
		return false;

	_iGold -= Gold;

	return true;
}

void Inventory::ItemInfoBoxCheck(POINT pt)
{
	for (size_t t = 0; t < _vecItem.size(); ++t)
	{
		RECT rc = _vecItem[t].second->GetItemRect();
		if (PtInRect(&rc, pt) && !_bMovecheck)
			_vecItem[t].second->SetInfoBoxCheck(true);
		else
			_vecItem[t].second->SetInfoBoxCheck(false);
	}
}

ITEMDATA* Inventory::UsingItem(POINT pt)
{
	for (size_t t = 0; t < _vecItem.size(); ++t)
	{
		RECT rc = _vecItem[t].second->GetItemRect();
		Slot::SLOTTYPE eType = _vecItem[t].second->GetSlotType();
		ITEMDATA* pItemInfo = nullptr;
		if (PtInRect(&rc, pt))
		{
			if (eType == Slot::SLOTTYPE::POTION)
			{
#ifdef _DEBUG
				_pItemSlotInfo = _vecItem[t].second->GetItemSlot()[0].second;
			//	_pItemData = _vecItem[t].first;
				_pItem = _vecItem[t].second;
				ReCatchtoExamine(_vecSlotGroup[0][0]->GetSlot(), _vecItem[t].second->GetItemSlot()[0].second->_vPos, true);
#else 
				_pItemSlotInfo = _vecItem[t].second->GetItemSlot()[0];
			//	_pItemData = _vecItem[t].first;
				_pItem = _vecItem[t].second;
				ReCatchtoExamine(_vecSlotGroup[0][0]->GetSlot(), _vecItem[t].second->GetItemSlot()[0]->_vPos, true);
#endif // _DEBUG
				pItemInfo = _vecItem[t].first;
				_vecItem[t].second->SetInfoBoxCheck(false);
				_vecItem[t].second->OnMouseDown();
				_vecItem.erase(_vecItem.begin() + (int)t);
				return pItemInfo;
			}
			else
			{
#ifdef _DEBUG
				_pItemSlotInfo = _vecItem[t].second->GetItemSlot()[0].second;
			//	_pItemData = _vecItem[t].first;
#else
				_pItemSlotInfo = _vecItem[t].second->GetItemSlot()[0];
			//	_pItemData = _vecItem[t].first;
#endif // _DEBUG
				_pItem = _vecItem[t].second;
				for (int i = 1; i < (int)Slot::SLOTTYPE::POTION; ++i)
				{
					if (_vecSlotGroup[i][0]->GetSlot()[0]->_bSlotCheck == true)
					{
						if (i == (int)Slot::SLOTTYPE::POTION - 1)
							return nullptr;
					}

					if (_pExamine->EquipItem(_vecSlotGroup[i], _pItemSlotInfo))
					{
						ReCatchtoExamine(_vecSlotGroup[0][0]->GetSlot(), _pItemSlotInfo->_vPos, true);
						SLOTINFO* pSlot = DropAtEtingExamine(_vecSlotGroup[i][0]->GetSlot());
						std::vector<SLOTINFO*> vSlot = _vecSlotGroup[i][0]->GetSlot();
						if (pSlot == nullptr /*&& i < (int)Slot::SLOTTYPE::POTION - 1*/)
							continue;
						else
						{
							D3DXVECTOR3 vpos = { (float)pSlot->_tRect.left,(float)pSlot->_tRect.top,0 };
							pItemInfo = _vecItem[t].first;
							_pItem->SetInvenPosition(vpos);
							return pItemInfo;
						}
					}
				}
				return nullptr;
			}
		}
	}
	return nullptr;
}

ITEMDATA* Inventory::Dropitem()
{
	for (size_t t = 0; t < _vecItem.size(); ++t)
	{
		if (_vecItem[t].second == _pItem)
		{
			_vecItem[t].second->DropItemSlot();
			ITEMDATA* ItemInfo = _vecItem[t].first;
			_vecItem.erase(_vecItem.begin() + (int)t);
			_bDropCheck = false;
			return ItemInfo;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Inventory::ItemCatch(POINT pt)
{
	_pItem = nullptr;
	_pItemSlotInfo = nullptr;
//	_pItemData = nullptr;

	for (size_t t = 0; t < _vecItem.size(); ++t)
	{
		_vecItemslot = _vecItem[t].second->GetItemSlot();
		RECT rc = _vecItem[t].second->GetItemRect();

		if (PtInRect(&rc, pt))
		{
			_bItemCatchCheck = true;
			_pItem = _vecItem[t].second;
#ifdef _DEBUG
			_pItemSlotInfo = _vecItemslot[0].second;
//			_pItemData = _vecItem[0].first;
#else
			_pItemSlotInfo = _vecItemslot[0];
//			_pItemData = _vecItem[t].first;
#endif // _DEBUG
			ItemCatchExamine(pt);
			return;
		}
		else
			_bItemCatchCheck = false;
	}
}

void Inventory::ItemCatchExamine(POINT pt)
{
	for (int i = 0; i < (int)Slot::SLOTTYPE::POTION; ++i)
	{
		auto& iter = _vecSlotGroup[i];

		Slot::SLOTTYPE eSlottype = iter[0]->GetSlotType();
		std::vector<SLOTINFO*> vSlot = iter[0]->GetSlot();

		RECT	MaxRc = iter[0]->GetRect();

		if (PtInRect(&MaxRc, pt))
		{
			SLOTINFO* pItem = _pItem->GetItemInfo(0);
			ReCatchtoExamine(vSlot, pItem->_vPos, true);
			return;
		}
	}
}

void Inventory::ReCatchtoExamine(std::vector<SLOTINFO*> InvenSlot, D3DXVECTOR3 vpos, bool bCheck) // 수정해야함
{
	int InvenCntX = InvenSlot[0]->_iSlotCntX;
	int InvenCntY = InvenSlot[0]->_iSlotCntY;
	int ItemCntX = 0;
	int ItemCntY = 0;
	if (bCheck)
	{
		ItemCntX = _pItemSlotInfo->_iSlotCntX;
		ItemCntY = _pItemSlotInfo->_iSlotCntY;
	}
	else
	{
		ItemCntX = _pPriveSlotInfo->_iSlotCntX;
		ItemCntY = _pPriveSlotInfo->_iSlotCntY;
	}

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
					if (MaxIndex >= ChageIndex)
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						return;
					}
					break;
				case 2:
					if (_pItem->GetSlotType() == Slot::SLOTTYPE::BELT)
					{
						if (MaxIndex >= ChageIndex && MaxIndex >= (ChageIndex + 1))
						{
							InvenSlot[ChageIndex]->_bSlotCheck = false;
							InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
							return;
						}
					}
					else
					{
						if (MaxIndex >= ChageIndex && MaxIndex >= (ChageIndex + InvenCntX))
						{
							InvenSlot[ChageIndex]->_bSlotCheck = false;
							InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
							return;
						}
					}
					break;
				case 3:
					if (MaxIndex >= ChageIndex && MaxIndex >= (ChageIndex + InvenCntX) && MaxIndex >= ChageIndex + (InvenCntX * 2))
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
						InvenSlot[ChageIndex + (InvenCntX * 2)]->_bSlotCheck = false;
						return;
					}
					break;
				case 4:
					if (MaxIndex >= ChageIndex && MaxIndex >= ChageIndex + 1 && MaxIndex >= ChageIndex + InvenCntX && MaxIndex >= ChageIndex + InvenCntX + 1)
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX + 1]->_bSlotCheck = false;
						return;
					}
					break;
				case 6:
					if (MaxIndex >= ChageIndex && MaxIndex >= ChageIndex + 1 && MaxIndex >= ChageIndex + InvenCntX && MaxIndex >= ChageIndex + InvenCntX + 1
						&& MaxIndex >= ChageIndex + (InvenCntX * 2) && MaxIndex >= ChageIndex + (InvenCntX * 2) + 1)
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX + 1]->_bSlotCheck = false;
						InvenSlot[ChageIndex + (InvenCntX * 2)]->_bSlotCheck = false;
						InvenSlot[ChageIndex + (InvenCntX * 2) + 1]->_bSlotCheck = false;
						return;
					}
					break;
				}
			}
		}
	}
}

bool Inventory::PickUpItems(ITEMDATA* pInvenInfo)
{
	GameObject* pobj = GameObject::Instantiate();
	float fx = UnsignedRandomf(400.f);
	float fy = UnsignedRandomf(700.f);
	ItemSlot* pSlot = new ItemSlot((Slot::SLOTTYPE)pInvenInfo->itype, gameObject->GetTransform(), fx, fy);
	pobj->AddComponent(pSlot);
	pobj->SetDontDestroy(true);
	_vecItem.emplace_back(pInvenInfo, pSlot);
	_pItem = pSlot;
#ifdef _DEBUG
	_pItemSlotInfo = pSlot->GetItemSlot()[0].second;
//	_pItemData = pInvenInfo;
#else
	_pItemSlotInfo = pSlot->GetItemInfo(0);
//	_pItemData = pInvenInfo;
#endif // _DEBUG

	return ItemEating();
}

bool Inventory::ItemEating()
{
	if (_pItem == nullptr || _pItemSlotInfo == nullptr)
		return false;

	SLOTINFO* pslot = DropAtEtingExamine(_vecSlotGroup[0][0]->GetSlot()); // 아이템이 들어갈 칸이있는지 검사

	if (pslot == nullptr)
	{
		_bDropCheck = true;
		return false;
	}

	D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
	_pItem->SetInvenPosition(vpos);

	RECT ItemRect = _pItem->GetItemRect();
	RECT SlotRect = _vecSlotGroup[0][0]->GetRect();

	if (SlotRect.right >= ItemRect.right && SlotRect.bottom >= ItemRect.bottom)
	{
		_bItemCatchCheck = false;
		return true;
	}
	else
	{
		ReCatchtoExamine(_vecSlotGroup[0][0]->GetSlot(), _pItemSlotInfo->_vPos, true);
		_bDropCheck = true;
		return false;
	}
	return true;
}

SLOTINFO* Inventory::DropAtEtingExamine(std::vector<SLOTINFO*> InvenSlot)
{
	int ItemCntX = _pItemSlotInfo->_iSlotCntX;
	int ItemCntY = _pItemSlotInfo->_iSlotCntY;

	switch (ItemCntX * ItemCntY)
	{
	case 1:
		return _pExamine->EatingExamine1X1(InvenSlot);
	case 2:
		if (_pItem->GetSlotType() == Slot::SLOTTYPE::BELT)
			return _pExamine->EatingExamine2X1(InvenSlot);
		else
			return _pExamine->EatingExamine1X2(InvenSlot);
	case 3:
		return _pExamine->EatingExamine1X3(InvenSlot);
	case 4:
		return _pExamine->EatingExamine2X2(InvenSlot);
	case 6:
		return _pExamine->EatingExamine2X3(InvenSlot);
	}
	return nullptr;
}

bool Inventory::ItemDropAtMouse(POINT pt)
{
	if (_pItemSlotInfo == nullptr || _pItem == nullptr)
		return false;

	for (int i = 0; i < (int)Slot::SLOTTYPE::POTION; ++i)
	{
		auto& iter = _vecSlotGroup[i];

		Slot::SLOTTYPE eSlottype = iter[0]->GetSlotType();
		Slot::SLOTTYPE eItemSlotType = _pItem->GetSlotType();
		std::vector<SLOTINFO*> vSlot = iter[0]->GetSlot();

		RECT	MaxRc = iter[0]->GetRect();
		D3DXVECTOR3 vpos = {};
		if (PtInRect(&MaxRc, pt))
		{
			for (int i = 0; i < (int)vSlot.size(); ++i)
			{
				if (PtInRect(&vSlot[i]->_tRect, pt))
				{
					if (vSlot[i]->_iFlag & _pItemSlotInfo->_iFlag && eItemSlotType != Slot::SLOTTYPE::POTION)
					{
						SLOTINFO* pslot = DropAtMouseExamine(vSlot, pt); // 들어갈 칸이 있는지 검사
						if (pslot == nullptr)
						{
							pslot = ItemSwitching(vSlot, pt); // 없으면 아이템 스위칭 해야 하는지 한번더 검사

							if (pslot == nullptr)
							{
								_bItemCatchCheck = true;
								return false;
							}
						}
						if (_bSwitchingcheck)
						{
							SLOTINFO* pslot = DropAtMouseExamine(vSlot, pt); //아이템 스위칭 해야하는 상황이면 스위칭될 아이템이 들어갈 자리가 있는지 한번더 검사
							if (pslot == nullptr)
							{
								_bItemCatchCheck = true; // 자리가 없으면 스위칭 시키지 않음
								_bSwitchingcheck = false;
								return false;
							}

							vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };

							_pItem->SetInvenPosition(vpos);
							_pItem = _pPriveItem;
							_bItemCatchCheck = true;
							_pItemSlotInfo = _pPriveSlotInfo;
						//	_pItemData = _pPriveItemData;
							_bSwitchingcheck = false;
							_pItemInfo = EquipItemCheck(_vecItem, _pItemSlotInfo);
							return false;
						}
						else
						{
							vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
							_pItemInfo = EquipItemCheck(_vecItem, _pItemSlotInfo);
							return false;
						}
					}
					else if (eSlottype == Slot::SLOTTYPE::NORMAL) // 장착 슬롯을 제외한 수납이 가능한 공간에서 검사 처리
					{
						SLOTINFO* pslot = DropAtMouseExamine(vSlot, pt); // 들어갈 칸이 있는지 검사
						if (pslot == nullptr)
						{
							pslot = ItemSwitching(vSlot, pt); // 없으면 아이템 스위칭 해야 하는지 한번더 검사

							if (pslot == nullptr)
							{
								_bItemCatchCheck = true;
								return false;
							}
						}

						if (_bSwitchingcheck)
						{
							SLOTINFO* pslot = DropAtMouseExamine(vSlot, pt); //아이템 스위칭 해야하는 상황이면 스위칭될 아이템이 들어갈 자리가 있는지 한번더 검사
							if (pslot == nullptr)
							{
								_bItemCatchCheck = true; // 자리가 없으면 스위칭 시키지 않음
								_bSwitchingcheck = false;
								return false;
							}
							vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
							_pItem = _pPriveItem;
							_pItemSlotInfo = _pPriveSlotInfo;
						//	_pItemData = _pPriveItemData;
							_bItemCatchCheck = true;
							_bSwitchingcheck = false;
							return false;
						}
						else
						{ // 스위칭을 할 필요가없으면 마우스 위치 기준의 칸으로 들어감
							vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
							return false;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < (int)Slot::SLOTTYPE::POTION; ++i)
	{
		auto& iter = _vecSlotGroup[i];
		RECT	MaxRc = iter[0]->GetRect();
		if (PtInRect(&MaxRc, pt))
		{
			_bItemCatchCheck = true;
			return false;
		}
	}
	// 비어있는 칸이 없거나 아이템 버리기 위해 아이템 슬롯 외의 공간에 아이템을 드랍 했을경우 ( 이미지 변경 )

	_bItemCatchCheck = false;

	RECT rc = {};
	rc.left = WINCX >> 1;
	rc.top = 0;
	rc.right = WINCX;
	rc.bottom = static_cast<Image*>(gameObject->GetComponent(COMPONENT_ID::IMAGE))->GetTexture()->Height();

	if (PtInRect(&rc, pt))
		ItemEating();
	else
		return true;

	return false;
}

SLOTINFO* Inventory::DropAtMouseExamine(std::vector<SLOTINFO*> InvenSlot, POINT pt)
{
	int ItemCntX = _pItemSlotInfo->_iSlotCntX;
	int ItemCntY = _pItemSlotInfo->_iSlotCntY;
	SLOTINFO* pSlotinfo = nullptr;
	switch (ItemCntX * ItemCntY)
	{
	case 1:
		return _pExamine->MouseExamine1X1(InvenSlot, pt);
		break;
	case 2:
		if (_pItem->GetSlotType() == Slot::SLOTTYPE::BELT)
			return _pExamine->MouseExamine2X1(InvenSlot, pt);
		else
			return _pExamine->MouseExamine1X2(InvenSlot, pt);
		break;
	case 3:
		return _pExamine->MouseExamine1X3(InvenSlot, pt);
		break;
	case 4:
		return _pExamine->MouseExamine2X2(InvenSlot, pt);
		break;
	case 6:
		return _pExamine->MouseExamine2X3(InvenSlot, pt);
		break;
	}
	return nullptr;
}

void Inventory::ItemMove()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (_pItem != nullptr)
	{
		_bMovecheck = true;
		_pItem->setMousePosition(D3DXVECTOR3(pt.x, pt.y, 0));
	}
}

SLOTINFO* Inventory::ItemSwitching(std::vector<SLOTINFO*> InvenSlot, POINT pt)
{
	RECT rc = {};
	if (_pItemSlotInfo != nullptr)
	{
		for (size_t t = 0; t < _vecItem.size(); ++t)
		{
			RECT CurrentRect = _pItem->GetItemRect();
			RECT PriveRect = _vecItem[t].second->GetItemRect();

			if (_pItem != _vecItem[t].second)
			{
				if (IntersectRect(&rc, &PriveRect, &CurrentRect))
				{
					RECT rc = {};
#ifdef _DEBUG
					if (IntersectRect(&rc, &_pItemSlotInfo->_tRect, &_vecItem[t].second->GetItemSlot()[0].second->_tRect))
					{
						_pPriveItem = _vecItem[t].second;
						_pPriveSlotInfo = _vecItem[t].second->GetItemSlot()[0].second;
						//_pPriveItemData = _vecItem[t].first;
						ReCatchtoExamine(InvenSlot, _pPriveSlotInfo->_vPos, false);
						_bSwitchingcheck = true;
						return _vecItem[t].second->GetItemSlot()[0].second;
					}
#else
					if (IntersectRect(&rc, &_pItemSlotInfo->_tRect, &_vecItem[t].second->GetItemSlot()[0]->_tRect))
					{
						_pPriveItem = _vecItem[t].second;
						_pPriveSlotInfo = _vecItem[t].second->GetItemSlot()[0];
						//_pPriveItemData = _vecItem[t].first;
						ReCatchtoExamine(InvenSlot, _pPriveSlotInfo->_vPos, false);
						_bSwitchingcheck = true;
						return _vecItem[t].second->GetItemSlot()[0];
					}
#endif // _DEBUG

				}
			}
		}
	}
	return nullptr;
}

ITEMDATA* Inventory::EquipItemCheck(std::vector<std::pair<ITEMDATA*, ItemSlot*>> vItem, SLOTINFO* vslotinfo)
{
	for (auto& iter : _vecItem)
	{
#ifdef _DEBUG
		if (iter.second->GetItemSlot()[0].second->_vPos == vslotinfo->_vPos)
		{
		//	_pPlayer->EquidItem(iter.first, _pItemData);
			return iter.first;
		}
#else
		if (iter.second->GetItemSlot()[0]->_vPos == vslotinfo->_vPos) 
		{
			//	_pPlayer->EquidItem(iter.first, _pItemData);
			return iter.first;
		}
#endif // _DEBUG
	}
	return nullptr;
}