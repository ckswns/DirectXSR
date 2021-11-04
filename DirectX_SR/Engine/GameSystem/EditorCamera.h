#pragma once

#include "GameObject.h"

namespace ce
{
	class ce::Transform;

	class EditorCamera : public GameObject
	{
	public:		explicit	EditorCamera(HWND hWnd) noexcept;
	public:		virtual		~EditorCamera(void) noexcept { __noop; }

	public:		bool		Init(void) noexcept override;
	public:		void		Update(float fElapsedTime) noexcept override;
	public:		void		Render(void) noexcept override;
	public:		void		Release(void) noexcept override;

	private:	bool		_bMBRightDown = false;
	private:	bool		_bWireFrame = false;
	private:	POINT		_ptPrevMousePos;
	private:	HWND		_hWnd;

	private:	ce::Transform* _pTransform = nullptr;
	};
}
