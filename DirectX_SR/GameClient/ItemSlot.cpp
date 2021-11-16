#include "pch.h"
#include "ItemSlot.h"
#include "GameObject.h"
#include "Image.h"
#include "Transform.h"

using namespace ce::UI;

ItemSlot::ItemSlot(GameObject* pObj,Slot::SLOTTYPE eType, float fx, float fy) noexcept
	: _pOwner(pObj), _eType(eType)
{
	_vStartPos = D3DXVECTOR3(fx, fy, 0);

	switch (_eType)
	{
	case Slot::SLOTTYPE::HEAD:
		_iSlotCntX = 2;
		_iSlotCntY = 2;
		_iFlag |= 0x00000002;
		break;
	case Slot::SLOTTYPE::BODY:
		_iSlotCntX = 2;
		_iSlotCntY = 3;
		_iFlag |= 0x00000004;
		break;
	case Slot::SLOTTYPE::MAINWP:
		_iSlotCntX = 1;
		_iSlotCntY = 3;
		_iFlag |= 0x00000008;
		break;
	case Slot::SLOTTYPE::SECONDWP:
		_iSlotCntX = 2;
		_iSlotCntY = 3;
		_iFlag |= 0x00000010;
		break;
	case Slot::SLOTTYPE::GLOVES:
		_iSlotCntX = 2;
		_iSlotCntY = 2;
		_iFlag |= 0x00000020;
		break;
	case Slot::SLOTTYPE::LEGS:
		_iSlotCntX = 2;
		_iSlotCntY = 2;
		_iFlag |= 0x00000040;
		break;
	case Slot::SLOTTYPE::BELT:
		_iSlotCntX = 2;
		_iSlotCntY = 1;
		_iFlag |= 0x00000080;
		break;
	case Slot::SLOTTYPE::RING1:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_iFlag |= 0x00000100;
		break;
	case Slot::SLOTTYPE::NECKLACE:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_iFlag |= 0x00000200;
		break;
	case Slot::SLOTTYPE::POTION:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_iFlag |= 0x00000001;
		break;
	}
	
	Start();
}

ItemSlot::~ItemSlot() noexcept
{
}

void ItemSlot::Start(void) noexcept
{
	Image* pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\4.png")); //

	_pOwner->AddComponent(pImage);
	_pOwner->SetSortOrder(2);
	_pOwner->GetTransform()->SetWorldPosition(_vStartPos.x, _vStartPos.y, 0);
	_pOwner->SetActive(true);

	_vecSlot.reserve((size_t)_iSlotCntX * (size_t)_iSlotCntY);

	SLOTINFO* pSlot = nullptr;
	for (int i = 0; i < _iSlotCntY; ++i)
	{
		for (int j = 0; j < _iSlotCntX; ++j)
		{
			pSlot = new SLOTINFO;

			pSlot->_vPos.x = _vStartPos.x + (pSlot->_iSlotSizeX * j);
			pSlot->_vPos.y = _vStartPos.y + (pSlot->_iSlotSizeY * i);
			pSlot->_tRect.left = LONG(pSlot->_vPos.x - (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.top = LONG(pSlot->_vPos.y - (pSlot->_iSlotSizeY * 0.5f));
			pSlot->_tRect.right = LONG(pSlot->_vPos.x + (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.bottom = LONG(pSlot->_vPos.y + (pSlot->_iSlotSizeY * 0.5f));
			pSlot->_iFlag = _iFlag;

			GameObject* pGameobject = GameObject::Instantiate();
			Image* pTest = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Test.png"));
			pGameobject->AddComponent(pTest);
			pGameobject->SetSortOrder(1);
			pGameobject->GetTransform()->SetWorldPosition(pSlot->_tRect.left, pSlot->_tRect.top, 0);
			pGameobject->SetActive(true);

			_vecSlot.emplace_back(std::make_pair(pGameobject,pSlot));
		}
	}
}

void ItemSlot::Update(float) noexcept
{
	int i = 0;
}

void ItemSlot::setMousePosition(D3DXVECTOR3 vtest)
{
	int Index = 0;
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
	vtest.x -= float(_vecSlot[0].second->_iSlotSizeX >> 1);
	vtest.y -= float(_vecSlot[0].second->_iSlotSizeY >> 1);
	_pOwner->GetTransform()->SetWorldPosition(vtest);
}

void ItemSlot::SetInvenPosition(D3DXVECTOR3 vpos)
{
	int Index = 0;
	for (int i = 0; i < _iSlotCntY; ++i)
	{
		for (int j = 0; j < _iSlotCntX; ++j)
		{
			Index = i * 2 + j;
			_vecSlot[Index].second->_vPos.x = (vpos.x + (_vecSlot[Index].second->_iSlotSizeX >> 1)) + (_vecSlot[Index].second->_iSlotSizeX * j);
			_vecSlot[Index].second->_vPos.y = (vpos.y + (_vecSlot[Index].second->_iSlotSizeY >> 1)) + (_vecSlot[Index].second->_iSlotSizeY * i);
			_vecSlot[Index].second->_tRect.left = LONG(_vecSlot[Index].second->_vPos.x - (_vecSlot[Index].second->_iSlotSizeX * 0.5f));
			_vecSlot[Index].second->_tRect.top = LONG(_vecSlot[Index].second->_vPos.y - (_vecSlot[Index].second->_iSlotSizeY * 0.5f));
			_vecSlot[Index].second->_tRect.right = LONG(_vecSlot[Index].second->_vPos.x + (_vecSlot[Index].second->_iSlotSizeX * 0.5f));
			_vecSlot[Index].second->_tRect.bottom = LONG(_vecSlot[Index].second->_vPos.y + (_vecSlot[Index].second->_iSlotSizeY * 0.5f));
			_vecSlot[Index].first->GetTransform()->SetWorldPosition(float(_vecSlot[Index].second->_tRect.left), float(_vecSlot[Index].second->_tRect.top), 0);
		}
	}
	vpos.x += float(_vecSlot[0].second->_iSlotSizeX >> 1);
	_pOwner->GetTransform()->SetWorldPosition(vpos);
}