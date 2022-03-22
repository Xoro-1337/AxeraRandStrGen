#include "../Extra_Headers/Global_Includes.h"
#include "../App_UI/UI.h"

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Overlay::Loop, nullptr, 0, nullptr);
	while (true)
	{
		Sleep(10);
	}
}