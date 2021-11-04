#pragma once
#include "GameObject.h"

class DirectionLight : public GameObject
{
public:		explicit	DirectionLight(void) noexcept { __noop; }
public:		virtual		~DirectionLight(void) noexcept { __noop; }

public:		bool		Init(void) noexcept override;
public:		void		Update(float fElapsedTime) noexcept override;
public:		void		Render(void) noexcept override;
public:		void		Release(void) noexcept override;
};

