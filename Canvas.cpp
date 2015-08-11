/**
 * Canvas.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Canvas.h"

using namespace EUMD_FlightSimulator::Core;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

Canvas::Canvas(const HINSTANCE& hInstance, 
			   const int& width, 
			   const int& height) :
					m_width(width),
					m_height(height) { init(hInstance); }

Canvas::Canvas() { ; }

Canvas::~Canvas() { ; }

/* Functions */

void Canvas::init(const HINSTANCE& hInstance) {
	///// Tests /////
	mp_scene = Scene_sptr(new Scene("Intro"));
	/////////////////

	m_hwnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, 
		"Flight Simulator", 
		"Flight Simulator", 
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		0, 
		0, 
		m_width, 
		m_height, 
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	m_hDevCtx = GetDC(m_hwnd);
	m_hglCtx = createglContext();

	glClearColor(.0f, .0f, .0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	ShowWindow(m_hwnd, SW_SHOW);
}

HGLRC Canvas::createglContext() {
	HGLRC hglrc;
	UINT pixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if (!(pixelFormat = ChoosePixelFormat(m_hDevCtx, &pfd))) return 0;
	if (!SetPixelFormat(m_hDevCtx, pixelFormat, &pfd)) return 0;
	if (!(hglrc = wglCreateContext(m_hDevCtx))) return 0;
	if (!wglMakeCurrent(m_hDevCtx, hglrc)) return 0;

	return hglrc;
}

void Canvas::resize(int w, int h) {
	glViewport(0, 0, w, h);
}

void Canvas::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	///// Tests /////
	std::cout << mp_scene->getType() << std::endl;
	std::cout << mp_scene->getType(EXTENDED_TYPE_INFO) << std::endl;
	/////////////////

	SwapBuffers(m_hDevCtx);
}

#pragma endregion

// END OF FILE