#include "includes.h"

//v table
void* d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
tEndScene oEndScene = nullptr;
extern LPDIRECT3DDEVICE9 pDevice = nullptr;

uintptr_t engineBase = (uintptr_t)GetModuleHandleW(L"engine.dll");
uintptr_t* clientstate = (uintptr_t*)(engineBase + (uintptr_t)offsets::dwClientState);
uintptr_t* clientVA = (uintptr_t*)(*clientstate + (uintptr_t)offsets::dwClientState_ViewAngles);

uintptr_t clientBase = (uintptr_t)GetModuleHandleW(L"client.dll");
uintptr_t* entityList = (uintptr_t*)(clientBase + (uintptr_t)offsets::dwEntityList);
float* viewMatrix = (float*)(clientBase + (uintptr_t)offsets::dwViewMatrix);


void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{
	if (!pDevice)
	{
		pDevice = o_pDevice;
	}
	//fred
	uintptr_t* myplayer = entityList + 20;
	esp::playerHeight(*myplayer,viewMatrix,pDevice);
	
	oEndScene(pDevice);
}

DWORD WINAPI hThread(HMODULE hMod)
{
	
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	
	if (getD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		memcpy(EndSceneBytes, (char*)d3d9Device[42], 7);

		oEndScene = (tEndScene)TrampHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
	}

	while (!GetAsyncKeyState(VK_END))
	{
		Sleep(1);
	}

	//unhook
	patch((BYTE*)d3d9Device[42], EndSceneBytes, 7);
	
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hMod, 0);
	return 0;
}
BOOL APIENTRY DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)hThread,hInstDLL,0,NULL));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}