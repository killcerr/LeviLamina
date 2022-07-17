// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <mutex>
#include <thread>
#include <LLAPI.h>
#include <LoggerAPI.h>
#include <HookAPI.h>

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            LL::registerPlugin("LLUnitTest", "Unit test for LiteLoaderBDS", LL::Version(0, 0, 1));
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

Logger logger("LLUnitTest");

////////////// Run Tests //////////////

void RunI18NTest();

extern "C" __declspec(dllexport) void onPostInit() {
    logger.info("LLUnitTest loaded!");

    // To cancel some module tests, just comment them
    RunI18NTest();
}

////////////// Hook main //////////////
bool error = false;

void Error(const std::string& msg) {
    logger.error(msg);
    error = true;
}

THook(int, "main", int argc, char** argv) {
    auto res = original(argc, argv);
    if (error) {
        logger.error("Some errors occurred in unit test! Return 1");
        return 1;
    }
    return res;
}