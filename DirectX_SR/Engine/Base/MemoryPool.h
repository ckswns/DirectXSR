#pragma once

#ifndef __MEMORY_POOL_H__
#define __MEMORY_POOL_H__

#include "Assertion.h"
#include <mutex>
#include "TypeDefine.h"

namespace ce
{
	template <class T, int ALLOC_BLOCK_SIZE = 50>
	class MemoryPool
	{
	protected:					MemoryPool(void) noexcept;
	protected:	virtual			~MemoryPool(void) noexcept;

	public:		static void*	operator new(std::size_t allocLength) noexcept;
	public:		static void		operator delete(void* deletePointer) noexcept;

	private:	static void		AllocBlock() noexcept;
	public:		static void		Release(void) noexcept;

	private:	static			byte* _pFreePtr;
	private:	static			std::mutex _mtx;
	};
}

#include "MemoryPool.hpp"

#endif