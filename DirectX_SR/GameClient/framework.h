#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <queue>
#include <chrono>
#include <unordered_set>

#include "../External/include/fmod.hpp"
#define __USE_FMOD__

#include "d3d9.h"
#pragma comment(lib, "d3d9.lib")

#include "d3dx9.h"
#pragma comment(lib, "d3dx9.lib")

#include "AutoDetectMemoryLeak.h"
#include "ManagerDef.h"
#include "ConstValues.h"
#include "CEMath.h"

using namespace ce;

#include "Game_Struct.h"
#include "Game_Math.h"
#include "Game_Enum.h"