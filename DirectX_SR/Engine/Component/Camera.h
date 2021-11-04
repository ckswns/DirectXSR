#pragma once

#include "Component.h"
#include "../Base/TypeDefine.h"

namespace ce
{ 
	class Transform;
	class GameObject;

	enum class ECAMERA_TYPE
	{
		PERSPECTIVE,
		ORTHO
	};

	class Camera : public Component
	{
	public:		explicit			Camera() = delete;
	public:		explicit			Camera(GameObject* owner, LPDIRECT3DDEVICE9 pDevice, ECAMERA_TYPE type = ECAMERA_TYPE::PERSPECTIVE) noexcept;
	public:		virtual				~Camera() noexcept { __noop; }

	public:		void				FixedUpdate(float fElapsedTime) noexcept override;
	public:		void				Update(float fElapsedTime) noexcept override;
	public:		void				LateUpdate(float fElapsedTime) noexcept override;
	public:		void				Release(void) noexcept override;
	public:		void				Render(void) noexcept override { __noop; }

	public:		Transform*			GetTransform(void) noexcept;

	private:	ECAMERA_TYPE		_type;

	private:	D3DXMATRIX			_matView;
	private:	D3DXMATRIX			_matProj;

	private:	LPDIRECT3DDEVICE9	_pDevice;

	public:		static Camera*		GetMainCamera(void) noexcept { return mainCamera; }
	private:	static Camera*		mainCamera;
	};
}
