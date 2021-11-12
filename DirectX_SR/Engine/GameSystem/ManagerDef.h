#pragma once
#include "AssetManager.h"
#ifdef __USE_FMOD__
#include "FMODManager.h"
#endif
#include "D3D9Device.h"
#include "INIManager.h"
#include "SceneManager.h"
#include "Input.h"
#include "TimeManager.h"

#define ASSETMANAGER	AssetManager::Instance()
#ifdef __USE_FMOD__
#define FMODMANAGER		FMODManager::Instance()
#endif
#define D3D9DEVICE		D3D9Device::Instance()
#define INIMANAGER		INIManager::Instance()
#define SCENEMANAGER	SceneManager::Instance()
#define INPUT			Input::Instance()
#define TIMEMANAGER		TimeManager::Instance()