#pragma once
#include "Component.h"
#include "Material.h"

namespace ce
{
	class Renderer : public Component
	{
	public:		explicit			Renderer(void) noexcept = delete;
	public:		explicit			Renderer(LPDIRECT3DDEVICE9 pDevice) : Component(COMPONENT_ID::RENDERER, true), _pDevice(pDevice) { __noop; }
	public:		virtual				~Renderer(void) noexcept { __noop; }

	public:		const Material&		GetMaterial(void) const noexcept { return _material; }
	public:		Material*			GetMaterialPTR(void) noexcept { return &_material; }

	protected:	LPDIRECT3DDEVICE9	_pDevice = nullptr;
	protected:	Material			_material;
	};
}
