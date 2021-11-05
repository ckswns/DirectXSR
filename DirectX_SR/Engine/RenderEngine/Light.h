#pragma once
#include "Component.h"

#ifndef IN
#define IN
#endif

namespace ce
{
	class GameObject;

	class Light : public Component
	{
	public:		enum class				Type
				{
										DIRECTIONAL,
										POINT,
										SPOT
				};

	public:		explicit				Light(void) = delete;
	public:		explicit				Light(Light::Type type, LPDIRECT3DDEVICE9 pDevice, IN const D3DCOLORVALUE& color, float range, float attenuation = 0, float theta = 0, float phi = 0, float fallOff = 0);
	public:		virtual					~Light(void) noexcept { __noop; }

	public:		void					Init(void) noexcept override;
	public:		void					Update(float) noexcept override;
	public:		void					Render(void) noexcept override;
	public:		void					Release(void) noexcept override;

	private:	const D3DCOLORVALUE&	GetColor(void) const noexcept { _color; }
	private:	void					SetColor(IN const D3DCOLORVALUE& color) noexcept { _color = color; }

	private:	Light::Type				_type;

	private:	D3DCOLORVALUE			_color;
	private:	D3DLIGHT9				_light;
	private:	LPDIRECT3DDEVICE9		_pDevice;

	private:	uint16					_lightID;
	private:	D3DXVECTOR3				_dir;

	private:	static uint16			_lightIDBuff;
	};
}
