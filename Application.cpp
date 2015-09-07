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
	//mp_rscFactory = ResourceFactory_sptr(new ResourceFactory());
	m_stickyKeys = { sizeof(STICKYKEYS), 0 };
	mb_kill = mb_ranOnce = false;
}

Application::~Application() { 
	clean();
#if _DEBUG
	DST_NOTIFY;
#endif
}

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

		if (sp_app->mb_registered = sp_app->registerWindowClass(hInstance)) {
			sp_app->mp_canvas = Canvas_sptr(
				new Canvas(hInstance, w, h, (VP_SPLITSCREEN_4 | VP_FITCANVAS | VP_BORDER), NULL, true));
		}
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

	if (RegisterClassEx(&winClass) == 0) {
		throw EX_GENERAL;
	}

	return true;
}

LRESULT CALLBACK Application::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
#if _DEBUG
#if MCT
	
	///// Camera Testing /////
	POINT mouse;
	float xoffset = .0f, yoffset = .0f;

	RECT view;
	if (sp_app->getCanvas()) {
		if (GetClientRect(hwnd, &view)) {
			sp_app->getCanvas()->setMidX(view.right / 2);
			sp_app->getCanvas()->setMidY(view.bottom / 2);
		}
	}
	//////////////////////////

#endif /* MCT */
#endif /* _DEBUG */
	
	switch (msg) {

#if _DEBUG
#if MCT	
		///// Camera Testing /////
		case WM_MOUSEMOVE:
			if (sp_app->getCanvas()) {
				GetCursorPos(&mouse);

				if (!sp_app->mb_ranOnce) {
					sp_app->getCanvas()->setMidX(mouse.x);
					sp_app->getCanvas()->setMidY(mouse.y);
					sp_app->mb_ranOnce = true;
				}

				xoffset = (mouse.x - sp_app->getCanvas()->getMidX()) * .0005f;
				yoffset = (mouse.y - sp_app->getCanvas()->getMidY()) * .0005f;

				sp_app->getCanvas()->getMainCamera()->getTransform()->setYaw(xoffset);
				sp_app->getCanvas()->getMainCamera()->getTransform()->setPitch(yoffset);
				sp_app->getCanvas()->getMainCamera()->orient();
				sp_app->getCanvas()->getMainCamera()->updateViewMatrix(true);
			}
			//sp_app->getCanvas()->setCursor(true);

			break;
		//////////////////////////
#endif /* MCT */

#if KCT
		case WM_KEYDOWN:
			switch (wparam) {
				case VK_ESCAPE:
					sp_app->clean();
					PostQuitMessage(0);
					break;

				///// Camera Testing /////
				case 'W':	// Cam Forward
					sp_app->getCanvas()->getMainCamera()->getTransform()->setPosition(
						sp_app->getCanvas()->getMainCamera()->getTransform()->getPosition() - Vec3(.0f, .0f, .5f));
					sp_app->getCanvas()->getMainCamera()->updateViewMatrix();
					break;
				case 'A':	// Cam Strafe Left
					sp_app->getCanvas()->getMainCamera()->getTransform()->setPosition(
						sp_app->getCanvas()->getMainCamera()->getTransform()->getPosition() - Vec3(.5f, .0f, .0f));
					sp_app->getCanvas()->getMainCamera()->updateViewMatrix();
					break;
				case 'S':	// Cam Backwards
					sp_app->getCanvas()->getMainCamera()->getTransform()->setPosition(
						sp_app->getCanvas()->getMainCamera()->getTransform()->getPosition() + Vec3(.0f, .0f, .5f));
					sp_app->getCanvas()->getMainCamera()->updateViewMatrix();
					break;
				case 'D':	// Cam Strafe Right
					sp_app->getCanvas()->getMainCamera()->getTransform()->setPosition(
						sp_app->getCanvas()->getMainCamera()->getTransform()->getPosition() + Vec3(.5f, .0f, .0f));
					sp_app->getCanvas()->getMainCamera()->updateViewMatrix();
					break;
				//////////////////////////

				default:
					break;
			}
			break;

#endif /* KCT */
#endif /* _DEBUG */

		case WM_PAINT:
			sp_app->getCanvas()->update();
			sp_app->getCanvas()->render();
			break;
		case WM_ERASEBKGND:
			return 0;
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
	}

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