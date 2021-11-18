﻿#include "pch.h"
#include "StoreWnd.h"
#include "ItemSlot.h"
#include "Slot.h"
#include "Transform.h"
#include "Image.h"
#include "Button.h"
using namespace ce::UI;
void StoreWnd::Start(void) noexcept
{
	_ItemSlot.assign((_iCntX * _iCntY), false);

	//칸 시작지점
	_vStartPos = D3DXVECTOR3(28, 88, 0);

	gameObject->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Store.png")));

	GameObject* CloseBtn = GameObject::Instantiate();
	CloseBtn->GetTransform()->SetParent(gameObject->GetTransform());
	CloseBtn->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Close_0.png")));
	Button<StoreWnd>* btn = static_cast<Button<StoreWnd>*>(gameObject->AddComponent(new Button<StoreWnd>(this)));
	btn->onMouseDown += &StoreWnd::OnClose;
	btn->SetTexture(nullptr, nullptr, ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Close_1.png"), nullptr);
	CloseBtn->SetSortOrder(2);
	CloseBtn->GetTransform()->SetLocalPosition(300,500,0);

	INVENITEMINFO info;
	info._eSlotType =(int)Slot::SLOTTYPE::POTION;
	AddItem(&info);

	INVENITEMINFO info2;
	info2._eSlotType = (int)Slot::SLOTTYPE::BODY;
	AddItem(&info2);
}

void StoreWnd::AddItem(INVENITEMINFO* item)
{
	GameObject* pobj = GameObject::Instantiate();
	ItemSlot* pSlot = new ItemSlot((Slot::SLOTTYPE)item->_eSlotType);
	pobj->AddComponent(pSlot);

	int Index = -1;
	int cntX, cntY;
	//넣어줄 빈칸 찾기 
	for (int y = 0; y < _iCntY; ++y)
	{
		for (int x = 0; x < _iCntX; ++x)
		{
			int idx = x + (y * _iCntX);
			if (!_ItemSlot[idx])
			{
				int itemX = pSlot->GetItemInfo(0)->_iSlotCntX;
				int itemY = pSlot->GetItemInfo(0)->_iSlotCntY;
				// 현 위치 기준으로 넣을 수 없음
				if (x + itemX >= _iCntX) continue;
				if (y + itemY >= _iCntY) continue;
				
				bool chk = false;
				for (int i = 0; i < itemX; i++)
				{
					//가로 칸 없음
					if (_ItemSlot[idx + i])
					{
						chk = true;
						break;
					}
					for (int j = 0; j < itemY; j++)
					{//세로칸 없음
						if (_ItemSlot[idx + i + (j * _iCntX)])
						{
							chk = true;
							break;
						}
					}
				}
				if (chk) continue;
				else 
				{
					Index = idx;
					cntX = x;
					cntY = y;
					break;
				}

			}
			if (Index != -1) break;
		}
		if (Index != -1) break;
	}

	if (Index != -1)
	{
		D3DXVECTOR3 vPos(0, 0, 0);
		vPos.x = _vStartPos.x + (46 * cntX);
		vPos.y = _vStartPos.y + (32 * cntY);

		pobj->GetTransform()->SetWorldPosition(vPos);
		_StoreItem.push_back(std::pair(pobj, item));
	
		for (int i = 0; i <pSlot->GetItemInfo(0)->_iSlotCntX; i++)
		{
			//가로 칸 
			_ItemSlot[(Index + i)] = true;
			for (int j = 0; j < pSlot->GetItemInfo(0)->_iSlotCntY; j++)
			{//세로칸 
				_ItemSlot[(Index + i + (j * _iCntX))] = true;
			}
		}
	}
}

void StoreWnd::SellItem()
{
	POINT pt;
	GetCursorPos(&pt);

	LIST_ITEM::iterator iter = _StoreItem.begin();
	while (iter != _StoreItem.end())
	{
		ItemSlot* itemSlot = static_cast<ItemSlot*>(iter->first->GetComponent(COMPONENT_ID::BEHAVIOUR));
		RECT rc = itemSlot->GetItemRect();
		if (PtInRect(&rc, pt))
		{
			//인벤토리로 이동
			//골드 차감 

			
			//아이템 제거
			D3DXVECTOR3 vPos = iter->first->GetTransform()->GetWorldPosition();
			int x = (vPos.x-_vStartPos.x) / 46;
			int y = (vPos.y - _vStartPos.y) / 32;
			int Index = x + (y * _iCntX);

			SLOTINFO slotInfo = *(itemSlot->GetItemInfo(0));
			for (int i = 0; i <= slotInfo._iSlotCntX; i++)
			{
				//가로 칸 
				_ItemSlot[(Index + i)] = false;
				for (int j = 0; j <= slotInfo._iSlotCntX; j++)
				{//세로칸 
					_ItemSlot[(Index + i + (j * _iCntX))] = false;
				}
			}

			iter->first->Destroy();
		}
	}
}

void StoreWnd::OnClose()
{
	gameObject->SetActive(false);
}