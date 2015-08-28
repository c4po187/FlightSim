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

#include "EUMD_Math.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <Windows.h>
#include "IApplicationObject.h"
#include "Viewport.h"
#include "SceneManager.h"
#include "Camera.h"

///// OBJ TESTING /////
#include "OBJLoader.h"
#include "ShaderProgram.h"
///////////////////////

using namespace EUMD_FlightSimulator::Utilities;
using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Core {

		#define VP_BGN 0x01

		/* Viewport Arrangement Presets */

		enum {
			VP_SINGLE = VP_BGN,
			VP_SPLITSCREEN_2H = VP_BGN << 1,
			VP_SPLITSCREEN_2V = VP_BGN << 2,
			VP_SPLITSCREEN_3H = VP_BGN << 3,
			VP_SPLITSCREEN_3V = VP_BGN << 4,
			VP_SPLITSCREEN_4 = VP_BGN << 5,
			VP_CUSTOM_LAYOUT = VP_BGN << 6,
			VP_FITCANVAS = VP_BGN << 7,
			VP_BORDER = VP_BGN << 8
		};

		using namespace Graphics;

		class Canvas;

		typedef std::tr1::shared_ptr<Canvas> Canvas_sptr;
		typedef std::vector<Viewport_sptr> PViewports;

		class Canvas final : public IApplicationObject {

		public:

			/* Ctor, Dtor */

			Canvas(const HINSTANCE& hInstance, const int width, const int height,
				U16 layoutFlags, Viewport_sptr pviewport, bool useSceneManager);
			Canvas(const HINSTANCE& hInstance, const int width, const int height,
				U16 layoutFlags, PViewports viewports, bool useSceneManager);
			Canvas(const HINSTANCE& hInstance, const int width, const int height);
			Canvas();
			~Canvas();

			/* Accessors */

			inline const int& getWidth() const { return m_width; }
			inline const int& getHeight() const { return m_height; }
			inline const HDC& getDeviceContext() const { return m_hDevCtx; }
			inline const HGLRC& getGLContext() const { return m_hglCtx; }
			inline const HWND& getWindowHandle() const { return m_hwnd; }
			inline const U16& getLayoutFlag() const { return m_layoutFlag; }
			inline const PViewports& getViewports() const { return mv_pViewports; }
			inline const bool hasViewports() const { return !(mv_pViewports.empty()); }
			inline SceneManager_sptr getSceneManager() { return mp_sceneManager; }
			inline Camera_sptr getMainCamera() { return mp_mainCamera; }

			/* Modifiers */

			inline void setLayoutFlag(const U16& flag) { m_layoutFlag = flag; }
			inline void setViewports(const PViewports& viewports) { 
				mv_pViewports = viewports; 
			}
			inline void setSceneManager(SceneManager_sptr sm) { mp_sceneManager = sm; }
			inline void setMainCamera(Camera_sptr pcamera) { mp_mainCamera = pcamera; }

			/* Functions */

			void addViewport(Viewport_sptr pviewport);
			bool removeViewport(const std::string& tag);
			bool removeViewportAt(const int& index);
			Viewport_sptr findViewport(const std::string& tag);
			bool attachSceneToViewport(Scene_sptr pscene, const int& index);
			bool attachSceneToViewport(Scene_sptr pscene, const std::string& vtag);
			bool attachSceneToViewport(const std::string& stag, const std::string& vtag);
			void sceneShare();
			bool attachMainCameraToViewports();
			bool attachMainCameraToViewport(const int& index);
			bool attachMainCameraToViewport(const std::string& tag);
			bool attachCameraToViewport(Camera_sptr pcamera, const int& index);
			bool attachCameraToViewport(Camera_sptr pcamera, const std::string& tag);
			void resize(int w, int h);
			void update();
			void render();

			/* Implementations */

			inline const std::string getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { return "Canvas"; }
			void clean();

		private:

			/* Members */

			HDC m_hDevCtx;
			HGLRC m_hglCtx;
			HWND m_hwnd;
			int m_width, m_height;
			PViewports mv_pViewports;
			SceneManager_sptr mp_sceneManager;
			bool mb_shareScene;
			U16 m_layoutFlag;
			Camera_sptr mp_mainCamera;

			///// Tests /////
			ShaderProgram_sptr mp_shaderProg;
			Shader_sptr mp_testVert, mp_testFrag;
			/////////////////

			/* Functions */

			void initialize(const HINSTANCE& hInstance);
			void setupPresetLayout();
			HGLRC createglContext();
		};
	}
}

#pragma endregion

#endif /* !__CANVAS_H__ */

// END OF FILE