/**
 * Viewport.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Viewport.h"

using namespace EUMD_FlightSimulator::Core::Graphics;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

Viewport::Viewport(int x, int y, U32 width, U32 height, 
				   std::string tag, const Vec4& color, Scene_sptr pscene) :
				   m_x(x), m_y(y), m_width(width), m_height(height),
				   m_tag(tag), m_clearColor(color), mp_scene(pscene) { initialize(); }

Viewport::Viewport(int x, int y, U32 width, U32 height) :
	m_x(x), m_y(y), m_width(width), m_height(height), 
	mp_scene(NULL), m_clearColor(Vec4(.0f, .0f, .0f, 1.0f)) { initialize(); }

Viewport::Viewport() { }

Viewport::~Viewport() {
	clean();
#if _DEBUG
	DST_NOTIFY;
#endif
}

/* Functions */

void Viewport::initialize() {
	mb_active = mb_visible = true;
	mb_border = false;

	// Default 1px white border, in case it gets set
	m_borderColor = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_borderThickness = 1.0f;

	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);
}

void Viewport::resize(const int& w, const int& h) {
	if (m_y != 0)
		m_y = h;

	m_width = w;
	m_height = h;
}

void Viewport::update() {
	if (mp_scene && mb_active)
		mp_scene->update();
}

void Viewport::render() {
	if (mb_visible) {
		
		glScissor(m_x, m_y, m_width, m_height);

		glClearDepth(1.0);
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, ((GLfloat)m_width / (GLfloat)m_height), .1, 500.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		mp_scene->render();
	}
}

void Viewport::clean() { return; }

#pragma endregion

// END OF FILE