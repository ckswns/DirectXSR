#pragma once
#include "Behaviour.h"

class ItemSlot;
class Inventory;
class Player;
class StoreWnd : public Behaviour
{
public:		using VEC_STORE = std::vector<bool>;
public:		using LIST_ITEM = std::list<std::pair<GameObject*, ITEMDATA*>>;

public:		explicit			StoreWnd() noexcept { __noop; }
public:		virtual				~StoreWnd(void) noexcept { __noop; }

public:		virtual void		Start(void) noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept { __noop; }
public:		virtual void		OnDestroy(void) noexcept;
private:	void				InitItem();

public:		void				AddItem(ITEMDATA* item);
public:		void				Sell(GameObject* obj);
public:		void				Open(Player* player);
public:		void				Close();


private:	D3DXVECTOR3			_vStartPos;
private:	int					_iCntX = 10;
private:	int					_iCntY = 10;
private:	float				_fSizeX;
private:	float				_fSizeY;
private:	VEC_STORE			_ItemSlot;	// ���� ������ĭ
private:	LIST_ITEM			_StoreItem;	// ���� ���� ������ 
private:	Inventory*			_pInven;
private:	Player*				_pPlayer;
};

