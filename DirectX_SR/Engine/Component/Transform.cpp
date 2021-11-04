#include "pch.h"
#include "Transform.h"
#include "../Base/GameObject.h"

namespace ce
{
	Transform::Transform(GameObject* const owner) noexcept
		: Component(owner, COMPONENT_ID::TRANSFORM, true),
		_worldPosition(0, 0, 0),
		_localPosition(0, 0, 0),
		_localScale(1, 1, 1),
		_worldEulerAngle(0, 0, 0),
		_localEulerAngle(0, 0, 0),
		_pParent(nullptr),
		_vecChild({}),
		_bDirtyPosition(false),
		_bDirtyRotation(false),
		_bDirtyScale(false),
		_bChangedPosition(false),
		_bChangedRotation(false),
		_bChangedScale(false),
		_bChanged(false)
	{
		D3DXMatrixIdentity(&_matPosition);
		D3DXMatrixIdentity(&_matRotation);
		D3DXMatrixIdentity(&_matScale);
		D3DXMatrixIdentity(&_matWorld);
	}

	void Transform::FixedUpdate(float) noexcept
	{
		__noop;
	}

	void Transform::Update(float) noexcept
	{
		__noop;
	}

	void Transform::LateUpdate(float) noexcept
	{
		if (nullptr != _pParent)
		{
			_bChangedPosition = _pParent->_bChangedPosition;
			_bChangedRotation = _pParent->_bChangedRotation;
			_bChangedScale = _pParent->_bChangedScale;
			_bChanged = _pParent->_bChanged;
		}
		else
		{
			_bChangedPosition = _bChangedRotation = _bChangedScale = _bChanged = false;
		}

		if (_bDirtyPosition)
		{
			_bDirtyPosition = false;
			_bChangedPosition = _bChanged = true;
			D3DXMatrixIdentity(&_matPosition);
			D3DXMatrixTranslation(&_matPosition, _localPosition.x, _localPosition.y, _localPosition.z);
		}

		if (_bDirtyRotation)
		{
			_bDirtyRotation = false;
			_bChangedRotation = _bChanged = true;
			D3DXMatrixIdentity(&_matRotation);

			//D3DXMatrixRotationYawPitchRoll(&_matRotation, _localEulerAngle.y, _localEulerAngle.x, _localEulerAngle.z);
			D3DXQuaternionRotationYawPitchRoll(&_quatRotation, _localEulerAngle.y, _localEulerAngle.x, _localEulerAngle.z);
			D3DXMatrixRotationQuaternion(&_matRotation, &_quatRotation);
		}

		if (_bDirtyScale)
		{
			_bDirtyScale = false;
			_bChangedScale = _bChanged = true;

			D3DXMatrixIdentity(&_matScale);
			D3DXMatrixScaling(&_matScale, _localScale.x, _localScale.y, _localScale.z);
		}

		if (_bChanged)
		{
			_matWorld = _matScale * _matRotation * _matPosition;

			if (nullptr != _pParent)
			{
				_matWorld *= _pParent->_matWorld;
			}

			for (int i = 0; i < _vecChild.size(); i++)
			{
				_vecChild[i]->ForcedReCalMat();
			}
		}
	}

	void Transform::Release(void) noexcept
	{
		while (_vecChild.size() != 0)
		{
			_vecChild[0]->SetParent(nullptr);
		}

		if (_pParent != nullptr)
		{
			_pParent->RemoveChild(this);
		}

		_vecChild.clear();
		std::vector<Transform*>().swap(_vecChild);
	}

	Transform* Transform::GetParent(void) noexcept
	{
		return _pParent;
	}

	const Transform* Transform::GetParent(void) const noexcept
	{
		return _pParent;
	}

	std::vector<const Transform*> Transform::GetParents(void) const noexcept
	{
		std::vector<const Transform*> parents;

		FindParentRecur(this, parents);

		return parents;
	}

	const std::vector<Transform*>& Transform::GetChilds(void) const noexcept
	{
		return _vecChild;
	}

	void Transform::SetParent(IN Transform* parent) noexcept
	{
		if (_pParent)
		{
			_pParent->RemoveChild(this);
		}

		_pParent = parent;

		if (_pParent)
		{
			_pParent->SetChild(this);

			bool b = _pOwner->GetActive();
			_pOwner->SetActive(!b);
			_pOwner->SetActive(b);
		}
	}

	D3DXVECTOR3 Transform::GetForward(void) const noexcept
	{
		return D3DXVECTOR3(_matWorld._31, _matWorld._32, _matWorld._33);
	}

	D3DXVECTOR3 Transform::GetUp(void) const noexcept
	{
		return D3DXVECTOR3(_matWorld._21, _matWorld._22, _matWorld._23);
	}

	D3DXVECTOR3 Transform::GetRight(void) const noexcept
	{
		return D3DXVECTOR3(_matWorld._11, _matWorld._12, _matWorld._13);
	}

	void Transform::Translate(const D3DXVECTOR3& position, bool isLocal)
	{
		if (isLocal)
			SetLocalPosition(_localPosition + position);
		else
			SetWorldPosition(_worldPosition + position);
	}

	void Transform::Translate(float x, float y, float z, bool isLocal)
	{
		D3DXVECTOR3 position = { x, y, z };

		if (isLocal)
			SetLocalPosition(_localPosition + position);
		else
			SetWorldPosition(_worldPosition + position);
	}

	void Transform::Rotate(const D3DXVECTOR3& euler, bool isLocal)
	{
		if (isLocal)
			SetLocalEulerAngle(_localEulerAngle + euler);
		else
			SetWorldEulerAngle(_worldEulerAngle + euler);
	}

