#include "pch.h"
#include "Light.h"
#include "ConstValues.h"
#include "Assertion.h"
#include "Transform.h"
#include "CEMath.h"

namespace ce
{
	uint16 Light::_lightIDBuff = 0;

	Light::Light(Light::Type type, LPDIRECT3DDEVICE9 pDevice, IN const D3DCOLORVALUE& color, float range, 
				float attenuation0, float attenuation1, float attenuation2, float theta, float phi, float fallOff) :
		Component(COMPONENT_ID::LIGHT),
		_type(type),
		_color(color),
		_pDevice(pDevice)
	{
		switch (type)
		{
		case Light::Type::DIRECTIONAL:
			_light.Type = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
			break;
		case Light::Type::POINT:
			_light.Type = D3DLIGHTTYPE::D3DLIGHT_POINT;
			_light.Attenuation0 = attenuation0;
			_light.Attenuation1 = attenuation1;
			_light.Attenuation2 = attenuation2;
			break;
		case Light::Type::SPOT:
			_light.Type = D3DLIGHTTYPE::D3DLIGHT_SPOT;
			_light.Attenuation0 = attenuation0;
			_light.Attenuation1 = attenuation1;
			_light.Attenuation2 = attenuation2;
			_light.Theta = theta;
			_light.Phi = phi;
			_light.Falloff = fallOff;
			break;
		}

		_light.Diffuse = color;
		_light.Specular = color;
		_light.Ambient = color;

		_light.Range = range;
	}

	void Light::Init(void) noexcept
	{
		_dir = _owner->GetTransform()->GetForward();

		D3DXVec3Normalize(&_dir, &_dir);

		_light.Direction = _dir;

		_light.Position = _owner->GetTransform()->GetWorldPosition();

		int i = 0;

		for (; i < 10; i++)
		{
			uint16 id = (1 << i);

			if (_lightIDBuff & id)
				continue;

			_lightIDBuff |= id;
			_lightID = id;

			_pDevice->SetLight(id, &_light);
			_pDevice->LightEnable(id, true);

			break;
		}

		if (i >= 10)
		{
			CE_ASSERT("ckswns", "설치된 조명이 너무 많습니다");
		}
	}

	void Light::Update(float) noexcept
	{
		D3DXVECTOR3 dir = _owner->GetTransform()->GetForward();
		D3DXVec3Normalize(&dir, &dir);

		if (_type == Type::DIRECTIONAL)
		{
			if (dir == _dir)
				return;

			_dir = dir;

			_light.Direction = _dir;

			_pDevice->SetLight(_lightID, &_light);
			_pDevice->LightEnable(_lightID, true);
		}

		else
		{
			_dir = dir;

			_light.Position = _owner->GetTransform()->GetWorldPosition();
			_light.Direction = _dir;

			_pDevice->SetLight(_lightID, &_light);
			_pDevice->LightEnable(_lightID, true);
		}
	}

	void Light::Render(void) noexcept
	{
	}

	void Light::Release(void) noexcept
	{
		_pDevice->LightEnable(_lightID, false);
		_lightIDBuff ^= _lightID;
	}
}