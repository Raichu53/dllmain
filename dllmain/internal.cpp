#include "includes.h"
#include <string>
#include <sstream>
#include <iomanip>

uintptr_t getLocalPlayerStartAddr(uintptr_t* entityList)
{
	
	return 0;
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

		pEnt += 10;
		
	}
	std::cout << "\n";
	return entCount;
}