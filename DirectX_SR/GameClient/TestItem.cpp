#include "pch.h"
#include "TestItem.h"
#include "GameObject.h"
#include "Image.h"
#include "Transform.h"
#include "Texture.h"

using namespace ce::UI;

TestItem::TestItem(GameObject* pobj, Slot::SLOTTYPE etype) noexcept
	: _pTest(pobj), _tInfo(0, 0, 0), _eType(etype)
{ 

}

TestItem::~TestItem() noexcept
{
	for (auto& iter : _vecSlot)
	{
		if (iter.second)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
}

void TestItem::Start(void) noexcept
{
	_pImage = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\4.png")); //
	const Texture* pTex = _pImage->GetTexture();

	_tInfo._iHeight = pTex->Height();;
	_tInfo._iWidth = pTex->Width();

	_pTest->AddComponent(_pImage);
	_pTest->SetSortOrder(2);
	_pTest->GetTransform()->SetWorldPosition(100, 100, 0);
	_pTest->SetActive(false);

	SLOTINFO* pSlot = nullptr;
	D3DXVECTOR3 startpos = _pTest->GetTransform()->GetWorldPosition();
	int iIndex = 0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			pSlot = new SLOTINFO;

			pSlot->_vPos.x = startpos.x + (pSlot->_iSlotSizeX * j);
			pSlot->_vPos.y = startpos.y + (pSlot->_iSlotSizeY * i);
			pSlot->_tRect.left = LONG(pSlot->_vPos.x - (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.top = LONG(pSlot->_vPos.y - (pSlot->_iSlotSizeY * 0.5f));
			pSlot->_tRect.right = LONG(pSlot->_vPos.x + (pSlot->_iSlotSizeX * 0.5f));
			pSlot->_tRect.bottom = LONG(pSlot->_vPos.y + (pSlot->_iSlotSizeY * 0.5f));

			GameObject* pGameobject = GameObject::Instantiate();
			Image* pTest = new Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Inventory\\Test.png"));
			pGameobject->AddComponent(pTest);
			pGameobject->SetSortOrder(1);
			pGameobject->GetTransform()->SetWorldPosition((float)pSlot->_tRect.left, (float)(pSlot->_tRect.top + (pSlot->_iSlotSizeY >> 1)), 0);
			pGameobject->SetActive(false);
			_vecSlot.push_back(std::make_pair(pGameobject, pSlot));
		}
	}
}

void TestItem::Update(float) noexcept
{
}

void TestItem::setTestPosition(D3DXVECTOR3 vtest)
{
	int Index = 0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			Index = i * 2 + j;
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
	_pTest->GetTransform()->SetWorldPosition(vtest);
}

void TestItem::SetPosition(D3DXVECTOR3 vpos)
{
	int Index = 0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
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
	_pTest->GetTransform()->SetWorldPosition(vpos);
}
