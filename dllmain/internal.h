#pragma once
#include <Windows.h>
#include <vector>
#include "dataTypes.h"

uintptr_t getLocalPlayerStartAddr(uintptr_t* entityList);

int getNumberOfEntities(uintptr_t* entityList);

bool WorldToScreen(vec3_t pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight);