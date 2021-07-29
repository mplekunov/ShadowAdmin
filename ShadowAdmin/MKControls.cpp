#include "MKControls.h"
#include <windows.h>

void SendMouseInput(int amount, DWORD dwFlag) {
	INPUT mouse_input{};

	mouse_input.type = INPUT_MOUSE;
	mouse_input.mi.dwFlags = dwFlag;
	SendInput(amount, &mouse_input, sizeof(mouse_input));

	ZeroMemory(&mouse_input, sizeof(mouse_input));
}

void SendMouseInput(int amount, DWORD dwFlag, LONG dx, LONG dy)
{
	INPUT mouse_input{};

	mouse_input.type = INPUT_MOUSE;
	mouse_input.mi.dwFlags = dwFlag;
	mouse_input.mi.dx = dx;
	mouse_input.mi.dy = dy;
	SendInput(amount, &mouse_input, sizeof(mouse_input));

	ZeroMemory(&mouse_input, sizeof(mouse_input));
}

void SendKeyboardInput(int amount, WORD key, DWORD dwFlag) {
	INPUT keyboard_input{};

	if (dwFlag) {
		keyboard_input.type = INPUT_KEYBOARD;
		keyboard_input.ki.wVk = key;
		keyboard_input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(amount, &keyboard_input, sizeof(keyboard_input));
	}
	else {
		keyboard_input.type = INPUT_KEYBOARD;
		keyboard_input.ki.wVk = key;
		SendInput(amount, &keyboard_input, sizeof(keyboard_input));
	}
	
	ZeroMemory(&keyboard_input, sizeof(keyboard_input));
}