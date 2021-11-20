#include "pch.h"
#include "BossCamera.h"
#include "Camera.h";
#include "Transform.h"
#include "CETween.h"
#include "Diablo.h"

BossCamera::BossCamera(Diablo* target) noexcept :
	_boss(target)
{
}

void BossCamera::Start(void) noexcept
{
	_target = _boss->GetTransform();
	_camera = Camera::GetMainCamera();
	Camera::SetMainCamera(nullptr);

	_camera->GetGameObject()->SetActive(false);
	gameObject->AddComponent(new Camera(D3D9DEVICE->GetDevice()));
	transform->SetParent(_target);
}

void BossCamera::Update(float fElapsedTime) noexcept
{
	if (_actionIndex == 0)
	{
		_time += fElapsedTime;

		float z = CETween::Lerp(0, 4, _time * 0.5f, CETween::EaseType::easeOutQuart);

		transform->SetLocalEulerAngle(_target->GetBillboardEulerAngleY());
		transform->SetLocalPosition(0, 0, -(6.5f - z));

		if (_time >= 2)
		{
			_time = 0;
			_actionIndex = 1;
			_boss->Intro();
			_shakeScale = 50;
		}
	}
	else if (_actionIndex == 1)
	{
		_time += fElapsedTime;

		if (_time >= 1.4f)
		{
			_time = 0;
			_actionIndex = 2;
		}
	}
	else if (_actionIndex == 2)
	{
		_time += fElapsedTime;
		D3DXVECTOR3 pos = transform->GetLocalPosition();
		_shakeScale = 50.f - CETween::Lerp(0, 50, _time * 0.5f, CETween::EaseType::easeLiner);

		if (_shakeScale <= 1)
			_shakeScale = 1.0f;

		float r = Random::GetValue(0, (int)_shakeScale) * 0.01f;
		float r2 = Random::GetValue(0, (int)_shakeScale) * -0.01f;
		float r3 = Random::GetValue(0, (int)_shakeScale) * -0.01f;
		float r4 = Random::GetValue(0, (int)_shakeScale) * 0.01f;

		pos.x = (r + r2);
		pos.y = (r3 + r4);

		transform->SetLocalPosition(pos.x, pos.y, pos.z);

		if (_time > 4)
		{
			_time = 0;
			_actionIndex = 0;
		}
	}
}
