#include "pch.h"
#include "StoreWnd.h"
#include "Inventory.h"
#include "StoreItem.h"
#include "Slot.h"
#include "Transform.h"
#include "Image.h"
#include "Button.h"
#include "RectTransform.h"

#include "Player.h"
#include "InputHandler.h"
using namespace ce::UI;
void StoreWnd::Start(void) noexcept
{
	_ItemSlot.assign((_iCntX * _iCntY), false);

	//칸 시작지점
	_vStartPos = D3DXVECTOR3(165, 148, 0);

	Image* img = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Store.png"));
	gameObject->AddComponent(img);
	gameObject->SetSortOrder(3);

	GameObject* CloseBtn = GameObject::Instantiate();
	CloseBtn->GetTransform()->SetParent(gameObject->GetTransform());
	CloseBtn->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Close_0.png")));
	Button<StoreWnd>* btn = static_cast<Button<StoreWnd>*>(CloseBtn->AddComponent(new Button<StoreWnd>(this)));
	btn->onMouseDown += &StoreWnd::Close;
	btn->SetTexture(nullptr, nullptr, ASSETMANAGER->GetTextureData("Asset\\UI\\Game\\Close_1.png"), nullptr);
	CloseBtn->SetSortOrder(4);
	CloseBtn->GetTransform()->SetLocalPosition(565,520,0);

	INVENITEMINFO* info = new INVENITEMINFO((int)Slot::SLOTTYPE::POTION);
	AddItem(info);
	info = new INVENITEMINFO((int)Slot::SLOTTYPE::BODY);
	AddItem(info);
}

void StoreWnd::OnDestroy(void) noexcept
{
	_ItemSlot.clear();
	_StoreItem.clear();
}

void StoreWnd::AddItem(INVENITEMINFO* item)
{
	GameObject* pobj = GameObject::Instantiate();
	StoreItem* pSlot = new StoreItem((Slot::SLOTTYPE)item->_eSlotType,this);
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
				if (x + itemX > _iCntX) continue;
				if (y + itemY > _iCntY) continue;
				
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
		//pobj->SetSortOrder(4);
		pobj->SetActive(false);
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
	else//빈칸없음
	{
		pobj->Destroy();
	}
}

/*
void StoreWnd::SellItem()
{
	POINT pt;
	GetCursorPos(&pt);

	ScreenToClient(g_hWnd, &pt);
	LIST_ITEM::iterator iter = _StoreItem.begin();
	while (iter != _StoreItem.end())
	{
		GameObject* obj = iter->first;
		ItemSlot* itemSlot = static_cast<ItemSlot*>(obj->GetComponent(COMPONENT_ID::BEHAVIOUR));
		
		D3DXVECTOR3 vPos = obj->GetTransform()->GetWorldPosition();
		RECT rc = itemSlot->GetItemRect();
		rc.left += vPos.x;
		rc.right += vPos.x;
		rc.top += vPos.y;
		rc.bottom += vPos.y;

	//	RectTransform* rectTransform = static_cast<RectTransform*>((iter->first)->GetComponent(COMPONENT_ID::RECT_TRANSFORM));

	//	RECT rc = rectTransform->GetPickingRect();
		if (PtInRect(&rc, pt))
		{
			//인벤토리로 이동
			//_pInven->GetItem(iter->second);	
			//골드 차감 
			
			//아이템 제거
		//	D3DXVECTOR3 vPos = obj->GetTransform()->GetWorldPosition();
			int x = (vPos.x-_vStartPos.x) / 46;
			int y = (vPos.y - _vStartPos.y) / 32;
			int Index = x + (y * _iCntX);

			SLOTINFO slotInfo = *(itemSlot->GetItemInfo(0));
			for (int i = 0; i < slotInfo._iSlotCntX; i++)
			{
				//가로 칸 
				_ItemSlot[(Index + i)] = false;
				for (int j = 0; j < slotInfo._iSlotCntX; j++)
				{//세로칸 
					_ItemSlot[(Index + i + (j * _iCntX))] = false;
				}
			}

	//		obj->Destroy();
	//		iter->first = nullptr;
	//		delete iter->second;
			_StoreItem.erase(iter);
			break;
		}
	}
}
*/

void StoreWnd::Sell(GameObject* obj)
{
	LIST_ITEM::iterator iter = _StoreItem.begin();
	while (iter != _StoreItem.end())
	{
		if (iter->first == obj)
		{
			//인벤토리로 이동
			_pInven->GetItem(iter->second);	
			//골드 차감 

			//아이템 제거
			D3DXVECTOR3 vPos = obj->GetTransform()->GetWorldPosition();
			int x = (vPos.x - _vStartPos.x) / 46;
			int y = (vPos.y - _vStartPos.y) / 32;
			int Index = x + (y * _iCntX);

			StoreItem* itemSlot = static_cast<StoreItem*>(obj->GetComponent(COMPONENT_ID::BEHAVIOUR));
			SLOTINFO slotInfo = *(itemSlot->GetItemInfo(0));
			for (int i = 0; i < slotInfo._iSlotCntX; i++)
			{
				//가로 칸 
				_ItemSlot[(Index + i)] = false;
				for (int j = 0; j < slotInfo._iSlotCntX; j++)
				{//세로칸 
					_ItemSlot[(Index + i + (j * _iCntX))] = false;
				}
			}

			obj->Destroy();
			//		iter->first = nullptr;
			//		delete iter->second;
			iter = _StoreItem.erase(iter);
			break;
		}
		iter++;
	}
}

void StoreWnd::Open(Player* player)
{
	_pPlayer = player;
	_pInven = _pPlayer->GetInventory();

	gameObject->SetActive(true);

	LIST_ITEM::iterator iter = _StoreItem.begin();
	while (iter != _StoreItem.end())
	{
		iter->first->SetActive(true);
		iter++;
	}
}

void StoreWnd::Close()
{
	gameObject->SetActive(false);

	LIST_ITEM::iterator iter = _StoreItem.begin();
	while (iter != _StoreItem.end())
	{
		iter->first->SetActive(false);
		iter++;
	}

	_pPlayer->GetInpuHandler()->ClosedStore();
}
