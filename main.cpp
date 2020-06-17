#include <iostream>
#include "EditMemory.h"

DWORD m_hActiveWeapon = 0x0DB8;
DWORD dwEntityList = 0xC490B4;
DWORD m_bReadyToBackstab = 0xC64;

int main()
{
	int procId = GetProcId(L"hl2.exe");
	DWORD moduleBase = GetModuleBaseAddress(procId, L"client.dll");
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
	while (true)
	{
		DWORD localPlayer = editmemory::ReadMem<DWORD>(handle, LPVOID(moduleBase + 0xC3B590));
		DWORD active_weapon = editmemory::ReadMem<DWORD>(handle, LPVOID(localPlayer + m_hActiveWeapon));
		DWORD current_weapon = editmemory::ReadMem<DWORD>(handle, LPVOID(moduleBase + dwEntityList + (((active_weapon & 0xFFF) - 1) * 0x10)));
		bool bReadyToBackstab = editmemory::ReadMem<bool>(handle, LPVOID(current_weapon + m_bReadyToBackstab));
		std::cout << bReadyToBackstab << std::endl;
		if (bReadyToBackstab == 1)
		{
			//dwForceAttack
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(20);
			//dwForceAttack
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(10);
		}
	}
}
