#pragma once
#include "Scene.h"

class TownScene_01 : public Scene
{
public:		explicit	TownScene_01(void) noexcept;
public:		virtual		~TownScene_01(void) noexcept { __noop; }

public:		bool		Init(void) noexcept override;
public:		void		FixedUpdate(float fElapsedTime) noexcept override;
public:		void		Update(float fElapsedTime) noexcept override;
public:		void		LateUpdate(float fElapsedTime) noexcept override;
public:		void		Render(float fElapsedTime) noexcept override;
public:		void		Release(void) noexcept override;
};

