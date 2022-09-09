#pragma once
#include <Windows.h>
#include <vector>
#include "dataTypes.h"

namespace esp
{
	void drawFilledRect(LPDIRECT3DDEVICE9 dev, float x, float y, int w, int h, D3DCOLOR color);
	void drawLine(LPDIRECT3DDEVICE9 dev, int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color);
	float getDistanceBetweenEntAndLocalPlayer(uintptr_t localPlayer,uintptr_t player);
	vec2 getPlayerScreenHeadPos(uintptr_t player, float* viewMatrix);
	void drawBox(vec2 headPos, float distance, LPDIRECT3DDEVICE9 dev);
}
