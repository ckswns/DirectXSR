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
	gameObject->SetSortOrder(0);

	GameObject* CloseBtn = GameObject::Instantiate();
	CloseBtn->GetTransform()->SetParent(gameObject->GetTransform());
	CloseBtn->AddComponent(new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Close_0.png")));
	Button<StoreWnd>* btn = static_cast<Button<StoreWnd>*>(CloseBtn->AddComponent(new Button<StoreWnd>(this)));
	btn->onMouseDown += &StoreWnd::Close;
	btn->SetTexture(nullptr, nullptr, ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Close_1.png"), nullptr);
	CloseBtn->SetSortOrder(1);
	CloseBtn->GetTransform()->SetLocalPosition(565,520,0);

	InitItem();
}

void StoreWnd::OnDestroy(void) noexcept
{
	_ItemSlot.clear();
	_StoreItem.clear();
}

void StoreWnd::InitItem()
{
	ITEMDATA* item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("HardArmor"), sizeof(ITEMDATA));
	AddItem(item);

	item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("BoneHelm"), sizeof(ITEMDATA));
	AddItem(item);
	item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("TowerShield"), sizeof(ITEMDATA));
	AddItem(item);
	item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("Gauntlets"), sizeof(ITEMDATA));
	AddItem(item);
	item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("PlatedBelt"), sizeof(ITEMDATA));
	AddItem(item);
	item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("Greaves"), sizeof(ITEMDATA));
	AddItem(item);
	item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("GrimWand"), sizeof(ITEMDATA));
	AddItem(item);
	item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("NokozanRelic"), sizeof(ITEMDATA));
	AddItem(item);

	item = new ITEMDATA();
	int iPotionCnt = CE_MATH::Random(5) + 1;
	memcpy(item, &GAMEDATAMANAGER->GetItemData("Potion"), sizeof(ITEMDATA));
	for (int i = 0; i < iPotionCnt; i++)
	{
		AddItem(item);
	}
	item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("JordanRing"), sizeof(ITEMDATA));
	AddItem(item);
	item = new ITEMDATA();
	memcpy(item, &GAMEDATAMANAGER->GetItemData("NagelRing"), sizeof(ITEMDATA));
	AddItem(item);

}

void StoreWnd::AddItem(ITEMDATA* item)
{
	GameObject* pobj = GameObject::Instantiate();
	StoreItem* pSlot = new StoreItem(item,this);
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
		pobj->SetSortOrder(4);
		pobj->GetTransform()->SetParent(GetTransform());
		//	pobj->SetActive(false);
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

void StoreWnd::Sell(GameObject* obj)
{
	LIST_ITEM::iterator iter = _StoreItem.begin();
	while (iter != _StoreItem.end())
	{
		if (iter->first == obj)
		{
			//골드 차감 
			if (_pInven->BuyItem(iter->second->buygold))
			{
				//인벤토리로 자리 확인
				if (!_pInven->PickUpItems(iter->second))
				{
					_pInven->PickUpGold(iter->second->buygold);
					return;
				}
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
				_StoreItem.erase(iter);
			}
			return;
		}
		iter++;
	}
}

void StoreWnd::Open(Player* player)
{
	if (_pPlayer == nullptr) 
	{
		_pPlayer = player;
		_pInven = _pPlayer->GetInventory();
	}

	gameObject->SetActive(true);
}

void StoreWnd::Close()
{
	gameObject->SetActive(false);
	_pPlayer->GetInpuHandler()->ClosedStore();
}
