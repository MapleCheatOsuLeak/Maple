﻿#include <iostream>
#include <thread>
#include <windows.h>
#include <clocale>


#include "Config/Config.h"
#include "Features/Timewarp/Timewarp.h"
#include "Features/Visuals/VisualsSpoofers.h"
#include "Hooks/Hooks.h"
#include "Sdk/Anticheat/Anticheat.h"
#include "Sdk/Audio/AudioEngine.h"
#include "Sdk/Bindings/BindingManager.h"
#include "Sdk/ConfigManager/ConfigManager.h"
#include "Sdk/Input/InputManager.h"
#include "Sdk/Mods/ModManager.h"
#include "Sdk/Osu/GameBase.h"
#include "Sdk/Player/HitObjectManager.h"
#include "Sdk/Player/Player.h"
#include "Sdk/Player/Ruleset.h"
#include "Utilities/Logging/Logger.h"
#include "Sdk/Osu/GameField.h"

DWORD WINAPI Initialize(LPVOID data_addr);
void InitializeMaple(const std::string& username);
void InitializeLogging(const std::string& directory);
void InitializeSdk();
void StartFunctions();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    std::setlocale(LC_NUMERIC, "en_US");
    DisableThreadLibraryCalls(hModule);

    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, Initialize, nullptr, 0, nullptr);
	
    return TRUE;
}

std::string GetWorkingDirectory(const std::string& username)
{
    char* val;
    size_t len;
    errno_t err = _dupenv_s(&val, &len, "APPDATA"); //TODO: xor later

    std::string path(val);
    path += "\\" + username; //TODO: hash later
    
    return path;
}

DWORD WINAPI Initialize(LPVOID data_addr)
{
	//TODO: initialize comms stuff here
    InitializeMaple("MapleRewriteTest");

    return 0;
}

void InitializeMaple(const std::string& username)
{
    std::string workingDirectory = GetWorkingDirectory(username);
	
    Vanilla::Initialize();

    InitializeLogging(workingDirectory);

    InitializeSdk();

    Config::Initialize(workingDirectory);

    Hooks::InstallAllHooks();

    StartFunctions();
}

void InitializeLogging(const std::string& directory)
{
#ifdef _DEBUG
    Logger::Initialize(directory + "\\runtime.log", LogSeverity::All, true, L"Runtime log | Maple");
#else
    Logger::Initialize(directory + "\\runtime.log", LogSeverity::All);
#endif
	
    Logger::Log(LogSeverity::Info, "Initialization started.");
}

void InitializeSdk()
{
    Anticheat::Initialize();
    GameBase::Initialize();
    GameField::Initialize();
    InputManager::Initialize();
    ConfigManager::Initialize();
    BindingManager::Initialize();
    AudioEngine::Initialize();
    ModManager::Initialize();
    Player::Initialize();
    Ruleset::Initialize();
    HitObjectManager::Initialize();
}

void StartFunctions()
{
    Anticheat::DisableAnticheat();

    CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Timewarp::TimewarpThread), nullptr, 0, nullptr);
    CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(VisualsSpoofers::FlashlightRemoverThread), nullptr, 0, nullptr);
}
