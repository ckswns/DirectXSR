#pragma once
#include "Scene.h"
class ToolScene : public Scene
{
public:		explicit			ToolScene(void) noexcept { __noop; }
public:		virtual				~ToolScene(void) noexcept { __noop; }

public:		virtual bool		Init(void) noexcept;
public:		virtual void		Render(float fElapsedTime) noexcept;

};

