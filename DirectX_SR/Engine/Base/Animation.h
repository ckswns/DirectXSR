#pragma once
#include "TypeDefine.h"
#include "Texture.h"

#ifndef _FUNCTIONAL_
#include <functional>
#endif

#ifndef _MAP_
#include <map>
#endif // !#ifndef _MAP_

#ifndef PURE
#define PURE =0
#endif

namespace ce
{
	class GameObject;
	class Material;

	class Animation final
	{
	public:		class EventData
				{
				public:			EventData(uint32 keyFrame, std::string eventStr, GameObject* listener) noexcept :
									_keyFrame(keyFrame),
									_eventName(eventStr),
									_pListener(listener)
								{
									__noop; 
								}

				private:		uint32		_keyFrame;
				private:		std::string _eventName;
				private:		GameObject* _pListener;

				private:		friend Animation;
				};

	private:	using			VEC_EVENT = std::vector<EventData>;
	private:	using			VEC_FRAME = std::vector<float>;
	private:	using			VEC_TEX = std::vector<Texture*>;
	private:	using			MAP_EVENT = std::map<uint32, std::vector<EventData>>;

	public:		explicit		Animation(void) noexcept = delete;
	public:		explicit		Animation(const std::vector<float>& vFrameTime, const std::vector<Texture*>& vTex, bool loop = false) noexcept;
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

	public:		int				GetCurrentFrame(void) const noexcept { return _iFrame; }

	public:		bool			AddEvent(uint32 keyIndex, std::string eventStr, GameObject* listener) noexcept;
	public:		bool			AddEvent(EventData data) noexcept;

	public:		void			SetMaterial(Material* mat) noexcept { _material = mat; }

	private:	int				_iFrame;

	private:	bool			_bLoop;
	private:	bool			_bEnd;
	private:	bool			_bPlay;

	private:	float			_fCurrentAniTime;
	private:	float			_fTotalAniTime;

	private:	VEC_FRAME		_vFrameTime;
	private:	VEC_TEX			_vTexture;
	private:	MAP_EVENT		_mapEvent;

	private:	Material*		_material;

	private:	std::function<void(GameObject&, int, std::string)> _fp;
	};
}