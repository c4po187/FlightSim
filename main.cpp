/**
 * Flight Simulator (main)
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <cstdio>
#include "Application.h"

#pragma endregion

#pragma region Libs

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "user32.lib")

#pragma endregion

#ifndef __cplusplus
#error No C++ compiler found!
#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS		// Stop the compiler bitching about 'Old Skool' C functions

#pragma region Entry Point

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdStr, int nCmd) {
	int exitCode = 0;

#if _DEBUG

	// Allocates a console, for debugging info
	AllocConsole();
	int fileDescriptor = _open_osfhandle(
		reinterpret_cast<long>(GetStdHandle(STD_OUTPUT_HANDLE)), _O_TEXT);
	FILE* pOStream = _fdopen(fileDescriptor, "w");
	setvbuf(pOStream, NULL, _IONBF, 1);
	*stdout = *pOStream;

	printf("Application is in debugging mode...\n\n");

#endif

	EUMD_FlightSimulator::Core::Application_sptr app = 
		EUMD_FlightSimulator::Core::Application::createApplication(hInstance, 1280, 720);
	app->run();

	// Exit
	ExitProcess(0);
	return exitCode;
}

#pragma endregion

#endif /* !_MSC_VER */

// END OF FILE