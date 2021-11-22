#pragma once
#include "Behaviour.h"
#include "Slot.h"

namespace ce
{
	namespace UI
	{
		class Image;
	}
	class Transform;
}

class InfoBox;

class ItemSlot : public Behaviour
{
public: explicit ItemSlot(ITEMDATA* data, Transform* pParent, float fx = 0, float fy = 0) noexcept;
public: virtual ~ItemSlot() noexcept;

public:	virtual	void Start(void) noexcept override;
public: virtual void Update(float) noexcept override;
public:	void OnMouseDown(void) noexcept override;

public: void											setMousePosition(D3DXVECTOR3 vtest);
public: void											SetInvenPosition(D3DXVECTOR3 vpos);
public: void											ChagneActive(bool bChange) { gameObject->SetActive(bChange); }
public: void											DropItemSlot();

public: void											SetInfoBoxCheck(bool Check) { _InfoBoxCheck = Check; }

public: Slot::SLOTTYPE									GetSlotType() { return _eType; }
public: RECT											GetItemRect() { return _SlotMaxRect; }

#ifdef _DEBUG
public: std::vector<std::pair<GameObject*, SLOTINFO*>>	GetItemSlot() { return _vecSlot; }
public: SLOTINFO*										GetItemInfo(int iIndex) { return _vecSlot[iIndex].second; }
#else
public: std::vector<SLOTINFO*>							GetItemSlot() { return _vecSlot; }
public: SLOTINFO*										GetItemInfo(int iIndex) { return _vecSlot[iIndex]; }
#endif // _DEBUG


protected: InfoBox*			_pInfoBox;

private: Slot::SLOTTYPE		_eType;
private: int				_iSlotCntX;
private: int				_iSlotCntY;
private: int				_iFlag;
private: D3DXVECTOR3		_vStartPos;
private: RECT				_SlotMaxRect;
private: UI::Image*			_pImage;
private: Transform*			_pParent;
private: bool				_InfoBoxCheck = false;
private: ITEMDATA*			_ItemData;

#ifdef _DEBUG
private: std::vector<std::pair<GameObject*, SLOTINFO*>> _vecSlot; // Debug¿ë
#else
private: std::vector<SLOTINFO*>	_vecSlot;
#endif // _DEBUG
};

