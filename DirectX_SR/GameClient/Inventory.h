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

public: bool				PickUpItems(ITEMDATA* pInvenInfo); // ������ �Դ� �Լ�. ���濡 �ڸ� ������ fase ��ȯ
public: void				PickUpGold(int Gold) { _iGold += Gold; } // ��� �ݴ� �Լ�
public: bool				BuyItem(int Gold); // ������ ���� �Լ� �� �����ϸ� false ��ȯ
public: bool				GetDropCheck() { return _bDropCheck; } // �κ��丮â���� �������� ��� ������ ��ȯ�ϴ� �Լ� TRUE�� ��� ��.
public: ITEMDATA*			UsingItem(POINT pt); // ���� R��ư Ŭ���� INVEITEMINFO* ��ȯ ������ Ŭ���� ������ �ش� ���Կ� �����ϰ� ������ ������ INVEITEMINFO* ��ȯ
public: ITEMDATA*			Dropitem(); // ������ �κ��丮 UI �ۿ��� ����ϸ� ����ϴ� ������ INVEITEMINFO* ��ȯ 

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
