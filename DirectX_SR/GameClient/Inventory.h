#pragma once
#include "Behaviour.h"
#include "Slot.h"
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

private: bool	ItemClicked(POINT pt);
private: void	ItemMove(POINT pt);
private: void	SettingItem();
private: void	SlotCheck(std::vector<SLOTINFO*> pSlot, std::vector<std::pair<GameObject*, SLOTINFO*>> pitemSlot);

private: GameObject* _pInven = nullptr;
private: GameObject* _pTestItem = nullptr;
private: GameObject* _pTestItem2 = nullptr;

private: bool		 _bInvenCheck = false;
private: bool		 _bItemMoveCheck = false;
private: bool		 _bSlotCheck= true;

private: int		_iSlotCntX = 10;
private: int		_iSlotCntY = 4;

private: RECT		_tInvenRect;
private: std::vector<SLOTINFO*>		_vecSlot;
private: std::vector<Slot*>		_vecSlotGroup[(int)Slot::SLOTTYPE::END];

};

