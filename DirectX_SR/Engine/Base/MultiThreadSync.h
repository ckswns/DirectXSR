#pragma once
#include "CriticalSection.h"

namespace ce
{
	class Lock;

	template <class T>
	class MultiThreadSync
	{
		friend class Lock;
	public:
		class Lock
		{
		public:
			Lock(void)
			{
				T::mSync.Enter();
			}

			~Lock(void)
			{
				T::mSync.Leave();
			}
		};

	
	public: MultiThreadSync() { __noop; }
	public:	virtual ~MultiThreadSync() { __noop; }

	private:
		static CCriticalSection mSync;
	};

	template <class T>
	CCriticalSection MultiThreadSync<T>::mSync;
}