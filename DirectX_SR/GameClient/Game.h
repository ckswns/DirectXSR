#pragma once
#include "Scene.h"

class NeviMesh;
class Game : public Scene
{
public:		explicit		Game(void) noexcept;
public:		virtual			~Game(void) noexcept { __noop; }

public:		bool			Init(void) noexcept override;
public:		void			FixedUpdate(float fElapsedTime) noexcept override;
public:		void			Update(float fElapsedTime) noexcept override;
public:		void			LateUpdate(float fElapsedTime) noexcept override;
public:		void			Render(float fElapsedTime) noexcept override;
public:		void			Release(void) noexcept override;

private:    NeviMesh* _pNeviMesh;
};

