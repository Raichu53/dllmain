#include "includes.h"

void patch(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oProc;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oProc);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oProc, &oProc);
}

bool hook(char* src, char* dst, int len)
{
	if (len < 5) return false;
	DWORD oProc;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oProc);
	memset(src, 0x90, len);
	uintptr_t returnAddr = (uintptr_t)(dst - src - 5);
	*src = (char)0xE9;
	*(uintptr_t*)(src + 1) = (uintptr_t)returnAddr;
	VirtualProtect(src, len, oProc, &oProc);

}

char* TrampHook(char* src, char* dst, unsigned int len)
{
	if (len < 5) return 0;
	char* gateway = (char*)VirtualAlloc(0, len + 5,
		MEM_COMMIT | MEM_RESERVE,	PAGE_EXECUTE_READWRITE);
	memcpy(gateway, src, len);
	uintptr_t returnAddr = (uintptr_t)(src - gateway - 5);
	*(gateway + len) = 0xE9;
	*(uintptr_t*)(gateway + len + 1) = returnAddr;
	
	if (hook(src, dst, len))
	{
		return gateway;
	}
	else return nullptr;
}
