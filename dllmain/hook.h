#pragma once

void patch(BYTE* dst, BYTE* src, unsigned int size);

bool hook(char* src, char* dst, int len);

char* TrampHook(char* src, char* dst, unsigned int len);