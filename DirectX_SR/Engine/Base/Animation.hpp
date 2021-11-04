#include "pch.h"
#include "Animation.h"
#include "CEMath.h"
#include "Transform.h"
#include "Renderer.h"

namespace ce
{
	template<typename T>
	inline Animation<T>::Animation(float totalTime, bool loop) noexcept :
		_bLoop(loop),
		_fTotalAniTime(totalTime),
		_fCurrentAniTime(0),
		_bEnd(false),
		_bPlay(false)
	{
	}

	template<typename T>
	inline Animation<T>::Animation(float totalTime, bool loop, const std::vector<float>& vKeyFrames) noexcept :
		_bLoop(loop),
		_fTotalAniTime(totalTime),
		_fCurrentAniTime(0),
		_bEnd(false),
		_bPlay(false)
	{

	}

	template<typename T>
	inline void Animation<T>::Update(float fElapsedTime) noexcept
	{
		if (_bPlay)
		{
			_fCurrentAniTime += fElapsedTime;

			if (_fCurrentAniTime >= _fTotalAniTime)
			{
				if (_bLoop)
				{
					_fCurrentAniTime = 0;
					if (CE_MATH::equl_f(_vKeyFrame[0].first, 0))
					{
						const VEC_DATA& datas = _vKeyFrame[0].second.first;

						for (int i = 0; i < datas.size(); i++)
						{
							switch (datas[i]._eType)
							{
							case AnimationType::SPRITE_ANIMATION:
								break;
							case AnimationType::POSITION_ANIMATION_LOCAL:
								break;
							case AnimationType::ROTATION_ANIMATION_LOCAL:
								break;
							case AnimationType::SCALE_ANIMATION_LOCAL:
								break;
							case AnimationType::POSITION_ANIMATION_GLOBAL:
								break;
							case AnimationType::ROTATION_ANIMATION_GLOBAL:
								break;
							case AnimationType::SCALE_ANIMATION_GLOBAL:
								break;
							default:
								break;
							}
						}

						const VEC_EVENTS& events = _vKeyFrame[0].second.second;

						for (int i = 0; i < events.size(); i++)
						{
							events[i].second(events[i].first);
						}
					}
				}
				else
				{
					if (CE_MATH::equl_f(_vKeyFrame[_vKeyFrame.size() - 1].first, _fTotalAniTime))
					{
						const VEC_EVENTS& events = _vKeyFrame[_vKeyFrame.size() - 1].second.second;

						for (int i = 0; i < events.size(); i++)
						{
							events[i].second(events[i].first);
						}
					}

					_bPlay = false;
					_bEnd = true;
					_fCurrentAniTime = _fTotalAniTime;
					return;
				}
			}

		//	if (_fCurrentAniTime > m_vecFrameTime[m_iFrame])
		//	{
		//		_fCurrentAniTime -= m_vecFrameTime[m_iFrame];

		//		int delaydFrameCount = 0;

		//		while (_fCurrentAniTime > m_vecFrameTime[m_iFrame])
		//		{
		//			_fCurrentAniTime -= m_vecFrameTime[m_iFrame];
		//			delaydFrameCount++;
		//		}

		//		m_iFrame += delaydFrameCount;

		//		if (m_iFrame < (INT)m_vecAnim.size() - 1)
		//		{
		//			m_iFrame++;
		//		}
		//		else if (m_bLoop)
		//		{
		//			m_iFrame = 0;
		//		}
		//		else
		//		{
		//			m_bPlay = FALSE;
		//			m_bEnd = TRUE;
		//			m_iFrame = (INT)m_vecAnim.size() - 1;
		//		}

		//		if (m_fpCallBack)
		//		{
		//			if (m_iFrame == m_iEventFrame)
		//				m_fpCallBack(*m_pCallbackTarget);
		//		}
		//	}
		}

		//m_pCurrentSprite = m_vecAnim[m_iFrame];
	}

	template<typename T>
	inline void Animation<T>::Play(void) noexcept
	{
		_bPlay = true;
		_bEnd = false;
		_fCurrentAniTime = 0;
	}

	template<typename T>
	inline void Animation<T>::Pause(void) noexcept
	{
		_bPlay = false;
	}

	template<typename T>
	inline void Animation<T>::Stop(void) noexcept
	{
		_bPlay = false;
		_bEnd = false;
		_fCurrentAniTime = 0;
	}

	template<typename T>
	inline void Animation<T>::Resume(void) noexcept
	{
		_bPlay = true;
	}

	template<typename T>
	inline bool Animation<T>::AddKeyFrame(float keyTime) noexcept
	{
		for (int i = 0; i < _vKeyFrame.size(); i++)
		{
			if (CE_MATH::equl_f(keyTime, _vKeyFrame[i].first))
				return false;
		}

		_vKeyFrame.push_back(std::make_pair(keyTime, std::make_pair(VEC_DATA(), VEC_EVENTS())));
		return true;
	}

	template<typename T>
	inline bool Animation<T>::AddEvent(int keyIndex, T* listener, std::function<void(T&)> fp) noexcept
	{
		if(_vKeyFrame.size() <= keyIndex)
			return false;

		_vKeyFrame[keyIndex].second.second.push_back(std::make_pair(listener, fp));
	}
}