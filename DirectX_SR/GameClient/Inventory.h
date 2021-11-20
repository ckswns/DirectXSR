#pragma once
#include "Behaviour.h"
#include "Slot.h"
#include "ItemSlot.h"
#include "Item.h"
#include "Examine.h"

namespace ce
{
	namespace UI
	{
		class Text;
	}
}

class Inventory : public Behaviour
{
public: explicit Inventory() noexcept;
public: virtual ~Inventory() noexcept;

public:	void Start(void) noexcept override;
public: void Update(float) noexcept override;

public: bool				PickUpItems(ITEMDATA* pInvenInfo); // 아이템 먹는 함수. 가방에 자리 없으면 fase 반환
public: void				PickUpGold(int Gold) { _iGold += Gold; } // 골드 줍는 함수
public: bool				BuyItem(int Gold); // 아이템 구매 함수 돈 부족하면 false 반환
public: bool				GetDropCheck() { return _bDropCheck; } // 인벤토리창에서 아이템을 드롭 했을때 반환하는 함수 TRUE면 드랍 됨.
public: ITEMDATA*			UsingItem(POINT pt); // 포션 R버튼 클릭시 INVEITEMINFO* 반환 아이템 클릭시 아이템 해당 슬롯에 장착하고 장착된 아이템 INVEITEMINFO* 반환
public: ITEMDATA*			Dropitem(); // 아이템 인벤토리 UI 밖에서 드랍하면 드랍하는 아이템 INVEITEMINFO* 반환 

public: ITEMDATA*			GetItemInfo() { return _pItemInfo; }

private: void				ItemInfoBoxCheck(POINT pt);

private: bool				ItemEating();
private: SLOTINFO*			DropAtEtingExamine(std::vector<SLOTINFO*> InvenSlot);

private: void				ItemCatch(POINT pt);
private: void				ItemCatchExamine(POINT pt);
private: void				ReCatchtoExamine(std::vector<SLOTINFO*> InvenSlot, D3DXVECTOR3 vpos, bool bCheck);

private: void				ItemMove();

private: bool				ItemDropAtMouse(POINT pt);
private: SLOTINFO*			DropAtMouseExamine(std::vector<SLOTINFO*> InvenSlot, POINT pt);

private: SLOTINFO*			ItemSwitching(std::vector<SLOTINFO*> InvenSlot, POINT pt);
private: ITEMDATA*			EquipItemCheck(std::vector<std::pair<ITEMDATA*, ItemSlot*>> vItem, SLOTINFO* vslotinfo);

private: bool													_bItemCatchCheck = false;

private: std::vector<Slot*>										_vecSlotGroup[(int)Slot::SLOTTYPE::END];

private: std::vector<std::pair<ITEMDATA*, ItemSlot*>>		_vecItem;

#ifdef _DEBUG
private: std::vector<std::pair<GameObject*, SLOTINFO*>>			_vecItemslot;
#else
private: std::vector<SLOTINFO*>									_vecItemslot;
#endif // _DEBUG

private: SLOTINFO* _pItemSlotInfo;
private: ItemSlot* _pItem;
private: Examine* _pExamine;
private: SLOTINFO* _pPriveSlotInfo;
private: ItemSlot* _pPriveItem;
private: bool													_bSwitchingcheck = false;
private: bool													_bDropCheck = false;
private: int													_iGold;
private: UI::Text* _pTexGold;
private: ITEMDATA* _pItemInfo;
private: bool													_bMovecheck = false;
};
