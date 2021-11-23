#pragma once
#include "Behaviour.h"

namespace ce
{
	class Camera;
	class Transform;
}

class Mephisto;

class MephistoCamera : public Behaviour
{
public:		explicit		MephistoCamera(Mephisto* target) noexcept;
public:		virtual			~MephistoCamera(void) noexcept { __noop; }

public:		void			Start(void) noexcept override;
public:		void			Update(float fElapsedTime) noexcept override;

private:	Mephisto*		_boss;
private:	Transform*		_target;
private:	Transform*		_player;
private:	Camera*			_camera;
private:	D3DXVECTOR3		_tempPos;

private:	int				_actionIndex = 0;
private:	bool			_shake = false;
private:	float			_time = 0;
private:	float			_shakeScale = 1.f;
};

