#pragma once
class VirtualDesktop
{
private:
	int numberOfActiveDesktops{0};
public: 
	void closeVirtualDesktop();
	void createVirtualDesktop();
	void switchToPreviousVirtualDesktop();
	void switchToNextVirtualDesktop();

	int getNumberOfActiveDesktops();
};

