#pragma once
#include <Windows.h>
#include <vector>
#include "dataTypes.h"

uintptr_t getLocalPlayerStartAddr(uintptr_t* entityList);

int getNumberOfEntities(uintptr_t* entityList);

bool WorldToScreen(vec3_t pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight);

vec3_t getBonePos(uintptr_t entity, int boneId);

bool isPlayerCT(uintptr_t player);

bool isPlayerDormant(uintptr_t player);