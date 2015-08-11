/**
 * Application.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Application.h"

using namespace EUMD_FlightSimulator::Core;

#pragma endregion

#pragma region Definitions

/* Globals */

Application_sptr Application::sp_app = NULL;

/* Ctor, Dtor */

Application::Application() {
	mp_rscFactory = ResourceFactory_sptr(new ResourceFactory());
	m_stickyKeys = { sizeof(STICKYKEYS), 0 };
	mb_kill = false;
}

Application::~Application() { ; }

/* Functions */

Application_sptr Application::createApplication(const HINSTANCE& hInstance, const int w, const int h) {
	if (!sp_app) {
		sp_app = Application_sptr(new Application());

		// Turn off sticky keys, while this app is running
		if ((sp_app->getStickyKeys_ptr()->dwFlags & SKF_STICKYKEYSON) == 0) {
			sp_app->getStickyKeys_ptr()->dwFlags &= ~SKF_HOTKEYACTIVE;
			sp_app->getStickyKeys_ptr()->dwFlags &= ~SKF_CONFIRMHOTKEY;
			SystemParametersInfo(
				SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), static_cast<LPVOID>(sp_app->getStickyKeys_ptr()), 0);
		}

		if (sp_app->mb_registered = sp_app->registerWindowClass(hInstance))
			sp_app->mp_canvas = Canvas_sptr(new Canvas(hInstance, w, h));
	}

	return sp_app;
}

bool Application::registerWindowClass(const HINSTANCE& hInstance) {
	WNDCLASSEX winClass;
	winClass.cbSize = sizeof(WNDCLASSEX);

	winClass.hInstance = hInstance;
	winClass.style = (CS_HREDRAW | CS_VREDRAW);
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hbrBackground = NULL;
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(0x6B));
	winClass.hIconSm = LoadIcon(winClass.hInstance, MAKEINTRESOURCE(0x6C));
	winClass.lpfnWndProc = this->wndProc;
	winClass.lpszClassName = "Flight Simulator";
	winClass.lpszMenuName = NULL;

	return RegisterClassEx(&winClass);
}

LRESULT CALLBACK Application::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
		case WM_SIZE:
			sp_app->getCanvas()->resize(LOWORD(lparam), HIWORD(lparam));
			break;
		case WM_DESTROY:
			sp_app->clean();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	
	return 0;
}

int Application::run() {
	MSG msg;

	while (!mb_kill) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				kill();
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		mp_canvas->render();
	}
	
	clean();

	return static_cast<int>(msg.wParam);
}

void Application::kill() {
	mb_kill = true;
}

void Application::clean() {
	sp_app->getStickyKeys_ptr()->dwFlags = (
		SKF_AVAILABLE | SKF_HOTKEYACTIVE | SKF_CONFIRMHOTKEY | SKF_AUDIBLEFEEDBACK);
	SystemParametersInfo(
		SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), static_cast<LPVOID>(sp_app->getStickyKeys_ptr()), 0);
}

#pragma endregion

// END OF FILE