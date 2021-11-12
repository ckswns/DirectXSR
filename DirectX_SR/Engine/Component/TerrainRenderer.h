#pragma once
#include "Renderer.h"
#include "Material.h"

namespace ce
{
	class Terrain;
	class Transform;

	class TerrainRenderer : public Renderer
	{
	public:		explicit	TerrainRenderer(void) = delete;
	public:		explicit	TerrainRenderer(LPDIRECT3DDEVICE9 pDevice, Terrain* terrain = nullptr) noexcept;
	public:		virtual		~TerrainRenderer(void) noexcept { __noop; }

	public:		void		SetTerrain(Terrain* pTerrain) noexcept;

	public:		void		Init(void) noexcept override;
	public:		void		Render(void) noexcept override;
	public:		void		Release(void) noexcept override;

	public:		Material*	GetAlphaMaterial(void) noexcept { return &_alphaMaterial; }

	private:	Material	_alphaMaterial;
	private:	Transform*	_pTransform = nullptr;
	private:	Terrain*	_pTerrain = nullptr;
	};
}
