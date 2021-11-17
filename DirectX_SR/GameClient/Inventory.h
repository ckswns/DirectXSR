#pragma once
#include "Behaviour.h"
#include "Slot.h"
#include "ItemSlot.h"

namespace ce
{
	namespace UI
	{
		class Image;
	}
}

class TestItem;

class Inventory : public Behaviour
{
public: explicit Inventory() noexcept;
public: virtual ~Inventory() noexcept;

public:	void Start(void) noexcept override;
public: void Update(float) noexcept override;

public: void	SetInvenShowCheck() { _bInvenCheck = !_bInvenCheck; }
public: bool	GetInvenShow() { return _bInvenCheck; }

private: void		ItemCatch(POINT pt);
private: void		ItemCatchExamine(POINT pt);
private: void		ItemMove();
private: void		ItemDrop(POINT pt);
private: void		ItemDroponMouse(POINT pt);
private: SLOTINFO* ItemExamine(std::vector<SLOTINFO*> InvenSlot);
private: void		CatchtoExamine(std::vector<SLOTINFO*> InvenSlot, D3DXVECTOR3 vpos);

private: SLOTINFO* Examine1X1(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY);
private: SLOTINFO* Examine1X3(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY);
private: SLOTINFO* Examine2X1(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY);
private: SLOTINFO* Examine2X2(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY);
private: SLOTINFO* Examine2X3(std::vector<SLOTINFO*> InvenSlot, int iInvenCntX, int iInvenCntY);

private: GameObject* _pInven = nullptr;

private: bool			_bInvenCheck = false;
private: bool			_bItemCatchCheck = false;
private: bool			_bSlotCheck = true;

private: std::vector<Slot*>			_vecSlotGroup[(int)Slot::SLOTTYPE::END];

private: std::vector<ItemSlot*>		_vecItem;

private: std::vector<std::pair<GameObject*, SLOTINFO*>> _vecItemslot;
private: ItemSlot* _pItem;
private: SLOTINFO* _pItemSlotInfo;

private: bool						_bCatch = false;
};

