#pragma once
#include "TypeDefine.h"
#include "Texture.h"

#ifndef _FUNCTIONAL_
#include <functional>
#endif

#ifndef PURE
#define PURE =0
#endif

#define ANIMATION_TYPE_NUM 4

namespace ce
{
	enum class AnimationType
	{
		SPRITE_ANIMATION,
		POSITION_ANIMATION_LOCAL,
		ROTATION_ANIMATION_LOCAL,
		SCALE_ANIMATION_LOCAL,
		POSITION_ANIMATION_GLOBAL,
		ROTATION_ANIMATION_GLOBAL,
		SCALE_ANIMATION_GLOBAL,
	};

	template <typename T>
	class Animation
	{
	protected:	struct AnimationData
				{
					explicit AnimationData(D3DXVECTOR3 v, AnimationType eType) noexcept : _D3DXVECTOR3(v), _isInit(true), _eType(eType) { __noop; }
					explicit AnimationData(Texture* t) noexcept : _texture(t), _isInit(true), _eType(AnimationType::SPRITE_ANIMATION) { __noop; }
					
					union
					{
						D3DXVECTOR3 _D3DXVECTOR3;
						Texture* _texture;
					};

					AnimationType _eType;
					bool _isInit;
				};

	protected:	using			VEC_EVENTS = std::vector<std::pair<T*, std::function<void(T&)>>>;
	protected:	using			VEC_DATA = std::vector<AnimationData>;
	protected:	using			VEC_KEYFRAME = std::vector<std::pair<float, std::pair<VEC_DATA, VEC_EVENTS>>>;

	public:		explicit		Animation(void) noexcept = delete;
	public:		explicit		Animation(float totalTime, bool loop = false) noexcept;
	public:		explicit		Animation(float totalTime, bool loop, const std::vector<float>& vKeyFrames) noexcept;
	public:		virtual			~Animation(void) noexcept { __noop; }

	public:		virtual void	Update(float fElapsedTime) noexcept;

	public:		virtual void	Play(void) noexcept;
	public:		virtual void	Pause(void) noexcept;
	public:		virtual void	Stop(void) noexcept;
	public:		virtual void	Resume(void) noexcept;

	public:		bool			IsPlaying(void) const noexcept { return _bPlay; }
	public:		bool			IsEnd(void) const noexcept { return _bEnd; }
	public:		bool			IsLoop(void) const noexcept { return _bLoop; }

	public:		float			GetProgress(void) const noexcept { return _fCurrentAniTime / _fTotalAniTime; }
	public:		float			GetRealTimeProgress(void) const noexcept { return _fCurrentAniTime; }
	public:		float			GetTimeLength(void) const noexcept { return _fTotalAniTime; }

	public:		bool			AddKeyFrame(float keyTime) noexcept;
	public:		bool			AddEvent(int keyIndex, T* listener, std::function<void(T&)> fp) noexcept;

	protected:	bool			_bLoop;
	protected:	bool			_bEnd;
	protected:	bool			_bPlay;

	protected:	float			_fCurrentAniTime;
	protected:	float			_fTotalAniTime;

	protected:	VEC_KEYFRAME	_vKeyFrame;
	};
}