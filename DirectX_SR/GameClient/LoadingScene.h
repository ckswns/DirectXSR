#pragma once
#include "Scene.h"

class LoadingScene : public Scene
{
public:		explicit	LoadingScene(void) noexcept;
public:		virtual		~LoadingScene(void) noexcept { __noop; }

public:		bool		Init(void) noexcept override;
public:		void		FixedUpdate(float fElapsedTime) noexcept override;
public:		void		Update(float fElapsedTime) noexcept override;
public:		void		LateUpdate(float fElapsedTime) noexcept override;
public:		void		Render(float fElapsedTime) noexcept override;
public:		void		Release(void) noexcept override;
};

