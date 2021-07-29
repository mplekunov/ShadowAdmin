#pragma once

#include "ConfigFile.h"

#include <Windows.h>
#include <string>

class StartProcess
{
private:
	STARTUPINFOA si{ sizeof(STARTUPINFOA) };
	PROCESS_INFORMATION pi{};
	DWORD isNewWindow{};
	LPSTR location{};

	std::string& GetFormattedLocation(std::string& location);

public:
	StartProcess() = delete;
	StartProcess(std::string& location, bool isNewWindow);

	const PROCESS_INFORMATION GetProcessInfo();

};
