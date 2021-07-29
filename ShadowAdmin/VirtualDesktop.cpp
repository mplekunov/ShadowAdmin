#include "VirtualDesktop.h"
#include "MKControls.h"

#include <Windows.h>


void VirtualDesktop::createVirtualDesktop()
{
	SendKeyboardInput(1, VK_CONTROL);
	SendKeyboardInput(1, VK_LWIN);
	SendKeyboardInput(1, VkKeyScanA('d'));

	SendKeyboardInput(1, VK_CONTROL, KEYEVENTF_KEYUP);
	SendKeyboardInput(1, VK_LWIN, KEYEVENTF_KEYUP);
	SendKeyboardInput(1, VkKeyScanA('d'), KEYEVENTF_KEYUP);

	this->numberOfActiveDesktops++;
}

void VirtualDesktop::switchToPreviousVirtualDesktop()
{
	SendKeyboardInput(1, VK_CONTROL);
	SendKeyboardInput(1, VK_LWIN);
	SendKeyboardInput(1, VK_LEFT);

	SendKeyboardInput(1, VK_CONTROL, KEYEVENTF_KEYUP);
	SendKeyboardInput(1, VK_LWIN, KEYEVENTF_KEYUP);
	SendKeyboardInput(1, VK_LEFT, KEYEVENTF_KEYUP);
}

void VirtualDesktop::switchToNextVirtualDesktop()
{
	SendKeyboardInput(1, VK_CONTROL);
	SendKeyboardInput(1, VK_LWIN);
	SendKeyboardInput(1, VK_RIGHT);

	SendKeyboardInput(1, VK_CONTROL, KEYEVENTF_KEYUP);
	SendKeyboardInput(1, VK_LWIN, KEYEVENTF_KEYUP);
	SendKeyboardInput(1, VK_RIGHT, KEYEVENTF_KEYUP);
}

int VirtualDesktop::getNumberOfActiveDesktops()
{
	return this->numberOfActiveDesktops;
}

void VirtualDesktop::closeVirtualDesktop()
{
	SendKeyboardInput(1, VK_CONTROL);
	SendKeyboardInput(1, VK_LWIN);
	SendKeyboardInput(1, VK_F4);

	SendKeyboardInput(1, VK_CONTROL, KEYEVENTF_KEYUP);
	SendKeyboardInput(1, VK_LWIN, KEYEVENTF_KEYUP);
	SendKeyboardInput(1, VK_F4, KEYEVENTF_KEYUP);

	this->numberOfActiveDesktops--;
}
