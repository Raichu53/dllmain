#include "includes.h"

void esp::drawFilledRect(LPDIRECT3DDEVICE9 dev, float x, float y, int w, int h, D3DCOLOR color)
{
	D3DRECT rect = { x,y,x + w,y + h };
	dev->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}
bool esp::drawLine(LPDIRECT3DDEVICE9 dev, float x, float y, float lenght,float thicknessFactor,bool vertical, D3DCOLOR color)
{
	//use D3DCOLOR_XRGB cast for calling ex: esp::drawLine(pDevice, 100, 150, 100,  3.f, true, D3DCOLOR_XRGB(255, 0, 255));
	if (!vertical)
	{
		D3DRECT line = { x,y,x + lenght,y + (1 * thicknessFactor) };
		dev->Clear(1, &line, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
		return true;
	}

	D3DRECT line = { x,y,x + (1 * thicknessFactor),y + lenght };
	dev->Clear(1, &line, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
	return true;
}

vec2 esp::playerHeight(uintptr_t player,float* viewMatrix,LPDIRECT3DDEVICE9 dev )
{

	vec2 scale = {};
	vec2 screenHead = {};


	vec3_t headPos = getBonePos(player, 8);
	

	WorldToScreen(headPos, screenHead, viewMatrix, WINDOW_WIDTH, WINDOW_HEIGHT);
	drawFilledRect(dev, screenHead.x, screenHead.y, 10, 10, D3DCOLOR_XRGB(0, 255, 0));
	
	
	//std::cout << "headPos2d : " << screenHead.x << " , " << screenHead.y << std::endl;

	return scale;
}
