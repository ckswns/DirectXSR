#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
}
class TargetCamera : public Behaviour
{
public:		explicit			TargetCamera(Transform* target) noexcept;
public:		virtual			~TargetCamera(void) noexcept { __noop; }

public:		void				Start(void) noexcept override;
public:		void				Update(float fElapsedTime) noexcept override;

private:		Transform*		_pTrans;
private:		Transform*		_pTargetTrans;

private:		float				_fDist;
private:		float				_fHeight;
};

