#pragma once

#ifndef __ASSERTION_H__
#define __ASSERTION_H__

#include <assert.h>
#include <cstdio>
#include <string>
#include "Log.h"

namespace ce
{

#ifdef _DEBUG
#define CE_ASSERT(DEVELOPER, MESSAGE) DebugAssert(DEVELOPER, MESSAGE);
#else
#define CE_ASSERT(DEVELOPER, MESSAGE) ReleaseAssert(DEVELOPER, MESSAGE);
#endif

	static void DebugAssert(const char* developer, const char* message, const char* fileName = nullptr)
	{
		std::string str = "Developer: ";
		str = str + developer + "\n" + "ERR : " + message;

		MessageBoxA(nullptr, str.c_str(), "ASSERT", MB_OK);

		if (fileName == nullptr)
			fileName = "../Log/debug_log.txt";
		
		Log::WriteLog(fileName, str.c_str());
		__debugbreak();
	}

	static void ReleaseAssert(const char* developer, const char* message, const char* fileName = nullptr)
	{
		if (fileName == nullptr)
			fileName = "../Log/release_log.txt";

		std::string str = "Developer: ";
		str = str + developer + "\n" + "ERR : " + message;

		Log::WriteLog(fileName, str.c_str());
	}
}

#endif