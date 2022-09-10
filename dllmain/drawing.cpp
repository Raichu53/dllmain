#include "includes.h"

namespace rgb_d3d
{
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR yellow = D3DCOLOR_XRGB(255, 255, 0);
}

void esp::drawLine( int x1,int y1,int x2,int y2,int thickness,D3DCOLOR color)
{
	LPD3DXLINE LineL;
	D3DXCreateLine(dev, &LineL);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);

	LineL->SetWidth(thickness);
	LineL->Draw(Line, 2, color);
	LineL->Release();
}
vec2 esp::getPlayerScreenHeadPos(uintptr_t player)
{
	vec2 screenHead = {};
	vec3_t headPos = getBonePos(player, 8);
	WorldToScreen(headPos, screenHead, viewMatrix, WINDOW_WIDTH, WINDOW_HEIGHT);
	return screenHead;
}
float esp::getDistanceBetweenEntAndLocalPlayer(uintptr_t player)
{

	float distance = {};
	vec3_t entityHeadPos = getBonePos(player, 8);
	vec3_t localHeadPos = getBonePos(*esp::entityList, 8);

	//formula : sqrt((x2-x1)²+(y2-y1)²+(z2-z1)²)
	distance = sqrt(pow((entityHeadPos.x - localHeadPos.x), 2) + pow((entityHeadPos.y - localHeadPos.y), 2) + 
		pow((entityHeadPos.z - localHeadPos.z), 2));
	
	//std::cout << "distance between player : " << (uintptr_t*)player << " and localPlayer is : " << distance << std::endl;

	return distance;
}
void esp::drawBox(vec2 headPos,float distance,float thickness,D3DCOLOR color)
{
	float newDefaultHeight, newDefaultWidth, ratio = {};
	vec2 newDefaultOffset = {};
	
	ratio = distance / DEFAULT_DISTANCE;
	
	if (ratio)
	{
		newDefaultHeight = DEFAULT_HEIGHT / ratio;
		newDefaultWidth = DEFAULT_WIDTH / ratio;
		newDefaultOffset.x = DEFAULT_OFFSET_X / ratio;
		newDefaultOffset.y = DEFAULT_OFFSET_Y / ratio;
	}
	//verticals
	//left
	drawLine( headPos.x - newDefaultOffset.x,
		headPos.y - newDefaultOffset.y,
		headPos.x - newDefaultOffset.x, 
		(headPos.y - newDefaultOffset.y) + newDefaultHeight,
		thickness,color);
	//right
	drawLine((headPos.x - newDefaultOffset.x) + newDefaultWidth, 
		headPos.y - newDefaultOffset.y,
		headPos.x - newDefaultOffset.x + newDefaultWidth,
		(headPos.y - newDefaultOffset.y) + newDefaultHeight,
		thickness,color);

	//horizontals
	//top
	drawLine(headPos.x - newDefaultOffset.x,
		headPos.y - newDefaultOffset.y,
		(headPos.x - newDefaultOffset.x) + newDefaultWidth,
		headPos.y - newDefaultOffset.y,
		thickness, color);
	//bottom
	drawLine( headPos.x - newDefaultOffset.x,
		(headPos.y - newDefaultOffset.y) + newDefaultHeight,
		(headPos.x - newDefaultOffset.x) + newDefaultWidth,
		(headPos.y - newDefaultOffset.y) + newDefaultHeight,
		thickness,color);
}
esp::esp(uintptr_t* entityList,float* viewMatrix,LPDIRECT3DDEVICE9 dev)
{
	esp::entityList = entityList;
	esp::viewMatrix = viewMatrix;
	esp::dev = dev;
	esp::numberOfEnts = getNumberOfEntities(entityList);
}
void esp::update()
{
	uintptr_t* player = nullptr;
	this->isLocalpCT = isPlayerCT(*entityList);
	for (int i = 0; i < this->numberOfEnts; i++)
	{
		if (!i) continue; //bc offset 0 of entList is localPlayer
		
		player = reinterpret_cast<uintptr_t*>(entityList + (i * 4));
		if (!isPlayerDormant(*player))
		{
			this->distance = esp::getDistanceBetweenEntAndLocalPlayer(*player);
			this->headPos = esp::getPlayerScreenHeadPos(*player);

			if (this->distance == 0)
				continue;
			if (isPlayerCT(*player) == this->isLocalpCT)
			{
				esp::drawBox(this->headPos, this->distance, 1, D3DCOLOR_XRGB(0, 255, 0));
			}
			if (isPlayerCT(*player) != this->isLocalpCT)
			{
				esp::drawBox(this->headPos, this->distance, 1, D3DCOLOR_XRGB(255, 0, 0));
			}
		}
	}
}