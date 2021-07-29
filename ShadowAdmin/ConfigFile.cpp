#include "ConfigFile.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <Windows.h>

ConfigFile::ConfigFile(const char* fileName)
{
	this->fileName = fileName;

	std::ifstream iFile{ this->fileName };
	std::string outLine{};

	while (std::getline(iFile, outLine, '\n')) {
		if (outLine == this->processLabel) {
			ProcessFormat currentProcess{};
			while (std::getline(iFile, outLine, '\n') && outLine != this->processLabel && outLine != "")
				GetProcessCreationInfo(currentProcess, outLine);

			this->processes.push_back(currentProcess);
		}
		else if (outLine == this->afkBotLabel) {
			while (std::getline(iFile, outLine, '\n') && outLine != this->afkBotLabel)
				GetAFKBotInfo(outLine);
		}
	}
}

std::string ConfigFile::RemoveString(std::string strOriginal, std::string strToRemove) {
	strOriginal = strOriginal.substr(strToRemove.length(), strOriginal.length());
	strOriginal.erase(std::remove_if(strOriginal.begin(), strOriginal.end(), isspace), strOriginal.end());
	strOriginal.erase(strOriginal.begin() + strOriginal.find('='));
	return strOriginal;
}

void ConfigFile::GetProcessCreationInfo(ProcessFormat &process, std::string lineToProcess)
{	
	if (lineToProcess.find(this->processName) != std::string::npos)
		process.name = RemoveString(lineToProcess, this->processName);
	else if (lineToProcess.find(this->processLocation) != std::string::npos)
		process.location = RemoveString(lineToProcess, this->processLocation);
	else if (lineToProcess.find(this->processNewWindow) != std::string::npos) {
		std::string isNewWindow{ RemoveString(lineToProcess, this->processNewWindow) };

		if (isNewWindow == "false")
			process.isNewWindow = false;
		else
			process.isNewWindow = true;
	}
	else if (lineToProcess.find(this->processNewDesktop) != std::string::npos) {
		std::string isNewDesktop{ RemoveString(lineToProcess, this->processNewDesktop) };

		if (isNewDesktop == "false")
			process.isNewDesktop = false;
		else
			process.isNewDesktop = true;
	}
	else if (lineToProcess.find(this->processWaitTime) != std::string::npos)
		process.waitTime = std::stoi(RemoveString(lineToProcess, this->processWaitTime));
}

void ConfigFile::GetAFKBotInfo(std::string lineToProcess) {
	if (lineToProcess.find(this->afkBotTimer) != std::string::npos)
		this->afkBot.timer = std::stoi(RemoveString(lineToProcess, this->afkBotTimer));
	else if (lineToProcess.find(this->afkBotRestart) != std::string::npos) {
		std::string isRestart{ RemoveString(lineToProcess, this->afkBotRestart) };

		if (isRestart == "false")
			this->afkBot.isRestart = false;
		else
			this->afkBot.isRestart = true;
	}
	else if (lineToProcess.find(this->afkBotAdmin) != std::string::npos) {
		std::string isAdmin{ RemoveString(lineToProcess, this->afkBotAdmin) };

		if (isAdmin == "false")
			this->afkBot.isAntiAFK = false;
		else
			this->afkBot.isAntiAFK = true;
	}
}

AFKBotFormat ConfigFile::GetAFKBotFormat() {
	return this->afkBot;
}

std::vector<ProcessFormat> ConfigFile::GetProcesses() {
	return this->processes;
}

