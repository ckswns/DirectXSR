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

	_iGold = 100;

	GameObject* obj;
	obj = GameObject::Instantiate();
	_pTexGold = static_cast<UI::Text*>(obj->AddComponent(new UI::Text(std::to_string(_iGold).c_str(), D3DCOLOR_ARGB(255, 255, 255, 255))));
	RectTransform* rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(40);
	rt->SetHeight(40);
	obj->SetSortOrder(10);
	obj->GetTransform()->SetWorldPosition(885, 530, 0);
}

void Inventory::Update(float) noexcept
{
	_pTexGold->SetText(std::to_string(_iGold).c_str());

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (INPUT->GetKeyDown(KEY_LBUTTON) || INPUT->GetKeyDown(KEY_LBUTTON))/*INPUT->GetKeyDown('o') || INPUT->GetKeyDown('O'))*/ // L��ư�� �� �ȸԾ �ٲ������.
	{
		float fx = pt.x;
		float fy = pt.y;
		if (!_vecItem.empty())
		{
			_bItemCatchCheck = !_bItemCatchCheck;
			if (_bItemCatchCheck)
				ItemCatch(pt);
			else
				_bDropCheck = ItemDropAtMouse(pt);
		}
	}
	else if (INPUT->GetKeyDown(KEY_RBUTTON) && !_bItemCatchCheck)
		UsingItem(pt);

	if (_bItemCatchCheck)
		ItemMove();


#ifdef _DEBUG
	if (INPUT->GetKeyDown('l') || INPUT->GetKeyDown('L'))
	{
		INVENITEMINFO* pInvenInfo = new INVENITEMINFO();

		int i = ce::CE_MATH::Random(1, 12);
		pInvenInfo->_eSlotType = i;

		PickUpItems(pInvenInfo);
	}
#endif // _DEBUG
}

bool Inventory::BuyItem(int Gold)
{
	_iGold -= Gold;

	if (_iGold < 0)
	{
		_iGold = 0;
		return false;
	}
	return true;
}

INVENITEMINFO* Inventory::UsingItem(POINT pt)
{
	int Index = 0;

	for (auto& iter : _vecItem)
	{
		RECT rc = iter.second->GetItemRect();
		Slot::SLOTTYPE eType = iter.second->GetSlotType();
		if(PtInRect(&rc, pt))
		{
			if (eType == Slot::SLOTTYPE::POTION)
			{
				iter.second->OnMouseDown();
				return iter.first;
			}
			else
			{
				iter.second->OnMouseDown();
#ifdef _DEBUG
				_pItemSlotInfo = iter.second->GetItemSlot()[0].second;
				ReCatchtoExamine(_vecSlotGroup[0][0]->GetSlot(), iter.second->GetItemSlot()[0].second->_vPos, true);
#else 
				_pItemSlotInfo = iter.second->GetItemSlot()[0];
				ReCatchtoExamine(_vecSlotGroup[0][0]->GetSlot(), iter.second->GetItemSlot()[0]->_vPos, true);
#endif // _DEBUG

				return iter.first;
			}
			break;
		}
	}
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
			ReCatchtoExamine(vSlot, pItem->_vPos,true);
			return;
		}
	}
}

void Inventory::ReCatchtoExamine(std::vector<SLOTINFO*> InvenSlot, D3DXVECTOR3 vpos, bool bCheck) // �����ؾ���
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
					return;
				case 2:
					if (MaxIndex >= ChageIndex && MaxIndex >= (ChageIndex + 1))
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
						return;
					}
					return;
				case 3:
					if (MaxIndex >= ChageIndex && MaxIndex >= (ChageIndex + InvenCntX) && MaxIndex >= ChageIndex + (InvenCntX * 2))
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
						InvenSlot[ChageIndex + (InvenCntX * 2)]->_bSlotCheck = false;
						return;
					}
					return;
				case 4:
					if (MaxIndex >= ChageIndex && MaxIndex >= ChageIndex + 1 && MaxIndex >= ChageIndex + InvenCntX && MaxIndex >= ChageIndex + InvenCntX + 1)
					{
						InvenSlot[ChageIndex]->_bSlotCheck = false;
						InvenSlot[ChageIndex + 1]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX]->_bSlotCheck = false;
						InvenSlot[ChageIndex + InvenCntX + 1]->_bSlotCheck = false;
						return;
					}
					return;
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
					return;
				}
			}
		}
	}
}

bool Inventory::PickUpItems(INVENITEMINFO* pInvenInfo)
{
	GameObject* pobj = GameObject::Instantiate();
	float fx = UnsignedRandomf(400.f);
	float fy = UnsignedRandomf(700.f);
	ItemSlot* pSlot = new ItemSlot((Slot::SLOTTYPE)pInvenInfo->_eSlotType,(int)_vecItem.size(), fx, fy);
	pobj->AddComponent(pSlot);
	_vecItem.emplace_back(pInvenInfo, pSlot);
	_pItem = pSlot;
#ifdef _DEBUG
	_pItemSlotInfo = pSlot->GetItemSlot()[0].second;
#else
	_pItemSlotInfo = pSlot->GetItemInfo(0);
#endif // _DEBUG

	return ItemEating();
}

