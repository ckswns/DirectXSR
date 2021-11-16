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


private: bool	ItemCatch(POINT pt);
private: bool	ItemDrop(POINT pt);
private: void	ItemMove(POINT pt);
private: void	InvenslotCheck(POINT pt);


private: void	SettingItem(); // 수정해야함
private: void	SlotCheck(std::vector<SLOTINFO*> pSlot, std::vector<std::pair<GameObject*, SLOTINFO*>> pitemSlot);
private: void	ItemSlotCheck();

private: GameObject*	_pInven = nullptr;

private: bool			_bInvenCheck = false;
private: bool			_bItemCatchCheck = false;
private: bool			_bSlotCheck = true;

private: std::vector<Slot*>			_vecSlotGroup[(int)Slot::SLOTTYPE::END];

private: std::vector<ItemSlot*>		_vecItem;
private: std::vector<GameObject*>	_VecItem;

private: std::vector<std::pair<GameObject*, SLOTINFO*>> _vecItemslot;
private: ItemSlot*					_pItem;
private: SLOTINFO*					_pItemSlotInfo;

private: bool						_bCatch = false;
};

