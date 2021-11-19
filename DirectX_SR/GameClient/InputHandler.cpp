#include "pch.h"
#include "InputHandler.h"

#include "AttackCommand.h"
#include "MoveCommand.h"
#include "SkillCommand.h"

#include "GameObject.h"
#include "Player.h"
#include "Item.h"

#include "Camera.h"
#include "Transform.h"
#include "SphereCollider.h"
#include "TargetCamera.h"
#include "Inventory.h"
#include "StoreNPC.h"
InputHandler::InputHandler(Player* player) noexcept
	:_pPlayer(player), _vDir(0, 0, 0), _bInven(false),
	_bFPV(false), _bAtt(false), _bDown(false), _bLBSkill(false), _bRBSkill(false), _bUsingStore(false)
{
	
}

void InputHandler::Start(void) noexcept
{
	_pPlayerObj = _pPlayer->GetGameObject();
	_pPlayerTrans = _pPlayerObj->GetTransform();

	_pLBCommand = new AttackCommand();
	_pRBCommand = new AttackCommand();
	_pMoveCommand = new MoveCommand();
}

void InputHandler::Update(float fElapsedTime) noexcept
{
	if (!_pTargetCamera)
	{
		_pCameraTrans = Camera::GetMainCamera()->GetTransform();
		_pTargetCamera = static_cast<TargetCamera*>(_pCameraTrans->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));
	}

	if (!_bUsingStore)
	{
		//시점 변경
		if (INPUT->GetKeyDown(VK_TAB))
		{
			if (_bFPV) _bFPV = false;
			else	   _bFPV = true;

			_pPlayer->SetFPV();

			_pTargetCamera->ChangeView();
		}

		if (INPUT->GetKeyDown('I'))
		{
			if (_bInven)
			{
				_bInven = false;
				_pPlayer->GetInventory()->GetGameObject()->SetActive(false);
			}
			else
			{
				_bInven = true;
				_pPlayer->GetInventory()->GetGameObject()->SetActive(true);
			}
		}

		if (!_bFPV) //3인칭 조작
		{
			//마우스 피킹 
			Ray ray = Camera::GetMainCamera()->ScreenPointToRay(INPUT->GetMousePosition());
			RaycastHit hit;

			bool lbtnDown = false;

			if (INPUT->GetKeyStay(VK_LBUTTON) && _isKeyDown == false)
			{
				lbtnDown = true;
				_isKeyDown = true;
			}
			else if (INPUT->GetKeyUp(VK_LBUTTON))
			{
				_isKeyDown = false;
			}

			if (lbtnDown)
			{
				if (_bInven)
				{
					POINT pt;
					GetCursorPos(&pt);
					ScreenToClient(g_hWnd, &pt);

					if (pt.x > WINCX * 0.5)
					{
						return;
					}
				}


				//마우스 피킹 
				if (Physics::Raycast(ray, hit, GameObjectLayer::ALPHA))
				{
					//몬스터인 경우 공격 
					if (hit.collider->GetGameObject()->GetTag() == GameObjectTag::MONSTER)
						_pLBCommand->Execute(_pPlayerObj, hit.point, hit.transform);
					else if (hit.collider->GetGameObject()->GetName() == "Item")
					{
						//아이템인 경우 줍기 
						//아이템 정보 
						INVENITEMINFO* ivenItem = static_cast<Item*>(hit.collider->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR))->GetItem();
						//인벤토리에 아이템 추가 
						if (_pPlayer->GetInventory()->PickUpItems(ivenItem))
							hit.collider->GetGameObject()->Destroy();
					}
					else if (hit.collider->GetGameObject()->GetName() == "Gold")
					{
						INVENITEMINFO* ivenItem = static_cast<Item*>(hit.collider->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR))->GetItem();
						_pPlayer->GetInventory()->PickUpGold(ivenItem->_iGold);
						hit.collider->GetGameObject()->Destroy();
					}
					else if (hit.collider->GetGameObject()->GetName() == "StoreNPC")
					{
						D3DXVECTOR3 vDir = hit.transform->GetWorldPosition() - _pPlayerTrans->GetWorldPosition();
						if (D3DXVec3Length(&vDir) < 1)
						{
							_bUsingStore = true;
							static_cast<StoreNPC*>(hit.collider->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR))->OnClick(_pPlayer);

							//인벤토리도 같이 열림 
							_bInven = true;
							_pPlayer->GetInventory()->GetGameObject()->SetActive(true);
						}
					}
					else if (Physics::Raycast(ray, hit, GameObjectLayer::BACKGROUND))
					{
						if (_bLBSkill)	//스킬인 경우
							_pLBCommand->Execute(_pPlayerObj, hit.point, hit.transform);
						else
							_pMoveCommand->Execute(_pPlayerObj, hit.point);
					}
				}
				else if (Physics::Raycast(ray, hit, GameObjectLayer::BACKGROUND))
				{
					if (_bLBSkill)	//스킬인 경우
						_pLBCommand->Execute(_pPlayerObj, hit.point, hit.transform);
					else
						_pMoveCommand->Execute(_pPlayerObj, hit.point);
				}
			}
			//else if (INPUT->GetKeyStay(VK_LBUTTON))
			//{
			//	if (Physics::Raycast(ray, hit, GameObjectLayer::BACKGROUND))
			//	{
			//		if (!_bLBSkill)	//스킬인 경우
			//			_pMoveCommand->Execute(_pPlayerObj, hit.point);
			//	}
			//}
			else if (INPUT->GetKeyDown(VK_RBUTTON))
			{
				if (_bInven)
				{
					POINT pt;
					GetCursorPos(&pt);
					ScreenToClient(g_hWnd, &pt);

					if (pt.x > WINCX * 0.5)
					{
						INVENITEMINFO* potion = nullptr;
						potion = _pPlayer->GetInventory()->UsingItem(pt);
						if (potion->_eSlotType == (int)Slot::SLOTTYPE::POTION)
						{
							//플레이어 회복
							_pPlayer->DrinkPotion(potion->_iValue);
						}

						return;
					}
				}
				Ray ray = Camera::GetMainCamera()->ScreenPointToRay(INPUT->GetMousePosition());
				RaycastHit hit;
				if (Physics::Raycast(ray, hit, GameObjectLayer::BACKGROUND))
				{
					if (_bRBSkill)	//스킬인 경우
						_pRBCommand->Execute(_pPlayerObj, hit.point, hit.transform);
					else
						_pMoveCommand->Execute(_pPlayerObj, hit.point);
				}
				else if (Physics::Raycast(ray, hit, GameObjectLayer::OBJECT))
				{
					//몬스터인 경우 공격 
					if (hit.collider->GetGameObject()->GetTag() == GameObjectTag::MONSTER)
						_pRBCommand->Execute(_pPlayerObj, hit.point, hit.transform);

				}
			}
		}
		//1인칭 조작
		else
		{
			D3DXVECTOR3 vLook;
			vLook.x = _pPlayerTrans->GetWorldMatrix()._31;
			vLook.y = _pPlayerTrans->GetWorldMatrix()._32;
			vLook.z = _pPlayerTrans->GetWorldMatrix()._33;

			D3DXVECTOR3 vRight;
			vRight.x = _pPlayerTrans->GetWorldMatrix()._11;
			vRight.y = _pPlayerTrans->GetWorldMatrix()._12;
			vRight.z = _pPlayerTrans->GetWorldMatrix()._13;
			//----------------- 좌우 회전 ----------------------//
			if (INPUT->GetKeyDown(VK_MBUTTON))
			{
				_bDown = true;
				GetCursorPos(&_ptStart);
			}
			else if (INPUT->GetKeyStay(VK_MBUTTON) && _bDown)
			{
				POINT ptEnd;
				GetCursorPos(&ptEnd);

				int dx = ptEnd.x - _ptStart.x;

				_pPlayerTrans->Rotate(0, dx * fElapsedTime, 0);
				_pCameraTrans->Rotate(0, dx * fElapsedTime, 0);

				_ptStart = ptEnd;
			}
			else
				_bDown = false;

			//---------------- 공격 (스킬사용) ---------------------//
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				_bAtt = true;
				_pLBCommand->Execute(_pPlayerObj, vLook);
			}
			else if (INPUT->GetKeyDown(VK_RBUTTON))
			{
				_bAtt = true;
				_pRBCommand->Execute(_pPlayerObj, vLook);
			}
			else
			{
				//--------------- 캐릭터 이동 --------------------//
				_vDir = D3DXVECTOR3(0, 0, 0);

				if (INPUT->GetKeyStay('W'))
					_vDir = vLook;
				else if (INPUT->GetKeyStay('S'))
					_vDir = -vLook;
				else
					_vDir = D3DXVECTOR3(0, 0, 0);

				if (INPUT->GetKeyStay('A'))
				{
					_vDir -= vRight;
				}
				else if (INPUT->GetKeyStay('D'))
				{
					_vDir += vRight;
				}

				if (D3DXVec3Length(&_vDir) > 0)
				{
					_bAtt = false;
					D3DXVec3Normalize(&_vDir, &_vDir);
					_pMoveCommand->Execute(_pPlayerObj, _vDir);
				}
				else if (!_bAtt)
				{
					_pPlayer->SetState(PLAYER_STAND, BACK);
				}
			}
		}
	}
}

void InputHandler::OnDestroy(void) noexcept
{
	delete _pLBCommand;
	_pLBCommand = nullptr;
	delete _pRBCommand;
	_pRBCommand = nullptr;
	delete _pMoveCommand;
	_pMoveCommand = nullptr;
}

void InputHandler::SetMouseBtn(bool isLeft, SKILL_ID id)
{
	if (id == SKILL_END)
	{
		if (isLeft) 
		{
			_bLBSkill = false;
			_pLBCommand = new AttackCommand();
		}
		else 
		{
			_bRBSkill = false;
			_pRBCommand = new AttackCommand();
		}
	}
	else
	{
		if (isLeft) 
		{
			_bLBSkill = true;
			_pLBCommand = new SkillCommand();
			static_cast<SkillCommand*>(_pLBCommand)->SetSkill(id);
		}
		else
		{
			_bRBSkill = true;
			_pRBCommand = new SkillCommand();
			static_cast<SkillCommand*>(_pRBCommand)->SetSkill(id);
		}
	}
}

void InputHandler::ClosedStore()
{
	_bUsingStore = false;
	_bInven = false;
	_pPlayer->GetInventory()->GetGameObject()->SetActive(false);
}
