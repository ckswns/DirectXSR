#pragma once
#include "SingletonBase.h"
#include "TypeDefine.h"

namespace ce
{
	class Input final : public SingletonBase<Input>
	{
	private:	explicit		Input(void) noexcept;
	private:	virtual			~Input(void) noexcept { __noop; }

	public:		void			Update(void) noexcept;
	public:		bool			GetKeyUp(uint8 key) noexcept;
	public:		bool			GetKeyDown(uint8 key) noexcept;
	public:		bool			GetKeyStay(uint8 key) noexcept;

	private:	bool			_bState[255];

	private:	friend			SingletonBase<Input>;
	};
}
