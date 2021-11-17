#include "pch.h"
#include "Slot.h"
#include "GameObject.h"
#include "Image.h"
#include "Transform.h"

using namespace ce::UI;
Slot::Slot(SLOTTYPE etype)
{
	_eType = etype;
	_iSlotCntX = 0;
	_iSlotCntY = 0;

	switch (_eType)
	{
	case Slot::SLOTTYPE::NORMAL:
		_iSlotCntX = 10;
		_iSlotCntY = 4;
		_vStartPos = D3DXVECTOR3(692.f, 370.f, 0);
		_iFlag |= 0x00000001;
		break;
	case Slot::SLOTTYPE::HEAD:
		_iSlotCntX = 2;
		_iSlotCntY = 2;
		_vStartPos = D3DXVECTOR3(875.f, 85.f, 0.f);
		_iFlag |= 0x00000002;
		break;
	case Slot::SLOTTYPE::BODY:
		_iSlotCntX = 2;
		_iSlotCntY = 3;
		_vStartPos = D3DXVECTOR3(875.f, 162.f, 0.f);
		_iFlag |= 0x00000004;
		break;
	case Slot::SLOTTYPE::MAINWP:
		_iSlotCntX = 2;
		_iSlotCntY = 4;
		_vStartPos = D3DXVECTOR3(693.f, 137.f, 0.f);;
		_iFlag |= 0x00000008;
		break;
	case Slot::SLOTTYPE::SECONDWP:
		_iSlotCntX = 2;
		_iSlotCntY = 4;
		_vStartPos = D3DXVECTOR3(1063.f, 137.f, 0.f);
		_iFlag |= 0x00000010;
		break;
	case Slot::SLOTTYPE::GLOVES:
		_iSlotCntX = 2;
		_iSlotCntY = 2;
		_vStartPos = D3DXVECTOR3(693.f, 279.f, 0.f);
		_iFlag |= 0x00000020;
		break;
	case Slot::SLOTTYPE::LEGS:
		_iSlotCntX = 2;
		_iSlotCntY = 2;
		_vStartPos = D3DXVECTOR3(1063.f, 279.f, 0.f);
		_iFlag |= 0x00000040;
		break;
	case Slot::SLOTTYPE::BELT:
		_iSlotCntX = 2;
		_iSlotCntY = 1;
		_vStartPos = D3DXVECTOR3(880.f, 279.f, 0.f);
		_iFlag |= 0x00000080;
		break;

	case Slot::SLOTTYPE::RING1:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_vStartPos = D3DXVECTOR3(811.f, 279.f, 0.f);
		_iFlag |= 0x00000100;
		break;
	case Slot::SLOTTYPE::RING2:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_vStartPos = D3DXVECTOR3(995.f, 279.f, 0.f);
		_iFlag |= 0x00000100;
		break;
	case Slot::SLOTTYPE::NECKLACE:
		_iSlotCntX = 1;
		_iSlotCntY = 1;
		_vStartPos = D3DXVECTOR3(993.f, 115.f, 0.f);
		_iFlag |= 0x00000200;
		break;
	}

	Start();
}

Slot::~Slot()
{
	for (auto& iter : _vecSlot)
	{
		if (iter)
		{
			delete iter;
			iter = nullptr;
		}
	}
}

void Slot::Start(void) noexcept
{
	_vecSlot.reserve((size_t)_iSlotCntX * (size_t)_iSlotCntY);

	SLOTINFO* pSlot = nullptr;
	int iIndex = 0;
	for (int i = 0; i < _iSlotCntY; ++i)
	{
		for (int j = 0; j < _iSlotCntX; ++j)
		{
			iIndex = i * _iSlotCntX + j;
			pSlot = new SLOTINFO;

			pSlot->_vPos.x = _vStartPos.x + (pSlot->_iSlotSizeX * j);
			pSlot->_vPos.y = _vStartPos.y + (pSlot->_iSlotSizeY * i);
			pSlot->_vPos.z = 0;
			pSlot->_tRect.left = LONG(pSlot->_vPos.x - (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.top = LONG(pSlot->_vPos.y - (pSlot->_iSlotSizeY * 0.5f));
			pSlot->_tRect.right = LONG(pSlot->_vPos.x + (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.bottom = LONG(pSlot->_vPos.y + (pSlot->_iSlotSizeY * 0.5f));
			pSlot->_iFlag = _iFlag;
			pSlot->_iIndex = iIndex;
			pSlot->_iSlotCntX = _iSlotCntX;
			pSlot->_iSlotCntY = _iSlotCntY;

#ifdef _DEBUG
			GameObject* pGameobject = GameObject::Instantiate();
			Image* pTest = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Test.png"));
			pGameobject->AddComponent(pTest);
			pGameobject->SetSortOrder(1);
			pGameobject->GetTransform()->SetWorldPosition(pSlot->_tRect.left, pSlot->_tRect.top, 0);
			pGameobject->SetActive(false);
#endif

			_vecSlot.push_back(pSlot);
		}
	}
	if (!_vecSlot.empty())
	{
		_SlotMaxRect.left = _vecSlot[0]->_tRect.left;
		_SlotMaxRect.top = _vecSlot[0]->_tRect.top;
		_SlotMaxRect.right = _vecSlot[iIndex]->_tRect.right;;
		_SlotMaxRect.bottom = _vecSlot[iIndex]->_tRect.bottom;;
	}
}

void Slot::Update(float) noexcept
{
}