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
	protected:				MemoryPool(void) { __noop; }
	protected:	virtual		~MemoryPool(void) { __noop; }

	public:		static void* operator new(std::size_t allocLength)
				{
					//std::lock_guard<std::mutex> guard(_mtx);
					if (sizeof(T) != allocLength)
						CE_ASSERT("ckswns", "메모리풀에 예약된 크기와 다른 크기의 할당 요청입니다");
					if (sizeof(T) < 1)
						CE_ASSERT("ckswns", "잘못된 크기의 할당요청입니다");

					if (!_pFreePtr)
						AllocBlock();

					byte* ReturnPointer = _pFreePtr;
					_pFreePtr = *reinterpret_cast<byte**>(ReturnPointer);

					return ReturnPointer;
				}

	public:		static void	operator delete(void* deletePointer)
				{
					//std::lock_guard<std::mutex> guard(_mtx);

					*reinterpret_cast<byte**>(deletePointer) = _pFreePtr;
					_pFreePtr = static_cast<byte*>(deletePointer);
				}

	private:	static void	AllocBlock()
				{
					_pFreePtr = new byte[sizeof(T) * ALLOC_BLOCK_SIZE];

					byte** Current = reinterpret_cast<byte**>(_pFreePtr);
					byte* Next = _pFreePtr;

					for (int i = 0; i < ALLOC_BLOCK_SIZE - 1; ++i)
					{
						Next += sizeof(T);
						*Current = Next;
						Current = reinterpret_cast<byte**>(Next);
					}

					*Current = 0;
				}

	private:	static	byte* _pFreePtr;
	private:	static	std::mutex _mtx;
	};

	template <class T, int ALLOC_BLOCK_SIZE>
	byte* MemoryPool<T, ALLOC_BLOCK_SIZE>::_pFreePtr;

	template <class T, int ALLOC_BLOCK_SIZE>
	std::mutex MemoryPool<T, ALLOC_BLOCK_SIZE>::_mtx;
}

#endif