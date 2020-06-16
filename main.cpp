#include <iostream>
#include "EditMemory.h"

int main()
{
	int procId = GetProcId(L"hl2.exe");
	DWORD moduleBase = GetModuleBaseAddress(procId, L"client.dll");
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
	while (true)
	{
		DWORD ptrBase = moduleBase + 0x00C37ADC;
		std::vector<unsigned int> m_CanBackStab = { 0x0,0x14,0x4,0x1EC,0x6F4 };
		uintptr_t BackStab = FindDynamicAddr(handle, ptrBase, m_CanBackStab);
		int CanBackStab = editmemory::ReadMem<int>(handle, LPVOID(BackStab));
		std::cout << CanBackStab << std::endl;
		if (CanBackStab == 256)
		{
			//dwForceAttack
			editmemory::WriteMem<int>(handle, LPVOID(moduleBase + 0xC692EC), 5);
			Sleep(20);
			//dwForceAttack
			editmemory::WriteMem<int>(handle, LPVOID(moduleBase + 0xC692EC), 4);
			Sleep(10);
		}
	}
}