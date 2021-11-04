#pragma once

#ifndef __INOCOPYABLE_H__
#define __INOCOPYABLE_H__

namespace ce
{
	class INoncopyable
	{
	protected:	INoncopyable(void) noexcept { __noop; }
	protected:	~INoncopyable(void) noexcept { __noop; }

	public:		INoncopyable(const INoncopyable&) noexcept = delete;
	public:		INoncopyable& operator = (const INoncopyable&) noexcept = delete;
	};
}

#endif