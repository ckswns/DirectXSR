#include "pch.h"
#include "AudioListener.h"
#include "GameObject.h"
#include "ConstValues.h"
#include "FMODManager.h"
#include "Transform.h"
#include "Assertion.h"

#ifdef __USE_FMOD__

namespace ce
{
	AudioListener::AudioListener(GameObject* owner) noexcept :
		Component(owner, COMPONENT_ID::AUDIOLISTENER),
		_pSystem(FMODManager::Instance()->GetSystem()),
		_pTransform(owner->GetTransform())
	{
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

	void AudioListener::FixedUpdate(float) noexcept
	{

	}

	void AudioListener::Update(float) noexcept
	{

	}

	void AudioListener::LateUpdate(float) noexcept
	{
		FMOD_VECTOR pos = _pTransform->GetWorldPosition();
		FMOD_VECTOR foward = _pTransform->GetForward();
		FMOD_VECTOR up = _pTransform->GetUp();

		_pSystem->set3DListenerAttributes(0, &pos, NULL, &foward, &up);
	}

	void AudioListener::Render(float) noexcept
	{

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