#include "pch.h"
#include "ItemSlot.h"
#include "GameObject.h"
#include "Transform.h"
#include "Image.h"

ItemSlot::ItemSlot(Slot::SLOTTYPE eType, float fx, float fy) noexcept
	:  _eType(eType)
{
	_vStartPos = D3DXVECTOR3(fx, fy, 0);

	switch (_eType)
	{
	case Slot::SLOTTYPE::HEAD:
		_iSlotCntX = 2;
		_iSlotCntY = 2;
		_iFlag |= 0x00000002;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Head.png"));
		break;
	case Slot::SLOTTYPE::BODY:
		_iSlotCntX = 2;
		_iSlotCntY = 3;
		_iFlag |= 0x00000004;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Body.png"));
		break;
	case Slot::SLOTTYPE::MAINWP:
		_iSlotCntX = 1;
		_iSlotCntY = 3;
		_iFlag |= 0x00000008;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\MainWp.png"));
		break;
	case Slot::SLOTTYPE::SECONDWP:
		_iSlotCntX = 2;
		_iSlotCntY = 3;
		_iFlag |= 0x00000010;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\SecondWp.png"));
		break;
	case Slot::SLOTTYPE::GLOVES:
		_iSlotCntX = 2;
		_iSlotCntY = 2;
		_iFlag |= 0x00000020;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Gloves.png"));
		break;
	case Slot::SLOTTYPE::LEGS:
		_iSlotCntX = 2;
		_iSlotCntY = 2;
		_iFlag |= 0x00000040;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Legs.png"));
		break;
	case Slot::SLOTTYPE::BELT:
		_iSlotCntX = 2;
		_iSlotCntY = 1;
		_iFlag |= 0x00000080;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Belt.png"));
		break;
	case Slot::SLOTTYPE::RING1:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_iFlag |= 0x00000100;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Ring.png"));
		break;
	case Slot::SLOTTYPE::RING2:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_iFlag |= 0x00000100;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Ring2.png"));
		break;
	case Slot::SLOTTYPE::NECKLACE:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_iFlag |= 0x00000200;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Necklace.png"));
		break;
	case Slot::SLOTTYPE::POTION:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_iFlag |= 0x00000001;
		_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Potion.png"));
		break;
	}
}

ItemSlot::~ItemSlot() noexcept
{
}

