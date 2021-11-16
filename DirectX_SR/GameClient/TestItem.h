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

class TestItem : public Behaviour
{
public: explicit TestItem(GameObject* pGameobjct, Slot::SLOTTYPE etype) noexcept;
public: virtual ~TestItem() noexcept;

public:	void Start(void) noexcept override;
public:	void Update(float) noexcept override;

public: void setTestPosition(D3DXVECTOR3 vtest);
public: void SetPosition(D3DXVECTOR3 vpos);

public: std::vector<std::pair<GameObject*, SLOTINFO*>>	GetItemSlot() { return _vecSlot; }
public: Slot::SLOTTYPE									GetItemType() { return _eType; }

private: GameObject* _pTest;
private: ITEMINFO	 _tInfo;
private: RECT		 _tRect;
private: UI::Image*	_pImage;

private: std::vector<std::pair<GameObject*, SLOTINFO*>> _vecSlot;
private: Slot::SLOTTYPE									_eType;

};

