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

Canvas::Canvas(const HINSTANCE& hInstance, const int width, const int height,
	U16 layoutFlags, Viewport_sptr pviewport) :
	m_width(width), m_height(height), m_layoutFlag(layoutFlags) {
	if (pviewport)
		addViewport(pviewport);
	initialize(hInstance);
}

Canvas::Canvas(const HINSTANCE& hInstance, const int width, const int height,
	U16 layoutFlags, PViewports viewports) :
	m_width(width), m_height(height), m_layoutFlag(layoutFlags), mv_pViewports(viewports) {
	initialize(hInstance);
}

Canvas::Canvas(const HINSTANCE& hInstance, const int width, const int height) :
	m_width(width), m_height(height) { 
	m_layoutFlag = (VP_SINGLE | VP_FITCANVAS);
	initialize(hInstance); 
}

Canvas::Canvas() { ; }

Canvas::~Canvas() {
	clean();
#if _DEBUG
	DST_NOTIFY;
#endif
}

/* Functions */

void Canvas::initialize(const HINSTANCE& hInstance) {
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

	setupPresetLayout();

	ShowWindow(m_hwnd, SW_NORMAL);

	glClearColor(.0f, .0f, .0f, 1.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	resize(m_width, m_height);
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

void Canvas::addViewport(Viewport_sptr pviewport) {
	mv_pViewports.push_back(pviewport);
}

bool Canvas::removeViewport(const std::string& tag) {
	static std::string _tag = tag;

	PViewports::iterator vit = std::find_if(
		mv_pViewports.begin(), mv_pViewports.end(),
		[](Viewport_sptr v)-> bool { return v->getTag() == _tag; });

	if (*vit) {
		int index = std::distance(mv_pViewports.begin(), vit);

		return removeViewportAt(index);
	}

	return false;
}

bool Canvas::removeViewportAt(const int& index) {
	if (index < 0 || index >= mv_pViewports.size())
		throw EX_IOR;

	size_t pre = mv_pViewports.size();
	mv_pViewports.erase(mv_pViewports.begin() + index);

	return (mv_pViewports.size() < pre);
}

void Canvas::resize(int w, int h) {
	// Get 1% of the current width and height before we resize
	double percWidth = (static_cast<double>(m_width) / 100.0);
	double percHeight = (static_cast<double>(m_height) / 100.0);

	// Store the new width & height
	m_width = w;
	m_height = h;

	GLdouble aspect = static_cast<GLdouble>(m_width) / static_cast<GLdouble>(m_height);

	// Resize base viewport
	glViewport(0, 0, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));

	// Set the perspective matrix accordingly
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, .1, 500.0);

	/**
	 * Create width & height scalars that reflect the percentage change
	 * that occured during the resize.
	 * These scalars will be used to adjust the dimensions of all the
	 * sub-viewports.
	 */
	double widthScalar = ((static_cast<double>(m_width) / percWidth) / 100.0);
	double heightScalar = ((static_cast<double>(m_height) / percHeight) / 100.0);

	// Adjust all viewports
	if (hasViewports()) {
		for (auto v : mv_pViewports) {
			
			// Set the dimensions
			v->setWidth(round32((static_cast<double>(v->getWidth()) * widthScalar)));
			v->setHeight(round32((static_cast<double>(v->getHeight()) * heightScalar)));

			// Set the X & Y positions if fit to canvas flag is on
			if (m_layoutFlag & VP_FITCANVAS) {
				if (v->getX() != 0) 
					v->setX(v->getWidth());
				if (v->getY() != 0)
					v->setY(v->getHeight());
			}
		}
	}
}

void Canvas::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (hasViewports()) {
		for (auto v : mv_pViewports) {
			v->update();
			v->render();
		}
	}

	SwapBuffers(m_hDevCtx);
}

