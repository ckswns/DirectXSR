#pragma once
#include "Behaviour.h"

class CreditScript : public Behaviour
{
public:		explicit		CreditScript(std::string str) noexcept;
public:		virtual			~CreditScript(void) noexcept { __noop; }

public:		void			Start(void) noexcept override;
public:		void			Update(float) noexcept override;
public:		std::string		_str;
};

