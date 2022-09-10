#pragma once
#include <Windows.h>
#include <vector>
#include "dataTypes.h"


class esp
{
public:
	uintptr_t* entityList;
	float* viewMatrix;
	LPDIRECT3DDEVICE9 dev;
	int numberOfEnts;
	float distance;
	vec2 headPos;
	bool isLocalpCT;


	void drawLine( int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color);
	float getDistanceBetweenEntAndLocalPlayer( uintptr_t player);
	vec2 getPlayerScreenHeadPos(uintptr_t player);
	void drawBox(vec2 headPos, float distance, float thickness,D3DCOLOR color);

	esp(uintptr_t* entityList, float* viewMatrix, LPDIRECT3DDEVICE9 dev);
	void update();
private:

};

