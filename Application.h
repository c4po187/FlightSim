/**
 * Application.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#pragma once

#pragma region Prerequisites

#include "IApplicationObject.h"
#include <memory>
#include <Windows.h>
#include "Canvas.h"

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Core {

		class Application;

		typedef std::tr1::shared_ptr<Application> Application_sptr;

		class Application final : public IApplicationObject {

		public:

			/* Ctor, Dtor */

			Application();
			virtual ~Application();

			/* Accessors */

			inline static Application_sptr		getApplication() { return sp_app; }
			inline Canvas_sptr					getCanvas() { return mp_canvas; }
			inline const bool&					isRegistered() const { return mb_registered; }
			inline LPSTICKYKEYS					getStickyKeys_ptr() { return &m_stickyKeys; }

			/* Functions */

			static Application_sptr				createApplication(const HINSTANCE& hInstance,
				const int w, const int h);
			int									run();
			void								kill();
			static void							clean();

			/* Implementations */

			inline const std::string			getType() { return "Application"; }

			/* Callbacks */

			static LRESULT CALLBACK				wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		private:

			/* Members */

			static Application_sptr				sp_app;
			Canvas_sptr							mp_canvas;
			bool								mb_registered,
												mb_kill;
			STICKYKEYS							m_stickyKeys;

			/* Functions */

			bool								registerWindowClass(const HINSTANCE& hInstance);
		};
	}
}

#pragma endregion

#endif /* !__APPLICATION_H__ */

// END OF FILE