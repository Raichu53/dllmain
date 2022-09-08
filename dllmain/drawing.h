#pragma once
#include <Windows.h>
#include <vector>
#include "dataTypes.h"

namespace esp
{
	void drawFilledRect(LPDIRECT3DDEVICE9 dev, float x, float y, int w, int h, D3DCOLOR color);
	bool drawLine(LPDIRECT3DDEVICE9 dev, float x, float y, float lenght, float thicknessFactor,bool vertical, D3DCOLOR color);
	vec2 playerScale(uintptr_t player, float* viewMatrix,LPDIRECT3DDEVICE9 dev);
}
