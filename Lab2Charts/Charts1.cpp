#include "Charts1.h"

#include <Windows.h>
using namespace Lab2Charts;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Charts);
	return 0;
}