#include "pch.h"
#include "Animation.h"
#include "CEMath.h"
#include "Transform.h"
#include "GameObject.h"
#include "Assertion.h"
#include "Material.h"

namespace ce
{
	Animation::Animation(const std::vector<float>& vFrameTime, const std::vector<Texture*>& vTex, bool loop) noexcept :
		_bLoop(loop),
		_fTotalAniTime(0),
		_fCurrentAniTime(0),
		_bEnd(false),
		_bPlay(false),
		_material(nullptr)
	{
		if (vFrameTime.size() != vTex.size())
			CE_ASSERT("ckswns", "프레임수와 텍스쳐의 숫자가 일치하지 않습니다");

		_vFrameTime.assign(vFrameTime.begin(), vFrameTime.end());
		_vTexture.assign(vTex.begin(), vTex.end());

		for (int i = 0; i < vFrameTime.size(); i++)
		{
			_fTotalAniTime += vFrameTime[i];
			_mapEvent.insert(std::make_pair(i, VEC_EVENT()));
		}

		_fp = &GameObject::OnAnimationEvent;
	}

	void Animation::Update(float fElapsedTime) noexcept
	{
		if (_bPlay)
		{
			_fCurrentAniTime += fElapsedTime;

			if (_fCurrentAniTime > _vFrameTime[_iFrame])
			{
				_fCurrentAniTime = 0;
				_iFrame++;

				if (_iFrame >= _vFrameTime.size())
				{
					if (_bLoop)
					{
						_iFrame = 0;
						if (_material)
							_material->SetMainTexture(_vTexture[_iFrame]);
					}
					else
					{
						_bPlay = false;
						_bEnd = true;

						return;
					}
				}
				else
				{
					if (_material)
						_material->SetMainTexture(_vTexture[_iFrame]);
				}

				if (_iFrame < _vFrameTime.size())
				{
					for (int i = 0; i < _mapEvent[_iFrame].size(); i++)
					{
						_fp(*_mapEvent[_iFrame][i]._pListener, _iFrame, _mapEvent[_iFrame][i]._eventName);
					}
				}
			}
		}
	}

	void Animation::Play(void) noexcept
	{
		_bPlay = true;
		_bEnd = false;
		_fCurrentAniTime = 0;
		_iFrame = 0;

		if (_material)
			_material->SetMainTexture(_vTexture[_iFrame]);
	}

	void Animation::Pause(void) noexcept
	{
		_bPlay = false;
	}

	void Animation::Stop(void) noexcept
	{
		_bPlay = false;
		_bEnd = false;
		_fCurrentAniTime = 0;
	}

	void Animation::Resume(void) noexcept
	{
		_bPlay = true;
	}
	bool Animation::AddEvent(uint32 keyIndex, std::string eventStr, GameObject* listener) noexcept
	{
		auto iter = _mapEvent.find(keyIndex);

		if (iter == _mapEvent.end())
			return false;

		iter->second.emplace_back(EventData(keyIndex, eventStr, listener));

		return true;
	}
	bool Animation::AddEvent(EventData data) noexcept
	{
		auto iter = _mapEvent.find(data._keyFrame);

		if (iter == _mapEvent.end())
			return false;

		iter->second.emplace_back(data);

		return true;
	}
	void Animation::SetFrame(int frame) noexcept
	{
		if (frame >= _vFrameTime.size())
			_iFrame = _vFrameTime.size() - 1;
		else
			_iFrame = frame;
	}
}