// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include <windows.h>
#include <gui.h>

//https://guidedhacking.com/threads/how-to-hack-any-game-first-internal-hack-dll-tutorial.12142/

DWORD WINAPI HackThread(HMODULE hModule)
{
    auto hack = new InternalHack();
    auto gui = InternalGUI(hack);
    gui.init();
    gui.draw();
    gui.close();

	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
    default: break;
	}
	return TRUE;
}