void ItemSlot::Start(void) noexcept
{
	gameObject->AddComponent(_pImage);
	gameObject->SetSortOrder(2);
	gameObject->GetTransform()->SetWorldPosition(_vStartPos.x, _vStartPos.y, 0);
	gameObject->SetActive(true);

	_vecSlot.reserve((size_t)_iSlotCntX * (size_t)_iSlotCntY);
	int iIndex = 01;
	SLOTINFO* pSlot = nullptr;
#ifdef _DEBUG
	for (int i = 0; i < _iSlotCntY; ++i)
	{
		for (int j = 0; j < _iSlotCntX; ++j)
		{
			pSlot = new SLOTINFO;
			iIndex = i * _iSlotCntX + j;

			pSlot->_vPos.x = _vStartPos.x + (pSlot->_iSlotSizeX * j);
			pSlot->_vPos.y = _vStartPos.y + (pSlot->_iSlotSizeY * i);
			pSlot->_vPos.z = 0;
			pSlot->_tRect.left = LONG(pSlot->_vPos.x - (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.top = LONG(pSlot->_vPos.y - (pSlot->_iSlotSizeY * 0.5f));
			pSlot->_tRect.right = LONG(pSlot->_vPos.x + (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.bottom = LONG(pSlot->_vPos.y + (pSlot->_iSlotSizeY * 0.5f));
			pSlot->_iFlag = _iFlag;
			pSlot->_iSlotCntX = _iSlotCntX;
			pSlot->_iSlotCntY = _iSlotCntY;

			GameObject* pGameobject = GameObject::Instantiate();
			Image* pTest = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Test.png"));
			pGameobject->AddComponent(pTest);
			pGameobject->SetSortOrder(1);
			pGameobject->GetTransform()->SetWorldPosition(pSlot->_tRect.left, pSlot->_tRect.top, 0);
			pGameobject->SetActive(false);

			_vecSlot.emplace_back(std::make_pair(pGameobject, pSlot));
		}
	}

	if (!_vecSlot.empty())
	{
		_SlotMaxRect.left = _vecSlot[0].second->_tRect.left;
		_SlotMaxRect.top = _vecSlot[0].second->_tRect.top;
		_SlotMaxRect.right = _vecSlot[iIndex].second->_tRect.right;;
		_SlotMaxRect.bottom = _vecSlot[iIndex].second->_tRect.bottom;;
	}
#else
	for (int i = 0; i < _iSlotCntY; ++i)
	{
		for (int j = 0; j < _iSlotCntX; ++j)
		{
			pSlot = new SLOTINFO;
			iIndex = i * _iSlotCntX + j;

			pSlot->_vPos.x = _vStartPos.x + (pSlot->_iSlotSizeX * j);
			pSlot->_vPos.y = _vStartPos.y + (pSlot->_iSlotSizeY * i);
			pSlot->_vPos.z = 0;
			pSlot->_tRect.left = LONG(pSlot->_vPos.x - (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.top = LONG(pSlot->_vPos.y - (pSlot->_iSlotSizeY * 0.5f));
			pSlot->_tRect.right = LONG(pSlot->_vPos.x + (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.bottom = LONG(pSlot->_vPos.y + (pSlot->_iSlotSizeY * 0.5f));
			pSlot->_iFlag = _iFlag;
			pSlot->_iSlotCntX = _iSlotCntX;
			pSlot->_iSlotCntY = _iSlotCntY;

			_vecSlot.emplace_back(pSlot);
		}
	}

	if (!_vecSlot.empty())
	{
		_SlotMaxRect.left = _vecSlot[0]->_tRect.left;
		_SlotMaxRect.top = _vecSlot[0]->_tRect.top;
		_SlotMaxRect.right = _vecSlot[iIndex]->_tRect.right;;
		_SlotMaxRect.bottom = _vecSlot[iIndex]->_tRect.bottom;;
	}
#endif // _DEBUG

}

void ItemSlot::Update(float) noexcept
{
}

void ItemSlot::setMousePosition(D3DXVECTOR3 vtest)
{
	int Index = 0;
#ifdef _DEBUG
	for (int i = 0; i < _iSlotCntY; ++i)
	{
		for (int j = 0; j < _iSlotCntX; ++j)
		{
			Index = i * _iSlotCntX + j;
			_vecSlot[Index].second->_vPos.x = vtest.x + (_vecSlot[Index].second->_iSlotSizeX * j);
			_vecSlot[Index].second->_vPos.y = vtest.y + (_vecSlot[Index].second->_iSlotSizeY * i);
			_vecSlot[Index].second->_tRect.left = LONG(_vecSlot[Index].second->_vPos.x - (_vecSlot[Index].second->_iSlotSizeX * 0.5f));
			_vecSlot[Index].second->_tRect.top = LONG(_vecSlot[Index].second->_vPos.y - (_vecSlot[Index].second->_iSlotSizeY * 0.5f));
			_vecSlot[Index].second->_tRect.right = LONG(_vecSlot[Index].second->_vPos.x + (_vecSlot[Index].second->_iSlotSizeX * 0.5f));
			_vecSlot[Index].second->_tRect.bottom = LONG(_vecSlot[Index].second->_vPos.y + (_vecSlot[Index].second->_iSlotSizeY * 0.5f));
			_vecSlot[Index].first->GetTransform()->SetWorldPosition(float(_vecSlot[Index].second->_tRect.left), float(_vecSlot[Index].second->_tRect.top + (_vecSlot[Index].second->_iSlotSizeY >> 1)), 0);
		}
}

	if (!_vecSlot.empty())
	{
		_SlotMaxRect.left = _vecSlot[0].second->_tRect.left;
		_SlotMaxRect.top = _vecSlot[0].second->_tRect.top;
		_SlotMaxRect.right = _vecSlot[Index].second->_tRect.right;;
		_SlotMaxRect.bottom = _vecSlot[Index].second->_tRect.bottom;;
	}

	if (_iSlotCntX == 1 && _iSlotCntY == 1)
		vtest.x -= float(_vecSlot[0].second->_iSlotSizeX >> 2);
	else
		vtest.x -= float(_vecSlot[0].second->_iSlotSizeX >> 1);
#else
	for (int i = 0; i < _iSlotCntY; ++i)
	{
		for (int j = 0; j < _iSlotCntX; ++j)
		{
			Index = i * _iSlotCntX + j;
			_vecSlot[Index]->_vPos.x = vtest.x + (_vecSlot[Index]->_iSlotSizeX * j);
			_vecSlot[Index]->_vPos.y = vtest.y + (_vecSlot[Index]->_iSlotSizeY * i);
			_vecSlot[Index]->_tRect.left = LONG(_vecSlot[Index]->_vPos.x - (_vecSlot[Index]->_iSlotSizeX * 0.5f));
			_vecSlot[Index]->_tRect.top = LONG(_vecSlot[Index]->_vPos.y - (_vecSlot[Index]->_iSlotSizeY * 0.5f));
			_vecSlot[Index]->_tRect.right = LONG(_vecSlot[Index]->_vPos.x + (_vecSlot[Index]->_iSlotSizeX * 0.5f));
			_vecSlot[Index]->_tRect.bottom = LONG(_vecSlot[Index]->_vPos.y + (_vecSlot[Index]->_iSlotSizeY * 0.5f));
		}
	}

	if (!_vecSlot.empty())
	{
		_SlotMaxRect.left = _vecSlot[0]->_tRect.left;
		_SlotMaxRect.top = _vecSlot[0]->_tRect.top;
		_SlotMaxRect.right = _vecSlot[Index]->_tRect.right;;
		_SlotMaxRect.bottom = _vecSlot[Index]->_tRect.bottom;;
	}

	if (_iSlotCntX == 1 && _iSlotCntY == 1)
		vtest.x -= float(_vecSlot[0]->_iSlotSizeX >> 2);
	else
		vtest.x -= float(_vecSlot[0]->_iSlotSizeX >> 1);
#endif // _DEBUG


	gameObject->GetTransform()->SetWorldPosition(vtest);
}

void ItemSlot::SetInvenPosition(D3DXVECTOR3 vpos)
{
	int Index = 0;
#ifdef _DEBUG
	for (int i = 0; i < _iSlotCntY; ++i)
	{
		for (int j = 0; j < _iSlotCntX; ++j)
		{
			Index = i * _iSlotCntX + j;
			_vecSlot[Index].second->_vPos.x = (vpos.x + (_vecSlot[Index].second->_iSlotSizeX >> 1)) + (_vecSlot[Index].second->_iSlotSizeX * j);
			_vecSlot[Index].second->_vPos.y = (vpos.y + (_vecSlot[Index].second->_iSlotSizeY >> 1)) + (_vecSlot[Index].second->_iSlotSizeY * i);
			_vecSlot[Index].second->_tRect.left = LONG(_vecSlot[Index].second->_vPos.x - (_vecSlot[Index].second->_iSlotSizeX * 0.5f));
			_vecSlot[Index].second->_tRect.top = LONG(_vecSlot[Index].second->_vPos.y - (_vecSlot[Index].second->_iSlotSizeY * 0.5f));
			_vecSlot[Index].second->_tRect.right = LONG(_vecSlot[Index].second->_vPos.x + (_vecSlot[Index].second->_iSlotSizeX * 0.5f));
			_vecSlot[Index].second->_tRect.bottom = LONG(_vecSlot[Index].second->_vPos.y + (_vecSlot[Index].second->_iSlotSizeY * 0.5f));
			_vecSlot[Index].first->GetTransform()->SetWorldPosition(float(_vecSlot[Index].second->_tRect.left), float(_vecSlot[Index].second->_tRect.top), 0);
		}
	}

	if (!_vecSlot.empty())
	{
		_SlotMaxRect.left = _vecSlot[0].second->_tRect.left;
		_SlotMaxRect.top = _vecSlot[0].second->_tRect.top;
		_SlotMaxRect.right = _vecSlot[Index].second->_tRect.right;;
		_SlotMaxRect.bottom = _vecSlot[Index].second->_tRect.bottom;;
	}

	if (_iSlotCntX == 1 && _iSlotCntY == 1)
	{
		vpos.x += float(_vecSlot[0].second->_iSlotSizeX >> 2);
	}
	else
		vpos.x += float(_vecSlot[0].second->_iSlotSizeX >> 1);
#else
	for (int i = 0; i < _iSlotCntY; ++i)
	{
		for (int j = 0; j < _iSlotCntX; ++j)
		{
			Index = i * _iSlotCntX + j;
			_vecSlot[Index]->_vPos.x = (vpos.x + (_vecSlot[Index]->_iSlotSizeX >> 1)) + (_vecSlot[Index]->_iSlotSizeX * j);
			_vecSlot[Index]->_vPos.y = (vpos.y + (_vecSlot[Index]->_iSlotSizeY >> 1)) + (_vecSlot[Index]->_iSlotSizeY * i);
			_vecSlot[Index]->_tRect.left = LONG(_vecSlot[Index]->_vPos.x - (_vecSlot[Index]->_iSlotSizeX * 0.5f));
			_vecSlot[Index]->_tRect.top = LONG(_vecSlot[Index]->_vPos.y - (_vecSlot[Index]->_iSlotSizeY * 0.5f));
			_vecSlot[Index]->_tRect.right = LONG(_vecSlot[Index]->_vPos.x + (_vecSlot[Index]->_iSlotSizeX * 0.5f));
			_vecSlot[Index]->_tRect.bottom = LONG(_vecSlot[Index]->_vPos.y + (_vecSlot[Index]->_iSlotSizeY * 0.5f));
		}
	}

	if (!_vecSlot.empty())
	{
		_SlotMaxRect.left = _vecSlot[0]->_tRect.left;
		_SlotMaxRect.top = _vecSlot[0]->_tRect.top;
		_SlotMaxRect.right = _vecSlot[Index]->_tRect.right;;
		_SlotMaxRect.bottom = _vecSlot[Index]->_tRect.bottom;;
	}

	if (_iSlotCntX == 1 && _iSlotCntY == 1)
	{
		vpos.x += float(_vecSlot[0]->_iSlotSizeX >> 2);
	}
	else
		vpos.x += float(_vecSlot[0]->_iSlotSizeX >> 1);
#endif // _DEBUG


	gameObject->GetTransform()->SetWorldPosition(vpos);
}