#pragma once
#include <windows.h>

void SendMouseInput(int amount, DWORD dwFlag);
void SendMouseInput(int amount, DWORD dwFlag, LONG dx, LONG dy);
void SendKeyboardInput(int amount, WORD key, DWORD dwFlag = 0);

