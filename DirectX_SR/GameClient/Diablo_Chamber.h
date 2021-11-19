#pragma once
#include "Scene.h"

class Diablo_Chamber : public Scene
{
public:		explicit	Diablo_Chamber(void) noexcept { __noop; }
public:		virtual		~Diablo_Chamber(void) noexcept { __noop; }

public:		bool		Init(void) noexcept override;
public:		void		FixedUpdate(float fElapsedTime) noexcept override;
public:		void		Update(float fElapsedTime) noexcept override;
public:		void		LateUpdate(float fElapsedTime) noexcept override;
public:		void		Render(float fElapsedTime) noexcept override;
public:		void		Release(void) noexcept override;
};

