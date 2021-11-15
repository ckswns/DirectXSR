#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
}
class TargetCamera : public Behaviour
{
public:		explicit		TargetCamera(Transform* target) noexcept;
public:		virtual			~TargetCamera(void) noexcept { __noop; }

public:		void			Start(void) noexcept override;
public:		void			Update(float fElapsedTime) noexcept override;

public:		void			ChangeView();
public:		bool			IsFPV() { return _bFPV; }

private:	Transform*		_pTrans;
private:	Transform*		_pTargetTrans;

private:	float			_fAngle;
private:	float			_fTPVDist;
private:	float			_fTPVHeight;

private:	bool			_bFPV;

private:	float			_fDelta;
private:	float			_fFPVDist;
private:	float			_fFPVHeight;
};

