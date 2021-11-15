#pragma once
#include "Behaviour.h"

class Slot : public Behaviour
{
public: enum class SLOTTYPE { NORMAL, HEAD, BODY, MAINWP, SECONDWP, GLOVES, LEGS, BELT, RING1, RING2, NECKLACE, END };

public: explicit Slot(SLOTTYPE etype);
public: virtual ~Slot();

public:	virtual void Start(void) noexcept override;
public: virtual void Update(float) noexcept override;

public: std::vector<SLOTINFO*>	GetSlot() { return _vecSlot; }
public: SLOTTYPE				GetSlotType() { return _eType; }
public: int						GetSlotCntX() { return _iSlotCntX; }
public: int						GetSlotCntY() { return _iSlotCntY; }

public: void					SlotFill(int ItemSlotX, int ItemSlotY);

private: std::vector<SLOTINFO*>	_vecSlot;
private: int					_iSlotCntX;
private: int					_iSlotCntY;
private: SLOTTYPE				_eType;
private: D3DXVECTOR3			_vStartPos;
};

