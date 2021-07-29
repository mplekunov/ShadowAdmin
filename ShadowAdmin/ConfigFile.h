#pragma once
#include <string>
#include "Process.h"
#include <vector>

struct ConfigFormat {
	std::string processLabel{ "[Start Process]" };
	std::string processName{ "ProcessName" };
	std::string processLocation{ "ProcessLocation" };
	std::string processNewWindow{ "StartInNewWindow" };
	std::string processNewDesktop{ "StartOnNewVirtualDesktop" };
	std::string processWaitTime{ "WaitTimeInSeconds" };

	std::string afkBotLabel{ "[AFK Bot]" };
	std::string afkBotAdmin{ "AntiAFK" };
	std::string afkBotTimer{ "TimerInMinutes" };
	std::string afkBotRestart{ "RestartWindowsOnTimerEnd" };
};

struct ProcessFormat {
	std::string name{};
	std::string location{};
	bool isNewWindow{};
	bool isNewDesktop{};
	int waitTime{};
};

struct AFKBotFormat {
	int timer{};
	bool isRestart{};
	bool isAntiAFK{};
};

class ConfigFile : public ConfigFormat{
private:
	int processCounter{ 0 };
	const char* fileName{};

	std::vector<ProcessFormat> processes{};
	AFKBotFormat afkBot{};

	std::string RemoveString(std::string strOriginal, std::string strToRemove);
	void GetProcessCreationInfo(ProcessFormat &process, std::string lineToProcess);    
	void GetAFKBotInfo(std::string lineToProcess);
public:
	ConfigFile() = delete;
	ConfigFile(const char* fileName);
	
	std::vector<ProcessFormat> GetProcesses();
	AFKBotFormat GetAFKBotFormat();
};