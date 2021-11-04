#pragma once
#include "GameObject.h"

class Cube_Object : public GameObject
{
public:	bool	Init(void) noexcept override;
public:	void	Update(float fElapsedTime) noexcept override;
public:	void	Render(void) noexcept override;
public:	void	Release(void) noexcept override;

};

