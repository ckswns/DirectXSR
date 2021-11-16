#pragma once

namespace ce
{
	class GameObject;
}
class Command abstract
{
public:		virtual				~Command() noexcept { __noop; }
public:		virtual void			Execute(GameObject* actor,D3DXVECTOR3 curPos) noexcept PURE;
};

