#pragma once
#include "Renderer.h"

namespace ce
{
	class Mesh;
	class Transform;

	class MeshRenderer : public Renderer
	{
	public:		explicit		MeshRenderer(void) = delete;
	public:		explicit		MeshRenderer(LPDIRECT3DDEVICE9 pDevice, Mesh* pMesh = nullptr) noexcept;
	public:		virtual			~MeshRenderer(void) noexcept { __noop; }

	public:		void			SetMesh(Mesh* pMesh) noexcept;

	public:		void			Init(void) noexcept override;
	public:		void			Render(void) noexcept override;
	public:		void			Release(void) noexcept override;

	private:	Transform*		_pTransform = nullptr;
	private:	Mesh*			_pMesh = nullptr;
	};
}
