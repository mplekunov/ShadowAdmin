#include "VirtualDesktop.h"
#include "MKControls.h"
#include "StartProcess.h"
#include "ConfigFile.h"

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <vector>

const int SECONDS_IN_MINUTE = 60;
const int MILLISECONDS_IN_SECONDS = 1000;
using namespace std;

HWND hwnd_shadow = {};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
void runProcessesFromConfig(ConfigFile &config, VirtualDesktop &desktop);
bool startShadow(HWND hwnd_shadow, DWORD shadowProcessId);


int main()
{
    const std::string configFileName{ "config.ini" };

    ConfigFile config(configFileName.c_str());

    AFKBotFormat afkBot{ config.GetAFKBotFormat() };

    VirtualDesktop desktop;
    
    runProcessesFromConfig(config, desktop);

    //Timer
    clock_t winShutdownTimer{};

    while (true) {
        clock_t winShutdownTimer = clock();

        while (clock() - winShutdownTimer < afkBot.timer * SECONDS_IN_MINUTE * MILLISECONDS_IN_SECONDS && FindWindowA("Shadow-Window-Class", NULL)) {
            if (afkBot.isAntiAFK) {
                srand(time(NULL));

                int pos_offset = rand() % (10 + 1 - 1) + 1;

                for (int i{ 0 }; i < pos_offset; i++) {
                    SendKeyboardInput(1, VK_MENU);
                    SendKeyboardInput(1, VK_TAB);
                    Sleep(200);
                    SendKeyboardInput(1, VK_MENU, KEYEVENTF_KEYUP);
                    SendKeyboardInput(1, VK_TAB, KEYEVENTF_KEYUP);

                    Sleep(1000);

                    SetCursorPos(20, 1060);
                    Sleep(10);
                    SendMouseInput(1, MOUSEEVENTF_LEFTUP);
                    Sleep(200);
                    SendMouseInput(1, MOUSEEVENTF_LEFTDOWN);
                }

                Sleep(5000);
            }

            Sleep(5000);
        }

        if (!FindWindowA("Shadow-Window-Class", NULL)) {
            DWORD shadowProcessId{};
            GetWindowThreadProcessId(hwnd_shadow, &shadowProcessId);

            startShadow(hwnd_shadow, shadowProcessId);
        }
    }

    if (desktop.getNumberOfActiveDesktops() > 0) {
        for (int i{ 0 }; i < desktop.getNumberOfActiveDesktops(); i++) {
            BringWindowToTop(GetDesktopWindow());
            SetFocus(GetDesktopWindow());
            SetActiveWindow(GetDesktopWindow());
            SetForegroundWindow(GetDesktopWindow());
            desktop.closeVirtualDesktop();
        }
    }

    if (afkBot.isRestart)
        system("C:\\windows\\system32\\shutdown /r");

    return 0;
    exit(0);
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    DWORD lpdwProcessId{};
    
    GetWindowThreadProcessId(hwnd, &lpdwProcessId);      
    
    if (lpdwProcessId == lParam) {
        std::string title(GetWindowTextLengthA(hwnd) + 1, 0);
        int size = GetWindowTextA(hwnd, &title[0], title.size());
        title.resize(size);

        if (!title.compare("Shadow")) {
            hwnd_shadow = hwnd;
            return false;
        }
    }

    return true;
}

void runProcessesFromConfig(ConfigFile &config, VirtualDesktop &desktop) {

    for (int i{ 0 }; i < config.GetProcesses().size(); i++) {
        ProcessFormat processInfo = config.GetProcesses().at(i);
        
        if (processInfo.isNewDesktop)
            desktop.createVirtualDesktop();

        if (processInfo.name == "Shadow") {
            DWORD shadowProcessId{};

            do {
                if (!FindWindowA(NULL, "Shadow")) {
                    StartProcess startedProcess(processInfo.location, processInfo.isNewWindow);
                    WaitForSingleObject(startedProcess.GetProcessInfo().hProcess, processInfo.waitTime * MILLISECONDS_IN_SECONDS);
                    shadowProcessId = startedProcess.GetProcessInfo().dwProcessId;
                }
            } while (!startShadow(hwnd_shadow, shadowProcessId));
        }
        else {
            StartProcess startedProcess(processInfo.location, processInfo.isNewWindow);
            WaitForSingleObject(startedProcess.GetProcessInfo().hProcess, processInfo.waitTime * MILLISECONDS_IN_SECONDS);
        }
    }

    BringWindowToTop(GetDesktopWindow());
    SetFocus(GetDesktopWindow());
    SetActiveWindow(GetDesktopWindow());
    SetForegroundWindow(GetDesktopWindow());

    if (desktop.getNumberOfActiveDesktops() > 0) {
        for (int i{ 0 }; i < desktop.getNumberOfActiveDesktops(); i++)
            desktop.switchToPreviousVirtualDesktop();
    }
}

bool startShadow(HWND hwnd_shadow, DWORD shadowProcessId) {
    if (EnumWindows(EnumWindowsProc, shadowProcessId))
        return false;

    SendKeyboardInput(1, VK_MENU);
    SendKeyboardInput(1, VK_TAB);
    Sleep(200);
    SendKeyboardInput(1, VK_MENU, KEYEVENTF_KEYUP);
    SendKeyboardInput(1, VK_TAB, KEYEVENTF_KEYUP);

    BringWindowToTop(hwnd_shadow);
    SetFocus(hwnd_shadow);
    SetActiveWindow(hwnd_shadow);
    SetForegroundWindow(hwnd_shadow);

    RECT rect = {};
    GetWindowRect(hwnd_shadow, &rect);

    //Coordinates of the Button Position Relative to the Shadow Window
    SetCursorPos(rect.right - 500, rect.bottom - 150);
    Sleep(200);
    SendMouseInput(1, MOUSEEVENTF_LEFTDOWN);
    SendMouseInput(1, MOUSEEVENTF_LEFTUP);
    
    HWND hwnd_shadow_desktop{ FindWindowA("Shadow - Window - Class", NULL) };
    if (hwnd_shadow_desktop) {
        ShowWindow(hwnd_shadow_desktop, SW_MAXIMIZE);
        Sleep(200);
        ShowWindow(hwnd_shadow_desktop, SW_NORMAL);
        return true;
    }
    else
        return false;
}