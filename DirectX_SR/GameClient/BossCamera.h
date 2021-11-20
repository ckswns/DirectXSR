#pragma once
#include "Behaviour.h"

namespace ce
{
	class Camera;
	class Transform;
}

class Diablo;

class BossCamera : public Behaviour
{
public:		explicit		BossCamera(Diablo* target) noexcept;
public:		virtual			~BossCamera(void) noexcept { __noop; }

public:		void			Start(void) noexcept override;
public:		void			Update(float fElapsedTime) noexcept override;

private:	Diablo*			_boss;
private:	Transform*		_target;
private:	Camera*			_camera;

private:	int				_actionIndex = 0;
private:	bool			_shake = false;
private:	float			_time = 0;
private:	float			_shakeScale = 1.f;
};

