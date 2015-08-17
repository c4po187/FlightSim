/**
 * Viewport.h
 *
 * Rici Underwood � 2015
 * c4po187@gmail.com
 */

#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#pragma once

#pragma region Prerequisites

#include <memory>
#include <Windows.h>
#include "Scene.h"
#include <gl\GL.h>
#include <gl\GLU.h>

using namespace EUMD_FlightSimulator;
using namespace EUMD_FlightSimulator::Resources;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Core {

		namespace Graphics {

			class Viewport;

			typedef std::tr1::shared_ptr<Viewport> Viewport_sptr;

			class Viewport : public IApplicationObject {

				public:

					/* Ctor, Dtor */

					Viewport(int x, int y, U32 width, U32 height, 
							 std::string tag, const Vec4& color, Scene_sptr pscene);
					Viewport(int x, int y, U32 width, U32 height);
					Viewport();
					~Viewport();

					/* Accessors */

					inline const int&				getX() const { return m_x; }
					inline const int&				getY() const { return m_y; }
					inline const U32&				getWidth() const { return m_width; }
					inline const U32&				getHeight() const { return m_height; }
					inline const std::string&		getTag() const { return m_tag; }
					inline Scene_sptr				getScene() { return mp_scene; }
					inline const Vec4&				getClearColor() const { return m_clearColor; }
					inline const Vec4&				getBorderColor() const { return m_borderColor; }
					inline const float&				getBorderThickness() const { return m_borderThickness; }
					inline const bool&				isActive() const { return mb_active; }
					inline const bool&				isVisible() const { return mb_visible; }
					inline const bool&				hasBorder() const { return mb_border; }

					/* Modifiers */

					inline void						setX(const int& x) { m_x = x; }
					inline void						setY(const int& y) { m_y = y; }
					inline void						setWidth(const U32& width) { m_width = width; }
					inline void						setHeight(const U32& height) { m_height = height; }
					inline void						setTag(const std::string& tag) { m_tag = tag; }
					inline void						setScene(Scene_sptr pscene) { mp_scene = pscene; }
					inline void						setClearColor(const Vec4& color) { m_clearColor = color; }
					inline void						setBorderColor(const Vec4& color) { m_borderColor = color; }
					inline void						setBorderThickness(const float& t) { m_borderThickness = t; }
					inline void						setActive(const bool& active) { mb_active = active; }
					inline void						setVisible(const bool& visible) { mb_visible = visible; }
					inline void						setBorder(const bool& border) { mb_border = border; }

					/* Implementations */

					inline const std::string		getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { 
						return "Viewport"; 
					}
					void							clean();

					/* Functions */

					void							resize(const int& w, const int& h);
					void							update();
					void							render();

				private:

					int								m_x,
													m_y;
					U32								m_width, 
													m_height;
					std::string						m_tag;
					Vec4							m_clearColor,
													m_borderColor;
					float							m_borderThickness;
					Scene_sptr						mp_scene;
					bool							mb_active,
													mb_visible,
													mb_border;

					///// Tests /////

					float							m_rotZ;

					/////////////////

					/* Functions */

					void							initialize();
			};
		}
	}
}

#pragma endregion

#endif /* !__VIEWPORT_H__ */

// END OF FILE