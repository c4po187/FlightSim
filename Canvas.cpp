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
	U16 layoutFlags, Viewport_sptr pviewport, bool useSceneManager) :
	m_width(width), m_height(height), m_layoutFlag(layoutFlags) {
	if (pviewport)
		addViewport(pviewport);
	if (useSceneManager)
		mp_sceneManager = SceneManager_sptr(new SceneManager());
	initialize(hInstance);
}

Canvas::Canvas(const HINSTANCE& hInstance, const int width, const int height,
	U16 layoutFlags, PViewports viewports, bool useSceneManager) :
	m_width(width), m_height(height), m_layoutFlag(layoutFlags), mv_pViewports(viewports) {
	if (useSceneManager)
		mp_sceneManager = SceneManager_sptr(new SceneManager());
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
	// Create default camera
	mp_mainCamera = Camera_sptr(new Camera(
		Vec3(), Vec3(.0f, 1.0f, .0f), Vec3(.0f, .0f, -1.0f),
		45.0f, static_cast<float>(m_width / m_height), .1f, 100.0f, "MainCamera"));
	
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
	
	GLenum glewerr = glewInit();
	if (glewerr != GLEW_OK) {
		std::cout << "Glew failed to initialize: " << glewGetErrorString(glewerr) << '\n' << std::endl;
		throw EX_INIT_FAIL;
	}
	else {
		std::cout << "Glew initialized successfully.\n\n";
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n' <<
			"OpenGL Vendor: " << glGetString(GL_VENDOR) << '\n' <<
			"OpenGL Renderer: " << glGetString(GL_RENDERER) << '\n' << std::endl;
	}

	setupPresetLayout();
	ShowWindow(m_hwnd, SW_NORMAL);

	glClearColor(.0f, .0f, .0f, 1.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	///// TESTING ////////////////////////////////////////////////////////////////////////////////////////////////
	mp_testVert = Shader::createShaderFromSource("noob.vert", SHADER_TYPE::VERT, "Noob_Vertex_Shader");
	mp_testFrag = Shader::createShaderFromSource("noob.frag", SHADER_TYPE::FRAG, "Noob_Fragment_Shader");
	mp_defaultVert = Shader::createShaderFromSource("default.vert", SHADER_TYPE::VERT, "Default_Vertex_Shader");
	mp_defaultFrag = Shader::createShaderFromSource("diffuse.frag", SHADER_TYPE::FRAG, "Diffuse_Fragment_Shader");
	mp_texDefaultFrag = Shader::createShaderFromSource(
		"texture_diffuse.frag", SHADER_TYPE::FRAG, "Texture_Diffuse_Fragment_Shader");
	mp_specFrag = Shader::createShaderFromSource("specular.frag", SHADER_TYPE::FRAG, "Specular_Fragment_Shader");
	mp_texSpecFrag = Shader::createShaderFromSource(
		"texture_specular.frag", SHADER_TYPE::FRAG, "Texture_Specular_Fragment_Shader");
	mp_scVert = Shader::createShaderFromSource(
		"simple_color.vert", SHADER_TYPE::VERT, "Simple_Color_Vertex_Shader");
	mp_scFrag = Shader::createShaderFromSource(
		"simple_color.frag", SHADER_TYPE::FRAG, "Simple_Color_Fragment_Shader");
	mp_skyVert = Shader::createShaderFromSource("skybox.vert", SHADER_TYPE::VERT, "Skybox_Vertex_Shader");
	mp_skyFrag = Shader::createShaderFromSource("skybox.frag", SHADER_TYPE::FRAG, "Skybox_Fragment_Shader");

	mp_shaderProg = ShaderProgram_sptr(new ShaderProgram("Noob_Test_Program"));
	mp_shaderProg->attachShader(mp_testVert);
	mp_shaderProg->attachShader(mp_testFrag);
	mp_shaderProg->link();
	mp_diffuseProg = ShaderProgram_sptr(new ShaderProgram("Diffuse_Program"));
	mp_diffuseProg->attachShader(mp_defaultVert);
	mp_diffuseProg->attachShader(mp_defaultFrag);
	mp_diffuseProg->link();
	mp_texDiffuseProg = ShaderProgram_sptr(new ShaderProgram("Texture_Diffuse_Program"));
	mp_texDiffuseProg->attachShader(mp_defaultVert);
	mp_texDiffuseProg->attachShader(mp_texDefaultFrag);
	mp_texDiffuseProg->link();
	mp_specProg = ShaderProgram_sptr(new ShaderProgram("Specular_Program"));
	mp_specProg->attachShader(mp_defaultVert);
	mp_specProg->attachShader(mp_specFrag);
	mp_specProg->link();
	mp_texSpecProg = ShaderProgram_sptr(new ShaderProgram("Texture_Specular_Program"));
	mp_texSpecProg->attachShader(mp_defaultVert);
	mp_texSpecProg->attachShader(mp_texSpecFrag);
	mp_texSpecProg->link();
	mp_scProg = ShaderProgram_sptr(new ShaderProgram("Simple_Color_Program"));
	mp_scProg->attachShader(mp_scVert);
	mp_scProg->attachShader(mp_scFrag);
	mp_scProg->link();
	mp_skyProg = ShaderProgram_sptr(new ShaderProgram("Skybox_Program"));
	mp_skyProg->attachShader(mp_skyVert);
	mp_skyProg->attachShader(mp_skyFrag);
	mp_skyProg->link();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Active scene shared amongst all viewports (if we have a scenemanager)
	if (mp_sceneManager)
		sceneShare();

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

bool Canvas::attachSceneToViewport(Scene_sptr pscene, const int& index) {
	if (!pscene || index < 0 || index >= mv_pViewports.size()) 
		return false;

	mb_shareScene = false;
	mv_pViewports[index]->setScene(pscene);

	return true;
}

bool Canvas::attachSceneToViewport(Scene_sptr pscene, const std::string& vtag) {
	if (!pscene) return false;

	Viewport_sptr pv = findViewport(vtag);
	if (!pv) return false;

	mb_shareScene = false;
	pv->setScene(pscene);

	return true;
}

bool Canvas::attachSceneToViewport(const std::string& stag, const std::string& vtag) {
	if (mp_sceneManager) {
		Scene_sptr ps = mp_sceneManager->findScene(stag);
		if (ps) {
			Viewport_sptr pv = findViewport(vtag);
			if (pv) {
				mb_shareScene = false;
				pv->setScene(ps);

				return true;
			}
		}
	}

	return false;
}

void Canvas::sceneShare() {
	mb_shareScene = true;
	if (hasViewports() && mp_sceneManager) {
		for (auto v : mv_pViewports)
			v->setScene(mp_sceneManager->getCurrentScene());
	}
}

bool Canvas::attachMainCameraToViewports() {
	if (!mp_mainCamera || !hasViewports()) return false;

	for (auto v : mv_pViewports)
		v->setViewCamera(mp_mainCamera);

	return true;
}

bool Canvas::attachMainCameraToViewport(const int& index) {
	if (mp_mainCamera && hasViewports()) {
		if (index < 0 || index >= mv_pViewports.size())
			return false;
		
		mv_pViewports[index]->setViewCamera(mp_mainCamera);

		return true;
	}

	return false;
}

bool Canvas::attachMainCameraToViewport(const std::string& tag) {
	if (mp_mainCamera && hasViewports()) {
		Viewport_sptr pv = findViewport(tag);
		if (!pv) return false;

		pv->setViewCamera(mp_mainCamera);

		return true;
	}

	return false;
}

bool Canvas::attachCameraToViewport(Camera_sptr pcamera, const int& index) {
	if (hasViewports() && index >= 0 && index < mv_pViewports.size()) {
		mv_pViewports[index]->setViewCamera(pcamera);

		return true;
	}

	return false;
}

bool Canvas::attachCameraToViewport(Camera_sptr pcamera, const std::string& tag) {
	if (hasViewports()) {
		Viewport_sptr pv = findViewport(tag);
		if (!pv) return false;

		pv->setViewCamera(pcamera);

		return true;
	}

	return false;
}

void Canvas::addViewport(Viewport_sptr pviewport) {
	mv_pViewports.push_back(pviewport);
}

bool Canvas::removeViewport(const std::string& tag) {
	static std::string _tag = tag;

	PViewports::iterator vit = std::find_if(
		mv_pViewports.begin(), mv_pViewports.end(),
		[](Viewport_sptr v)-> bool { return v->getTag() == _tag; });

	if (vit != mv_pViewports.end()) {
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

Viewport_sptr Canvas::findViewport(const std::string& tag) {
	static std::string _tag = tag;

	PViewports::iterator vit = std::find_if(
		mv_pViewports.begin(), mv_pViewports.end(),
		[](Viewport_sptr v)-> bool { return v->getTag() == _tag; });


	return (vit != mv_pViewports.end()) ? (*vit) : nullptr;
}

void Canvas::resize(int w, int h) {
	// Get 1% of the current width and height before we resize
	double percWidth = (static_cast<double>(m_width) / 100.0);
	double percHeight = (static_cast<double>(m_height) / 100.0);

	// Store the new width & height
	m_width = w;
	m_height = h;

	float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
	mp_mainCamera->setAspectRatio(aspect);
	mp_mainCamera->updateProjectionMatrix();

	// Resize base viewport
	glViewport(0, 0, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));

	// Set the perspective matrix accordingly
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(mp_mainCamera->getProjectionMatrix()));

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

void Canvas::update() {
	if (mp_sceneManager)
		mp_sceneManager->update();

	if (hasViewports()) {
		for (auto v : mv_pViewports)
			v->update();
	}
}

void Canvas::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (hasViewports()) {
		for (auto v : mv_pViewports) 
			v->render();
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

			if (mp_mainCamera) {
				for (auto v : mv_pViewports)
					v->setViewCamera(mp_mainCamera);
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