#include "includes.h"

//v table
void* d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
tEndScene oEndScene = nullptr;
extern LPDIRECT3DDEVICE9 pDevice = nullptr;


HackClass Hack = HackClass(NULL);
esp espHack = esp(Hack.entityList, Hack.viewMatrix, Hack.pDevice);

void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{
	if (!pDevice)
	{
		pDevice = o_pDevice;
		Hack.espHack = &espHack;
		Hack.espHack->dev = pDevice;
	}

	Hack.espHack->update();
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
		Sleep(5);
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