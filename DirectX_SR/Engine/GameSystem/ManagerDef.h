#pragma once
#include "AssetManager.h"
#include "FMODManager.h"
#include "D3D9Device.h"
#include "INIManager.h"
#include "SceneManager.h"
#include "Input.h"
#include "TimeManager.h"

#define ASSETMANAGER	AssetManager::Instance()
#define FMODMANAGER		FMODManager::Instance()
#define D3D9DEVICE		D3D9Device::Instance()
#define INIMANAGER		INIManager::Instance()
#define SCENEMANAGER	SceneManager::Instance()
#define INPUT			Input::Instance()
#define TIMEMANAGER		TimeManager::Instance()