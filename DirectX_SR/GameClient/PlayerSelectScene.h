#pragma once
#include "Scene.h"

class PlayerSelectScene : public Scene
{
public:		explicit	PlayerSelectScene(void) noexcept;
public:		virtual		~PlayerSelectScene(void) noexcept { __noop; }

public:		bool		Init(void) noexcept override;
public:		void		FixedUpdate(float fElapsedTime) noexcept override;
public:		void		Update(float fElapsedTime) noexcept override;
public:		void		LateUpdate(float fElapsedTime) noexcept override;
public:		void		Render(float fElapsedTime) noexcept override;
public:		void		Release(void) noexcept override;
};

