#pragma once
#include "Scene.h"

class Mephisto_Chamber : public Scene
{
public:		explicit	Mephisto_Chamber(void) noexcept;
public:		virtual		~Mephisto_Chamber(void) noexcept;

public:		bool		Init(void) noexcept override;
public:		void		FixedUpdate(float fElapsedTime) noexcept override;
public:		void		Update(float fElapsedTime) noexcept override;
public:		void		LateUpdate(float fElapsedTime) noexcept override;
public:		void		Render(float fElapsedTime) noexcept override;
public:		void		Release(void) noexcept override;
};

