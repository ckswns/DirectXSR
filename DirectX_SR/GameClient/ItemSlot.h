#pragma once
#include "Behaviour.h"
#include "Slot.h"

class ItemSlot : public Behaviour
{
public: explicit ItemSlot(GameObject* pObj, Slot::SLOTTYPE eType, float fx, float fy) noexcept;
public: virtual ~ItemSlot() noexcept;

public:	virtual	void Start(void) noexcept override;
public: virtual void Update(float) noexcept override;

public: void											setMousePosition(D3DXVECTOR3 vtest);
public: void											SetInvenPosition(D3DXVECTOR3 vpos);

public: RECT											GetItemRect() { return _SlotMaxRect; }
public: std::vector<std::pair<GameObject*, SLOTINFO*>>	GetItemSlot() { return _vecSlot; }
public: SLOTINFO* GetItemInfo(int iIndex) { return _vecSlot[iIndex].second; }

private: Slot::SLOTTYPE		_eType;

private: int				_iSlotCntX;
private: int				_iSlotCntY;
private: int				_iFlag;
private: D3DXVECTOR3		_vStartPos;
private: GameObject* _pOwner;
private: RECT				_SlotMaxRect;

private: std::vector<std::pair<GameObject*, SLOTINFO*>> _vecSlot;

};

