#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
}
class TargetCamera : public Behaviour
{
public:		explicit				TargetCamera(Transform* target) noexcept;
public:		virtual					~TargetCamera(void) noexcept { __noop; }

public:		virtual void			Start(void) noexcept override;
public:		virtual void			Update(float fElapsedTime) noexcept override;
public:		virtual void				FixedUpdate(float fElapsedTime) noexcept;

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

private:	bool			_bDoLerp = false;
private:	D3DXVECTOR3		_destPos;
private:	D3DXVECTOR3		_srcPos;

private:	float			_currentLerpTime = 0;
};

