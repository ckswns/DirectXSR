#pragma once

#include "Behaviour.h"

namespace ce
{
	class ce::Transform;

	class EditorCamera : public Behaviour
	{
	public:		explicit	EditorCamera(HWND hWnd) noexcept;
	public:		virtual		~EditorCamera(void) noexcept { __noop; }

	public:		void		Start(void) noexcept override;
	public:		void		Update(float fElapsedTime) noexcept override;

	private:	bool		_bMBRightDown = false;
	private:	bool		_bWireFrame = false;
	private:	POINT		_ptPrevMousePos;
	private:	HWND		_hWnd;
	};
}
