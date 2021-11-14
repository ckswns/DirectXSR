#pragma once
#include "Collider.h"

namespace ce
{
	class BoxCollider : public Collider
	{
	public:		explicit		BoxCollider(void) noexcept = delete;
	public:		explicit		BoxCollider(const D3DXVECTOR3& size, const D3DXVECTOR3& center = D3DXVECTOR3(0, 0, 0), std::string tag = "") noexcept;
	public:		virtual			~BoxCollider(void) noexcept { __noop; }

	public:		void			Open(void) noexcept override;
	public:		void			Close(void) noexcept override;

	public:		bool			CheckCollision(Collider* rhs) const noexcept override;
	public:		bool			CheckHitRaycast(const Ray& ray, RaycastHit& hit) const noexcept override;

	public:		void			Render(void) noexcept override;

	public:		D3DXVECTOR3		GetMin(void) const noexcept;
	public:		D3DXVECTOR3		GetMax(void) const noexcept;

	private:	D3DXVECTOR3		_center;
	private:	D3DXVECTOR3		_size;
#ifdef _DEBUG
	private:	LPD3DXMESH		_dbgBox;
#endif // DEBUG

	};
}
