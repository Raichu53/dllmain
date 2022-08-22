#pragma once

typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

bool getD3D9Device(void** pTable, size_t size);

static HWND window;

extern int windowHeight, windowWidth;

extern LPDIRECT3DDEVICE9 pDevice;