#pragma once

#ifndef __SINGLETON_BASE_H__
#define __SINGLETON_BASE_H__

#include "INoncopyable.h"
#include <mutex>

namespace ce 
{
	template <typename T>
	class SingletonBase : public INoncopyable
	{
	protected:	SingletonBase(void) noexcept {};
	protected:	virtual ~SingletonBase(void) noexcept {};

	public:		static T* volatile Instance(void)
				{
					if (_instance == nullptr)
					{
						std::lock_guard<std::mutex> lock(SingletonBase<T>::_mtx);

						if (_instance == nullptr)
						{
							_instance = new T;
						}
					}

					return _instance;
				}

	public:		static void ReleaseSingleton(void)
				{
					if (_instance)
					{
						delete _instance;
						_instance = nullptr;
					}
				}

	protected:	static T* volatile	_instance;
	private:	static std::mutex	_mtx;
	};

	template <typename T>
	T* volatile	SingletonBase<T>::_instance = nullptr;

	template <typename T>
	std::mutex	SingletonBase<T>::_mtx;
}

#endif