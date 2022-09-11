#include "includes.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "dataTypes.h"


uintptr_t getLocalPlayerStartAddr(uintptr_t* entityList)
{
	uintptr_t localPlayerStartAddr = *entityList;
	return localPlayerStartAddr;
}
/// <summary>
/// get the number of entities in the lobby (it doesnt count the localPlayer)
/// </summary>
/// <param name="entityList"></param>
/// <returns></returns>
int getNumberOfEntities(uintptr_t* entityList)
{
	//skip pWorld so add 6 bytes padding and another 6 to skip the pLocalPlayer
	uintptr_t* pEnt = (uintptr_t*)(entityList);
	int entCount = 0;
	
	
	while (*pEnt != 0)
	{
		entCount++;

		pEnt += 4;
		
	}
	std::cout << "\n";
	return entCount;
}
bool WorldToScreen(vec3_t pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	vec3_t NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}
vec3_t getBonePos(uintptr_t entity, int boneId)
{
	vec3_t pos;
	uintptr_t* pBoneAddr = (uintptr_t*)(entity + offsets::m_dwBoneMatrix);
	
	pos.x = *((float*)*pBoneAddr + boneId * 12 + 3);
	pos.y = *((float*)*pBoneAddr + boneId * 12 + 7);
	pos.z = *((float*)*pBoneAddr + boneId * 12 + 11);
	
	return pos;
}
bool isPlayerCT(uintptr_t player)
{
	uintptr_t* pLocalPlayerTeamId = reinterpret_cast<uintptr_t*>(player + offsets::m_iTeamNum);
	if (*(int*)pLocalPlayerTeamId == 2)
	{
		return false;
	}
	return true;
}
//return false if player is updated (<=> not dormant)
bool isPlayerDormant(uintptr_t player)
{
	uintptr_t* pPlayerDormant = reinterpret_cast<uintptr_t*>(player + offsets::m_bDormant);
	if (*(int*)pPlayerDormant)
	{
		return true;
	}
	return false;
}