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

#include <algorithm>
#include <memory>
#include <vector>
#include <Windows.h>
#include "IApplicationObject.h"
#include "Viewport.h"

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Core {

		#define VP_BGN 0x01

		/* Viewport Arrangement Presets */

		enum {
			VP_SINGLE			= VP_BGN,
			VP_SPLITSCREEN_2H	= VP_BGN << 1,
			VP_SPLITSCREEN_2V	= VP_BGN << 2,
			VP_SPLITSCREEN_3	= VP_BGN << 3,
			VP_SPLITSCREEN_4	= VP_BGN << 4,
			VP_CUSTOM_LAYOUT	= VP_BGN << 5,
			VP_FITCANVAS		= VP_BGN << 6,
			VP_BORDER			= VP_BGN << 7
		};

		using namespace Graphics;

		class Canvas;

		typedef std::tr1::shared_ptr<Canvas> Canvas_sptr;
		typedef std::vector<Viewport_sptr> PViewports;

		class Canvas final : public IApplicationObject {

		public:

			/* Ctor, Dtor */

			Canvas(const HINSTANCE& hInstance, const int width, const int height,
				U16 layoutFlags, Viewport_sptr pviewport);
			Canvas(const HINSTANCE& hInstance, const int width, const int height,
				U16 layoutFlags, PViewports viewports);
			Canvas(const HINSTANCE& hInstance, const int width, const int height);
			Canvas();
			~Canvas();

			/* Accessors */

			inline const U16&				getLayoutFlag() const { return m_layoutFlag; }
			inline const bool&				hasViewports() const { return !mv_pViewports.empty(); }

			/* Modifiers */

			inline void						setLayoutFlag(const U16& flag) { m_layoutFlag = flag; }

			/* Functions */

			void							addViewport(Viewport_sptr pviewport);
			bool							removeViewport(const std::string& tag);
			bool							removeViewportAt(const int& index);
			void							resize(int w, int h);
			void							render();

			/* Implementations */

			inline const std::string		getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { return "Canvas"; }
			void							clean();

		private:

			/* Members */

			HDC								m_hDevCtx;
			HGLRC							m_hglCtx;
			HWND							m_hwnd;
			int								m_width,
											m_height;
			PViewports						mv_pViewports;
			U16								m_layoutFlag;

			/* Functions */

			void							initialize(const HINSTANCE& hInstance);
			void							setupPresetLayout();
			HGLRC							createglContext();
		};
	}
}

#pragma endregion

#endif /* !__CANVAS_H__ */

// END OF FILE