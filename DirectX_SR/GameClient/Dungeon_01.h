#pragma once
#include "scene.h"

class Dungeon_01 : public Scene
{
public:		explicit	Dungeon_01(void) noexcept;
public:		virtual		~Dungeon_01(void) noexcept;

public:		bool		Init(void) noexcept override;
public:		void		FixedUpdate(float fElapsedTime) noexcept override;
public:		void		Update(float fElapsedTime) noexcept override;
public:		void		LateUpdate(float fElapsedTime) noexcept override;
public:		void		Render(float fElapsedTime) noexcept override;
public:		void		Release(void) noexcept override;
};