	void Transform::Rotate(float x, float y, float z, bool isLocal)
	{
		D3DXVECTOR3 euler = { x, y, z };

		if (isLocal)
			SetLocalEulerAngle(_localEulerAngle + euler);
		else
			SetWorldEulerAngle(_worldEulerAngle + euler);
	}

	void Transform::SetWorldPosition(const D3DXVECTOR3& worldPosition) noexcept
	{
		_bDirtyPosition = (_worldPosition != worldPosition);

		_worldPosition = _localPosition = worldPosition;

		if (_pParent)
		{
			_localPosition = worldPosition - _pParent->_worldPosition;
		}

		OnParentPosChanged();
	}

	void Transform::SetWorldPosition(float x, float y, float z) noexcept
	{
		SetWorldPosition(D3DXVECTOR3(x, y, z));
	}

	void Transform::SetLocalPosition(const D3DXVECTOR3& localPosition) noexcept
	{
		_bDirtyPosition = (_localPosition != localPosition);

		_worldPosition = _localPosition = localPosition;

		if (_pParent)
		{
			_worldPosition = localPosition + _pParent->_worldPosition;
		}

		OnParentPosChanged();
	}

	void Transform::SetLocalPosition(float x, float y, float z) noexcept
	{
		SetLocalPosition(D3DXVECTOR3(x, y, z));
	}

	void Transform::SetWorldEulerAngle(const D3DXVECTOR3& eulerAngle) noexcept
	{
		_bDirtyRotation = (_worldEulerAngle != eulerAngle);

		_worldEulerAngle = _localEulerAngle = eulerAngle;

		if (_pParent)
		{
			_localEulerAngle = eulerAngle - _pParent->_worldEulerAngle;
		}
	}

	void Transform::SetWorldEulerAngle(float x, float y, float z) noexcept
	{
		SetWorldEulerAngle(D3DXVECTOR3(x, y, z));
	}

	void Transform::SetLocalEulerAngle(const D3DXVECTOR3& eulerAngle) noexcept
	{
		_bDirtyRotation = (_localEulerAngle != eulerAngle);

		_worldEulerAngle = _localEulerAngle = eulerAngle;

		if (_pParent)
		{
			_worldEulerAngle = eulerAngle + _pParent->_worldEulerAngle;
		}
	}

	void Transform::SetLocalEulerAngle(float x, float y, float z) noexcept
	{
		SetLocalEulerAngle(D3DXVECTOR3(x, y, z));
	}

	D3DXVECTOR3 Transform::GetLossyScale(void) const noexcept
	{
		if (_pParent)
		{
			D3DXVECTOR3 lossy = _localScale;

			_pParent->CalculateLossyScale(lossy);
			return lossy;
		}

		return _localScale;
	}

	void Transform::CalculateLossyScale(OUT D3DXVECTOR3& lossy) noexcept
	{
		lossy = { lossy.x * _localScale.x, lossy.y * _localScale.y, lossy.z * _localScale.z };

		if (_pParent)
		{
			_pParent->CalculateLossyScale(lossy);
		}
	}

	void Transform::SetLocalScale(const D3DXVECTOR3& localScale) noexcept
	{
		_bDirtyScale = (_localScale != localScale);
		_localScale = localScale;
	}

	void Transform::SetLocalScale(float x, float y, float z) noexcept
	{
		SetLocalScale(D3DXVECTOR3(x, y, z));
	}

	bool Transform::RemoveChild(const Transform* child) noexcept
	{
		_vecChild.erase(std::remove(_vecChild.begin(), _vecChild.end(), child), _vecChild.end());
		return true;
	}

	void Transform::SetChild(IN const Transform* child) noexcept
	{
		_vecChild.push_back(const_cast<Transform*>(child));
	}

	void Transform::FindParentRecur(const Transform* transform, OUT std::vector<const Transform*>& vecParents) const noexcept
	{
		if (transform->_pParent != nullptr)
		{
			vecParents.push_back(transform->_pParent);
			transform->_pParent->FindParentRecur(transform->_pParent, vecParents);
		}
		return;
	}

	void Transform::OnParentPosChanged(void) noexcept
	{
		for (int i = 0; i < _vecChild.size(); i++)
		{
			_vecChild[i]->_worldPosition = _vecChild[i]->_localPosition + _worldPosition;
			_vecChild[i]->OnParentPosChanged();
			_vecChild[i]->_bDirtyPosition = true;
		}
	}

	void Transform::ForcedReCalMat(void) noexcept
	{
		D3DXMatrixIdentity(&_matPosition);
		D3DXMatrixTranslation(&_matPosition, _localPosition.x, _localPosition.y, _localPosition.z);

		D3DXMatrixIdentity(&_matRotation);
		//D3DXMatrixRotationZ(&m_matRotation, D3DXToRadian(m_localEulerAngle.z));
		D3DXMatrixRotationYawPitchRoll(&_matRotation, _localEulerAngle.y, _localEulerAngle.x, _localEulerAngle.z);

		D3DXMatrixIdentity(&_matScale);
		D3DXMatrixScaling(&_matScale, _localScale.x, _localScale.y, _localScale.z);

		_matWorld = _matScale * _matRotation * _matPosition;

		if (nullptr != _pParent)
		{
			_matWorld *= _pParent->_matWorld;
		}

		for (int i = 0; i < _vecChild.size(); i++)
		{
			_vecChild[i]->ForcedReCalMat();

		}
	}
}