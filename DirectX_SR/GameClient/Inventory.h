#pragma once
#include "Behaviour.h"
#include "Slot.h"
#include "ItemSlot.h"
#include "Item.h"
#include "Examine.h"

class TestItem;

class Inventory : public Behaviour
{
public: explicit Inventory() noexcept;
public: virtual ~Inventory() noexcept;

public:	void Start(void) noexcept override;
public: void Update(float) noexcept override;

public: void		GetItem(INVENITEMINFO* pInvenInfo); // 아이템 먹는 함수.
private: void		ItemEating(); // 먹었을때 작동하는함수
private: SLOTINFO*	DropAtEtingExamine(std::vector<SLOTINFO*> InvenSlot);

private: void		ItemCatch(POINT pt);
private: void		ItemCatchExamine(POINT pt);
private: void		ReCatchtoExamine(std::vector<SLOTINFO*> InvenSlot, D3DXVECTOR3 vpos);

private: void		ItemMove();

private: void		ItemDropAtMouse(POINT pt);
private: SLOTINFO*	DropAtMouseExamine(std::vector<SLOTINFO*> InvenSlot, POINT pt);

private: SLOTINFO*	ItemSwitching(POINT pt);

private: bool													_bItemCatchCheck = false;

private: std::vector<Slot*>										_vecSlotGroup[(int)Slot::SLOTTYPE::END];

private: std::vector<std::pair<INVENITEMINFO*, ItemSlot*>>		_vecItem;

#ifdef _DEBUG
private: std::vector<std::pair<GameObject*, SLOTINFO*>>			_vecItemslot;
#else
private: std::vector<SLOTINFO*>									_vecItemslot;
#endif // _DEBUG

private: SLOTINFO*												_pItemSlotInfo;
private: ItemSlot*												_pItem;
private: Examine*												_pExamine;
private: ItemSlot*												_pPriveItem;
private: bool													_bSwitchingcheck = false; // 수정
};

