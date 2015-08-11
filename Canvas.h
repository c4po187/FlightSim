/**
 * Canvas.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__

#pragma once

#pragma region Prerequisites

#include "IApplicationObject.h"
#include <memory>
#include <Windows.h>
#include <gl\GL.h>

///// Tests /////

#include "Scene.h"
using namespace EUMD_FlightSimulator::Resources;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Core {

		class Canvas;

		typedef std::tr1::shared_ptr<Canvas> Canvas_sptr;

		class Canvas : public IApplicationObject {

		public:

			/* Ctor, Dtor */

			Canvas(const HINSTANCE& hInstance, const int& width, const int& height);
			Canvas();
			~Canvas();

			/* Functions */

			void						resize(int w, int h);
			void						render();

			/* Implementations */

			inline const std::string	getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { return "Canvas"; }

		private:

			/* Members */

			HDC							m_hDevCtx;
			HGLRC						m_hglCtx;
			HWND						m_hwnd;
			int							m_width,
										m_height;

			///// Tests /////

			Scene_sptr					mp_scene;

			/* Functions */

			void						init(const HINSTANCE& hInstance);
			HGLRC						createglContext();
		};
	}
}

#pragma endregion

#endif /* !__CANVAS_H__ */

// END OF FILE