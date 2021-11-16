#pragma once
#include "Behaviour.h"

class BillboardSprite : public Behaviour
{
public:		explicit	BillboardSprite(Texture* tex) noexcept;
public:		virtual		~BillboardSprite(void) noexcept { __noop; }

public:		void		Start(void) noexcept override;
public:		void		Update(float) noexcept override;

private:	Texture*	_tex;
};

