#pragma once
#include "SpriteRenderer.h"

class EffectRenderer : public SpriteRenderer
{
public:		explicit	EffectRenderer(void) noexcept;
public:		virtual		~EffectRenderer(void) noexcept { __noop; }

public:		void		Render(void) noexcept override;
};

