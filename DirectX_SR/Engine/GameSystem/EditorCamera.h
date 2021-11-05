#pragma once

#include "Behaviour.h"

namespace ce
{
	class ce::Transform;

	class EditorCamera : public Behaviour
	{
	public:		explicit	EditorCamera(HWND hWnd, float velocity = 0.5f) noexcept;
	public:		virtual		~EditorCamera(void) noexcept { __noop; }

	public:		void		Start(void) noexcept override;
	public:		void		Update(float fElapsedTime) noexcept override;

	private:	float		_velocity;
	private:	bool		_bMBRightDown = false;
	private:	bool		_bWireFrame = false;
	private:	POINT		_ptPrevMousePos;
	private:	HWND		_hWnd;
	};
}
