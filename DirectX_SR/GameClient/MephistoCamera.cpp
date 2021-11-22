#include "pch.h"
#include "MephistoCamera.h"
#include "Camera.h";
#include "Transform.h"
#include "CETween.h"
#include "Mephisto.h"
#include "TargetCamera.h"
#include "Light.h"
MephistoCamera::MephistoCamera(Mephisto* target) noexcept :
	_boss(target)
{
}

void MephistoCamera::Start(void) noexcept
{
	_target = _boss->GetTransform();
	_camera = Camera::GetMainCamera();
	Camera::SetMainCamera(nullptr);
	Camera::SetMainCamera(static_cast<Camera*>(gameObject->AddComponent(new Camera(D3D9DEVICE->GetDevice()))));
	_player = GameObject::FindObjectByTag(GameObjectTag::PLAYER)->GetTransform();

	_camera->GetGameObject()->SetActive(false);

	D3DCOLORVALUE c;
	c.a = 1;
	c.r = 1;
	c.g = 1;
	c.b = 1;
	gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 20, 0, 0, 0.02f));
	gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 100, 2.f));

	transform->SetParent(_target);
}

void MephistoCamera::Update(float fElapsedTime) noexcept
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

		if (_time > 2.5f)
		{
			_time = 0;
			_actionIndex = 3;
			_tempPos = transform->GetWorldPosition();
			_camera->GetGameObject()->SetActive(true);
		}
	}
	else if (_actionIndex == 3)
	{
		_time += fElapsedTime;
		D3DXVECTOR3 pos = _player->GetWorldPosition();

		float x = CETween::Lerp(_tempPos.x, pos.x, _time * 0.5f, CETween::EaseType::easeLiner);
		float y = CETween::Lerp(_tempPos.y, pos.y, _time * 0.5f, CETween::EaseType::easeLiner);
		float z = CETween::Lerp(_tempPos.z, pos.z, _time * 0.5f, CETween::EaseType::easeInCubic);

		transform->SetWorldPosition(x, y, z);

		if (_time > 2)
		{
			Camera::SetMainCamera(_camera);
			gameObject->Destroy();
			_boss->IntroDone();
		}
	}
}
