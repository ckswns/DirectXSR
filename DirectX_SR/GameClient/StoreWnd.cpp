#include "pch.h"
#include "StoreWnd.h"
#include "ItemSlot.h"

#include "Transform.h"
#include "Image.h"
#include "Button.h"
using namespace ce::UI;
void StoreWnd::Start(void) noexcept
{
	_ItemSlot.assign(_iCntX * _iCntY, false);

	gameObject->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Store.png")));

	GameObject* CloseBtn = GameObject::Instantiate();
	CloseBtn->GetTransform()->SetParent(gameObject->GetTransform());
	CloseBtn->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Close_0.png")));
	Button<StoreWnd>* btn = static_cast<Button<StoreWnd>*>(gameObject->AddComponent(new Button<StoreWnd>(this)));
	btn->onMouseDown += &StoreWnd::OnClose;
	btn->SetTexture(nullptr, nullptr, ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Close_1.png"), nullptr);
	CloseBtn->SetSortOrder(2);
	//CloseBtn->GetTransform()->SetLocalPosition();



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
				// 현 위치 기준으로 넣을 수 없음
				if (x + pSlot->GetItemInfo()._iSlotCntX >= _iCntX) continue;
				if (y + pSlot->GetItemInfo()._iSlotCntY >= _iCntY) continue;
				
				bool chk = false;
				for (int i = 0; i <= pSlot->GetItemInfo()._iSlotCntX ; i++)
				{
					//가로 칸 없음
					if (_ItemSlot[idx + i])
					{
						chk = true;
						break;
					}
					for (int j = 0; j <= pSlot->GetItemInfo()._iSlotCntY; j++)
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
		}
	}

	if (Index != -1)
	{
		pobj->GetTransform()->SetWorldPosition((46 * cntX), (32 * cntY), 0);
		_StoreItem.push_back(std::pair(pobj, item));
	
		for (int i = 0; i <= pSlot->GetItemInfo()._iSlotCntX; i++)
		{
			//가로 칸 
			_ItemSlot[Index + i] = true;
			for (int j = 0; j <= pSlot->GetItemInfo()._iSlotCntY; j++)
			{//세로칸 
				_ItemSlot[Index + i + (j * _iCntX)] = true;
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
		RECT rc = iter->first->GetComponent(COMPONENT_ID::BEHAVIOUR)->GetItemRect();
		if (PtInRect(&rc, pt))
		{
			//인벤토리로 이동
			//골드 차감 

			//상점 아이템칸 비우기 
			D3DXVECTOR3 vPos = iter->first->GetTransform()->GetWorldPosition();
			int x = vPos.x / 46;
			int y = vPos.y / 32;
			int Index = x + (y * _iCntX);

			SLOTINFO slot = iter->first->GetComponent(COMPONENT_ID::BEHAVIOUR)->GetItemInfo();
			for (int i = 0; i <= pslot._iSlotCntX; i++)
			{
				//가로 칸 
				_ItemSlot[Index + i] = false;
				for (int j = 0; j <= slot._iSlotCntX; j++)
				{//세로칸 
					_ItemSlot[Index + i + (j * _iCntX)] = false;
				}
			}

			break;
		}
	}
}

void StoreWnd::OnClose()
{
	gameObject->SetActive(false);
}
