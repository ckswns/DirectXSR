#pragma once
#include "Renderer.h"

namespace ce
{
	class Mesh;
	class Transform;

	class MeshRenderer : public Renderer
	{
	public:		explicit		MeshRenderer(void) = delete;
	public:		explicit		MeshRenderer(GameObject* owner, LPDIRECT3DDEVICE9 pDevice, Mesh* pMesh = nullptr) noexcept;
	public:		virtual			~MeshRenderer(void) noexcept { __noop; }

	public:		void			SetMesh(Mesh* pMesh) noexcept;

	public:		void			FixedUpdate(float) noexcept override { __noop; }
	public:		void			Update(float) noexcept override { __noop; }
	public:		void			LateUpdate(float) noexcept override { __noop; }
	public:		void			Render(void) noexcept override;
	public:		void			Release(void) noexcept override;

	private:	Transform*		_pTransform = nullptr;
	private:	Mesh*			_pMesh = nullptr;
	};
}
