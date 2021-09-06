#include "stdafx.h"
#include "proc.h"
//https://guidedhacking.com/threads/how-to-hack-any-game-first-internal-hack-dll-tutorial.12142/

DWORD GetProcId(const wchar_t* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
                WCHAR *procEntryName = nullptr;
                mbstowcs(procEntryName, procEntry.szExeFile, strlen(procEntry.szExeFile));

				if (!_wcsicmp(procEntryName, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));

		}
	}
	CloseHandle(hSnap);
	return procId;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr;
    // This structure contains lots of goodies about a module
    MODULEENTRY32 modEntry = { 0 };
    // Grab a snapshot of all the modules in the specified process
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

    if (!hSnap)
        return NULL;

	if (hSnap != INVALID_HANDLE_VALUE)
	{
        // You have to initialize the size, otherwise it will not work
		modEntry.dwSize = sizeof(modEntry);

        // Get the first module in the process
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
                WCHAR *modEntryName = nullptr;
                mbstowcs(modEntryName, modEntry.szModule, strlen(modEntry.szModule));

                // Check if the module name matches the one we're looking for
				if (!_wcsicmp(modEntryName, modName))
				{
                    // If it does, close the snapshot handle and return the base address
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    CloseHandle(hSnap);
                    return modBaseAddr;
				}
                // Grab the next module in the snapshot
			} while (Module32Next(hSnap, &modEntry));
		}
	}
    // We couldn't find the specified module, so return NULL
	CloseHandle(hSnap);
	return NULL;
}

uintptr_t FindDereferencedMultilevelPointerAddress(HANDLE hProc, uintptr_t ptr, const std::vector<unsigned int>& offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int offset : offsets)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), nullptr);
		addr += offset;
	}
	return addr;
}