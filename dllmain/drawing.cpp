#include "includes.h"

namespace rgb_d3d
{
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR yellow = D3DCOLOR_XRGB(255, 255, 0);
}

void esp::drawFilledRect(LPDIRECT3DDEVICE9 dev, float x, float y, int w, int h, D3DCOLOR color)
{
	D3DRECT rect = { x,y,x + w,y + h };
	dev->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}
void esp::drawLine(LPDIRECT3DDEVICE9 dev, int x1,int y1,int x2,int y2,int thickness,D3DCOLOR color)
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
vec2 esp::getPlayerScreenHeadPos(uintptr_t player, float* viewMatrix)
{
	vec2 screenHead = {};
	vec3_t headPos = getBonePos(player, 8);
	WorldToScreen(headPos, screenHead, viewMatrix, WINDOW_WIDTH, WINDOW_HEIGHT);
	return screenHead;
}
float esp::getDistanceBetweenEntAndLocalPlayer(uintptr_t localPlayer,uintptr_t player )
{

	float distance = {};
	vec3_t entityHeadPos = getBonePos(player, 8);
	vec3_t localHeadPos = getBonePos(localPlayer, 8);

	//formula : sqrt((x2-x1)²+(y2-y1)²+(z2-z1)²)
	distance = sqrt(pow((entityHeadPos.x - localHeadPos.x), 2) + pow((entityHeadPos.y - localHeadPos.y), 2) + 
		pow((entityHeadPos.z - localHeadPos.z), 2));
	
	std::cout << "distance between player : " << (uintptr_t*)player << " and localPlayer is : " << distance << std::endl;

	return distance;
}
void esp::drawBox(vec2 headPos,float distance,LPDIRECT3DDEVICE9 dev)
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
	drawLine(dev, headPos.x - newDefaultOffset.x,
		headPos.y - newDefaultOffset.y,
		headPos.x - newDefaultOffset.x, 
		(headPos.y - newDefaultOffset.y) + newDefaultHeight,
		2,rgb_d3d::green);
	//right
	drawLine(dev, (headPos.x - newDefaultOffset.x) + newDefaultWidth, 
		headPos.y - newDefaultOffset.y,
		headPos.x - newDefaultOffset.x + newDefaultWidth,
		(headPos.y - newDefaultOffset.y) + newDefaultHeight,
		2,rgb_d3d::green);

	//horizontals
	//top
	drawLine(dev, headPos.x - newDefaultOffset.x,
		headPos.y - newDefaultOffset.y,
		(headPos.x - newDefaultOffset.x) + newDefaultWidth,
		headPos.y - newDefaultOffset.y, 
		2,rgb_d3d::green);
	//bottom
	drawLine(dev, headPos.x - newDefaultOffset.x,
		(headPos.y - newDefaultOffset.y) + newDefaultHeight,
		(headPos.x - newDefaultOffset.x) + newDefaultWidth,
		(headPos.y - newDefaultOffset.y) + newDefaultHeight,
		2, rgb_d3d::green);
}