void Canvas::setupPresetLayout() {
	// First check if the flag is zero
	if (m_layoutFlag == 0) {
		// No flags are set, so check if there is are viewports available
		if (!hasViewports()) {
			/**
			 * No viewports...
			 * Let's set the presets and create a single viewport.
			 */
			m_layoutFlag = (VP_SINGLE | VP_FITCANVAS);
			addViewport(Viewport_sptr(new Viewport(0, 0, m_width, m_height)));

			return;
		}

		else {
			m_layoutFlag = VP_CUSTOM_LAYOUT;

			if (mv_pViewports.size() == 1)
				m_layoutFlag |= VP_SINGLE;

			return;
		}

	} else {
		// Flag is set to a value, again check if we've any viewports
		if (!hasViewports()) {
			// As no viewports have been provided, we will make all presets fit canvas
			if (!(m_layoutFlag & VP_FITCANVAS))
				m_layoutFlag |= VP_FITCANVAS;

			/* Viewport layout settings */
			{
				int hw = (m_width / 2);
				int hh = (m_height / 2);

				// Singular
				if (m_layoutFlag & VP_SINGLE) 
					addViewport(Viewport_sptr(new Viewport(0, 0, m_width, m_height)));

				// Horizontal 2P Splitscreen
				else if (m_layoutFlag & VP_SPLITSCREEN_2H) {
					addViewport(Viewport_sptr(new Viewport(0, hh, m_width, hh)));
					addViewport(Viewport_sptr(new Viewport(0, 0, m_width, hh)));

					mv_pViewports[0]->setTag("Top");
					mv_pViewports[1]->setTag("Bottom");
				}

				// Vertical 2P Splitscreen
				else if (m_layoutFlag & VP_SPLITSCREEN_2V) {
					addViewport(Viewport_sptr(new Viewport(0, 0, hw, m_height)));
					addViewport(Viewport_sptr(new Viewport(hw, 0, hw, m_height)));

					mv_pViewports[0]->setTag("Left");
					mv_pViewports[1]->setTag("Right");
				}

				// 3P Splitscreen (Top heavy)
				else if (m_layoutFlag & VP_SPLITSCREEN_3H) {
					addViewport(Viewport_sptr(new Viewport(0, hh, m_width, hh)));
					addViewport(Viewport_sptr(new Viewport(0, 0, hw, hh)));
					addViewport(Viewport_sptr(new Viewport(hw, 0, hw, hh)));

					mv_pViewports[0]->setTag("Top");
					mv_pViewports[1]->setTag("BottomLeft");
					mv_pViewports[2]->setTag("BottomRight");
				}

				// 3P Splitscreen (Left side heavy)
				else if (m_layoutFlag & VP_SPLITSCREEN_3V) {
					addViewport(Viewport_sptr(new Viewport(0, 0, hw, m_height)));
					addViewport(Viewport_sptr(new Viewport(hw, hh, hw, hh)));
					addViewport(Viewport_sptr(new Viewport(hw, 0, hw, hh)));

					mv_pViewports[0]->setTag("Left");
					mv_pViewports[1]->setTag("TopRight");
					mv_pViewports[2]->setTag("BottomRight");
				}

				// 4P Splitscreen
				else if (m_layoutFlag & VP_SPLITSCREEN_4) {
					addViewport(Viewport_sptr(new Viewport(0, hh, hw, hh)));
					addViewport(Viewport_sptr(new Viewport(hw, hh, hw, hh)));
					addViewport(Viewport_sptr(new Viewport(0, 0, hw, hh)));
					addViewport(Viewport_sptr(new Viewport(hw, 0, hw, hh)));

					mv_pViewports[0]->setTag("TopLeft");
					mv_pViewports[1]->setTag("TopRight");
					mv_pViewports[2]->setTag("BottomLeft");
					mv_pViewports[3]->setTag("BottomRight");
				}

				else
					return;
			}

			// Set borders as specified
			if (hasViewports()) {
				if (m_layoutFlag & VP_BORDER) {
					for (auto v : mv_pViewports)
						v->setBorder(true);
				}
			}

			return;
		}
	}
}

void Canvas::clean() {
	if (hasViewports()) {
		for (auto v : mv_pViewports)
			v->clean();
		
		mv_pViewports.clear();
	}
	
	if (m_hglCtx) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hglCtx);
		m_hglCtx = NULL;
	}

	ReleaseDC(m_hwnd, m_hDevCtx);
}

#pragma endregion

// END OF FILE