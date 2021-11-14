#pragma once

namespace ce
{
	class Cube;
	class Texture;
	class Transform;

	class SkyBox
	{
	public:		explicit			SkyBox(void) noexcept = delete;
	public:		explicit			SkyBox(LPDIRECT3DDEVICE9 device) noexcept;
	public:		virtual				~SkyBox(void) noexcept { __noop; }

	public:		void				SetTransform(Transform* transform) noexcept { _transform = transform; }
	public:		void				SetTexture(Texture* texture) noexcept;
	public:		void				Render(void) noexcept;
	public:		void				Release(void) noexcept;

	private:	LPDIRECT3DDEVICE9	_pDevice;
	private:	Transform*			_transform;
	private:	Texture*			_texture;
	private:	Cube*				_cube;
	};
}
