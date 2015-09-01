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

Viewport::Viewport(int x,  int y, U32 width, U32 height,
				   std::string tag, Camera_sptr pcamera) :
				   m_x(x), m_y(y), m_width(width), m_height(height),
				   m_tag(tag), mp_viewCam(pcamera) { initialize(); }

Viewport::Viewport(int x, int y, U32 width, U32 height,
				   std::string tag, Camera_sptr pcamera, Scene_sptr pscene) :
				   m_x(x), m_y(y), m_width(width), m_height(height),
				   m_tag(tag), mp_viewCam(pcamera), mp_scene(pscene) { initialize(); }

Viewport::Viewport(int x, int y, U32 width, U32 height, 
				   std::string tag, const Vec4& color, Scene_sptr pscene) :
				   m_x(x), m_y(y), m_width(width), m_height(height),
				   m_tag(tag), m_clearColor(color), mp_scene(pscene) { initialize(); }

Viewport::Viewport(int x, int y, U32 width, U32 height) :
	m_x(x), m_y(y), m_width(width), m_height(height) { initialize(); }

Viewport::Viewport() { ; }

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
}

void Viewport::resize(const int& w, const int& h) {
}

void Viewport::update() {
	if (mp_scene && mb_active)
		mp_scene->update();
}

void Viewport::render() {
	if (mb_visible) {

		glViewport(m_x, m_y, m_width, m_height);

		if (mp_viewCam)
			glLoadMatrixf(glm::value_ptr(mp_viewCam->getViewMatrix()));

		if (mp_scene)
			mp_scene->render();

	}
}

void Viewport::clean() { return; }

#pragma endregion

// END OF FILE