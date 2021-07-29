
#include "StartProcess.h"
#include <iostream>
#include <fstream>

StartProcess::StartProcess(std::string& location, bool isNewWindow)
{
	this->si.cb = sizeof(si);
	this->location = (LPSTR)GetFormattedLocation(location).c_str();
	if (isNewWindow)
		this->isNewWindow = CREATE_NEW_CONSOLE;
	else
		this->isNewWindow = CREATE_NO_WINDOW;

	CreateProcessA(NULL, this->location, NULL, NULL, FALSE, this->isNewWindow, NULL, NULL, &this->si, &this->pi);
}

std::string& StartProcess::GetFormattedLocation(std::string& location)
{
	if (location.find(".bat") != std::string::npos)
		location.assign("cmd.exe /c " + location);

	return location;
}

const PROCESS_INFORMATION StartProcess::GetProcessInfo() { return this->pi; };

