#pragma once
#include "Scene.h"

class CreditScene : public Scene
{
public:		explicit		CreditScene(void) noexcept;
public:		virtual			~CreditScene(void) noexcept { __noop; }

public:		bool			Init(void) noexcept override;
public:		void			FixedUpdate(float fElapsedTime) noexcept override;
public:		void			Update(float fElapsedTime) noexcept override;
public:		void			LateUpdate(float fElapsedTime) noexcept override;
public:		void			Render(float fElapsedTime) noexcept override;
public:		void			Release(void) noexcept override;

private:	using			CREDIT_SCRIPT = std::vector<std::string>;

private:	CREDIT_SCRIPT	_scripts;
private:	float			_deltaTime = 0.0f;
private:	int				_index = 0;
};