bool Inventory::ItemEating()
{
	if (_pItem == nullptr || _pItemSlotInfo == nullptr)
		return false;

	SLOTINFO* pslot = DropAtEtingExamine(_vecSlotGroup[0][0]->GetSlot()); // �������� �� ĭ���ִ��� �˻�

	if (pslot == nullptr)
		return false;

	D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
	_pItem->SetInvenPosition(vpos);

	RECT ItemRect = _pItem->GetItemRect();
	RECT SlotRect = _vecSlotGroup[0][0]->GetRect();

	if(SlotRect.right >= ItemRect.right && SlotRect.bottom >= ItemRect.bottom)
		_bItemCatchCheck = false;
	else
	{
		ReCatchtoExamine(_vecSlotGroup[0][0]->GetSlot(), _pItemSlotInfo->_vPos, true);
		float fx = UnsignedRandomf(400.f);
		float fy = UnsignedRandomf(700.f);
		D3DXVECTOR3 vPos = { fx, fy, 0.f };
		_pItem->SetInvenPosition(vPos);
		return false;
	}
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

bool Inventory::ItemDropAtMouse(POINT pt)
{
	if (_pItemSlotInfo == nullptr || _pItem == nullptr)
		return false;

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

						SLOTINFO* pslot = DropAtMouseExamine(vSlot, pt); // �� ĭ�� �ִ��� �˻�
						if (pslot == nullptr)
						{
							pslot = ItemSwitching(vSlot, pt); // ������ ������ ����Ī �ؾ� �ϴ��� �ѹ��� �˻�

							if (pslot == nullptr)
							{
								_bItemCatchCheck = true;
								return false;
							}
						}
						if (_bSwitchingcheck)
						{
							SLOTINFO* pslot = DropAtMouseExamine(vSlot, pt); //������ ����Ī �ؾ��ϴ� ��Ȳ�̸� ����Ī�� �������� �� �ڸ��� �ִ��� �ѹ��� �˻�
							if (pslot == nullptr)
							{
								_bItemCatchCheck = true; // �ڸ��� ������ ����Ī ��Ű�� ����
								_bSwitchingcheck = false;
								return false;
							}
							D3DXVECTOR3 vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
							_pItem = _pPriveItem;
							_pItemSlotInfo = _pPriveSlotInfo;
							_bItemCatchCheck = true;
							_bSwitchingcheck = false;
							return true;
						}
						else
						{
							D3DXVECTOR3 vpos = { (float)vSlot[0]->_tRect.left, (float)vSlot[0]->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
							return true;
						}
					}
					else if (eSlottype == Slot::SLOTTYPE::NORMAL) // ���� ������ ������ ������ ������ �������� �˻� ó��
					{
						SLOTINFO* pslot = DropAtMouseExamine(vSlot, pt); // �� ĭ�� �ִ��� �˻�
						if (pslot == nullptr)
						{
							pslot = ItemSwitching(vSlot, pt); // ������ ������ ����Ī �ؾ� �ϴ��� �ѹ��� �˻�

							if (pslot == nullptr)
							{
								_bItemCatchCheck = true;
								return false;
							}
						}

						if (_bSwitchingcheck)
						{
							SLOTINFO* pslot = DropAtMouseExamine(vSlot, pt); //������ ����Ī �ؾ��ϴ� ��Ȳ�̸� ����Ī�� �������� �� �ڸ��� �ִ��� �ѹ��� �˻�
							if (pslot == nullptr)
							{
								_bItemCatchCheck = true; // �ڸ��� ������ ����Ī ��Ű�� ����
								_bSwitchingcheck = false;
								return false;
							}
							D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
							_pItem = _pPriveItem;
							_pItemSlotInfo = _pPriveSlotInfo;
							_bItemCatchCheck = true;
							_bSwitchingcheck = false;
							return true;
						}
						else
						{ // ����Ī�� �� �ʿ䰡������ ���콺 ��ġ ������ ĭ���� ��
							D3DXVECTOR3 vpos = { (float)pslot->_tRect.left, (float)pslot->_tRect.top, 0 };
							_pItem->SetInvenPosition(vpos);
							return true;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < (int)Slot::SLOTTYPE::END; ++i)
	{
		auto& iter = _vecSlotGroup[i];
		RECT	MaxRc = iter[0]->GetRect();
		if (PtInRect(&MaxRc, pt))
		{
			_bItemCatchCheck = true;
			return false;
		}
	}
	// ����ִ� ĭ�� ���ų� ������ ������ ���� ������ ���� ���� ������ �������� ��� ������� 
	float fx = UnsignedRandomf(400.f);
	float fy = UnsignedRandomf(700.f);
	D3DXVECTOR3 vPos = { fx, fy, 0.f };
	_pItem->SetInvenPosition(vPos);
	_bItemCatchCheck = false;
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
		return _pExamine->MouseExamine2X1(InvenSlot, pt);
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
		_pItem->setMousePosition(D3DXVECTOR3(pt.x, pt.y, 0));
		return;
	}
}

SLOTINFO* Inventory::ItemSwitching(std::vector<SLOTINFO*> InvenSlot,POINT pt) // ����Ī �����ؾ���.
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
						ReCatchtoExamine(InvenSlot, _pPriveSlotInfo->_vPos, false);
						_bSwitchingcheck = true;
						return _vecItem[t].second->GetItemSlot()[0].second;
					}
#else
					if (IntersectRect(&rc, &_pItemSlotInfo->_tRect, &_vecItem[t].second->GetItemSlot()[0]->_tRect))
					{
						_pPriveItem = _vecItem[t].second;
						_pPriveSlotInfo = _vecItem[t].second->GetItemSlot()[0];
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