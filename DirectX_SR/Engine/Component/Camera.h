#pragma once

#include "Component.h"
#include "../Base/TypeDefine.h"

namespace ce
{ 
	class Transform;
	class GameObject;
	class SkyBox;

	class Camera : public Component
	{
	public:		enum class Type
				{
					PERSPECTIVE,
					ORTHO
				};

	public:		enum class ClearOption
				{
					SOLID_COLOR,
					SKYBOX
				};

	public:		explicit			Camera() = delete;
	public:		explicit			Camera(LPDIRECT3DDEVICE9 pDevice, Type type = Type::PERSPECTIVE) noexcept;
	public:		virtual				~Camera() noexcept { __noop; }

	public:		void				Init(void) noexcept override;
	public:		void				FixedUpdate(float fElapsedTime) noexcept override { __noop; }
	public:		void				Update(float fElapsedTime) noexcept override { __noop; }
	public:		void				LateUpdate(float fElapsedTime) noexcept override;
	public:		void				Release(void) noexcept override;
	public:		void				Render(void) noexcept override { __noop; }

	public:		Transform*			GetTransform(void) noexcept;

	private:	Type				_type;

	private:	D3DXMATRIX			_matView;
	private:	D3DXMATRIX			_matProj;

	private:	LPDIRECT3DDEVICE9	_pDevice;

	private:	SkyBox*				_skybox;

	public:		static Camera*		GetMainCamera(void) noexcept { return mainCamera; }
	private:	static Camera*		mainCamera;
	};
}
