#include <Windows.h>

class HackClass
{
public:
	esp* espHack;
	LPDIRECT3DDEVICE9 pDevice = nullptr;

	uintptr_t clientBase = (uintptr_t)GetModuleHandleW(L"client.dll");
	float* viewMatrix = (float*)(clientBase + (uintptr_t)offsets::dwViewMatrix);
	uintptr_t* entityList = reinterpret_cast<uintptr_t*>((uintptr_t)GetModuleHandleW(L"client.dll") + (uintptr_t)offsets::dwEntityList);
	
	uintptr_t engineBase = (uintptr_t)GetModuleHandleW(L"engine.dll");
	uintptr_t* clientstate = (uintptr_t*)(engineBase + (uintptr_t)offsets::dwClientState);
	uintptr_t* clientVA = (uintptr_t*)(*clientstate + (uintptr_t)offsets::dwClientState_ViewAngles);

	HackClass(esp* espHack);
private:

};

