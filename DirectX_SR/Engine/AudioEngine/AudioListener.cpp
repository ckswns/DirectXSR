#include "pch.h"
#include "AudioListener.h"
#include "GameObject.h"
#include "ConstValues.h"
#include "FMODManager.h"
#include "Transform.h"
#include "Assertion.h"

#ifdef __USE_FMOD__
AudioListener* AudioListener::_pListener = nullptr;

namespace ce
{
	AudioListener::AudioListener(void) noexcept :
		Component(COMPONENT_ID::AUDIOLISTENER),
		_pSystem(nullptr),
		_pTransform(nullptr)
	{

	}

	void AudioListener::Init(void) noexcept
	{
		_pSystem = FMODManager::Instance()->GetSystem();
		_pTransform = _owner->GetTransform();

		if (_pSystem == nullptr)
			CE_ASSERT("ckswns", "FMOD::System이 초기화 되지 않았습니다!");
		if (_pTransform == nullptr)
			CE_ASSERT("ckswns", "Owner의 Transform을 얻어오는데 실패하였습니다");

		if (_pListener != nullptr)
		{
			CE_ASSERT("ckswns", "AudioListener는 씬에 여러개 존재할 수 없습니다.");
		}
		else
			_pListener = this;
	}

	void AudioListener::LateUpdate(float) noexcept
	{
		D3DXVECTOR3 pos = _pTransform->GetWorldPosition();
		D3DXVECTOR3 foward = _pTransform->GetForward();
		D3DXVECTOR3 up = _pTransform->GetUp();

		D3DXVec3Normalize(&foward, &foward);
		D3DXVec3Normalize(&up, &up);

		FMOD_VECTOR fPos = { pos.x, pos.y, pos.z };
		FMOD_VECTOR fFoward = { foward.x, foward.y, foward.z };
		FMOD_VECTOR fUp = { up.x, up.y, up.z };

		_pSystem->set3DListenerAttributes(0, &fPos, NULL, &fFoward, &fUp);
	}

	void AudioListener::Release(void) noexcept
	{
		if (_pListener == this)
		{
			_pListener = nullptr;
		}
	}
}

#endif