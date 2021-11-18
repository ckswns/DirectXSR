#pragma once
#include "Behaviour.h"

class ItemSlot;
class StoreWnd : public Behaviour
{
public:		using VEC_STORE = std::vector<bool>;
public:		using LIST_ITEM = std::list<std::pair<GameObject*, INVENITEMINFO*>>;

public:		explicit			StoreWnd() noexcept { __noop; }
public:		virtual				~StoreWnd(void) noexcept { __noop; }

public:		virtual void		Start(void) noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept { __noop; }

public:		void				AddItem(INVENITEMINFO* item);
public:		void				SellItem();
public:		void				OnClose();

private:	D3DXVECTOR3			_vStartPos;
private:	int					_iCntX = 10;
private:	int					_iCntY = 10;
private:	float				_fSizeX;
private:	float				_fSizeY;
private:	VEC_STORE			_ItemSlot;	// 상점 아이템칸
private:	LIST_ITEM			_StoreItem;	// 상점 소유 아이템 
};

