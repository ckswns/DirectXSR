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

public: bool				PickUpItems(INVENITEMINFO* pInvenInfo); // 아이템 먹는 함수. 가방에 자리 없으면 fase 반환
public: void				PickUpGold(int Gold) { _iGold += Gold; } // 골드 줍는 함수
public: bool				BuyItem(int Gold); // 아이템 구매 함수 돈 부족하면 false 반환
public: bool				GetDropCheck() { return _bDropCheck; } // 인벤토리창에서 아이템을 드롭 했을때 반환하는 함수 false면 드랍 됨.
public: INVENITEMINFO*		UsingItem(POINT pt); // 포션 R버튼 클릭시 INVENINFO* 반환  포션 제외한 아이템 R버튼 클릭시 삭제됨.

private: bool				ItemEating();
private: SLOTINFO*			DropAtEtingExamine(std::vector<SLOTINFO*> InvenSlot);

private: void				ItemCatch(POINT pt);
private: void				ItemCatchExamine(POINT pt);
private: void				ReCatchtoExamine(std::vector<SLOTINFO*> InvenSlot, D3DXVECTOR3 vpos,bool bCheck);

private: void				ItemMove();

private: bool				ItemDropAtMouse(POINT pt);
private: SLOTINFO*			DropAtMouseExamine(std::vector<SLOTINFO*> InvenSlot, POINT pt);

private: SLOTINFO*			ItemSwitching(std::vector<SLOTINFO*> InvenSlot,POINT pt);

private: bool													_bItemCatchCheck = false;

private: std::vector<Slot*>										_vecSlotGroup[(int)Slot::SLOTTYPE::END];

private: std::vector<std::pair<INVENITEMINFO*, ItemSlot*>>		_vecItem;

#ifdef _DEBUG
private: std::vector<std::pair<GameObject*, SLOTINFO*>>			_vecItemslot;
#else
private: std::vector<SLOTINFO*>									_vecItemslot;
#endif // _DEBUG

private: SLOTINFO* _pItemSlotInfo;
private: ItemSlot*												_pItem;
private: Examine*												_pExamine;
private: SLOTINFO*												_pPriveSlotInfo;
private: ItemSlot*												_pPriveItem;
private: bool													_bSwitchingcheck = false;
private: bool													_bDropCheck = true;
private: int													_iGold;
private: UI::Text*												_pTexGold;
};

