/**
 * Scene.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Resource.h"
#include "Scene.h"

using namespace EUMD_FlightSimulator::Resources;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

Scene::Scene(const std::string& tag, Camera_sptr pcamera, bool showGrid) : mb_showGrid(showGrid) {
	m_tag = tag;
	mb_active = true;
	addComponent(pcamera);
	initializeGrid();
	initTests();
	//initTests2();
}

Scene::Scene(const std::string& tag, bool active) {
	m_tag = tag;
	mb_active = active;
	mb_showGrid = false;
}

Scene::Scene() { 
	mb_active = mb_showGrid = false;
}

Scene::~Scene() { ; }

/* Functions */

void Scene::initTests() {
	// Setup light
	m_light = { Vec4(-2.0f, 5.0f, 5.0f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 5.0f };
	
	Shader_sptr vsh = Shader::createShaderFromSource(
		"default.vert", SHADER_TYPE::VERT, "Default_Vertex_Shader");
	Shader_sptr fsh = Shader::createShaderFromSource(
		"diffuse.frag", SHADER_TYPE::FRAG, "Diffuse, Fragment_Shader");
	ShaderProgram_sptr testProg = ShaderProgram_sptr(new ShaderProgram("Diffuse_Test_Shader"));
	testProg->attachShader(vsh);
	testProg->attachShader(fsh);
	if (testProg->link() && testProg->activate()) {
		testProg->sendUniform(testProg->getUniformLocation("light.position"), 1, m_light.position);
		testProg->sendUniform(testProg->getUniformLocation("light.color"), 1, m_light.color);
		testProg->sendUniform(testProg->getUniformLocation("light.intensity"), m_light.intensity);
		mp_testMesh = Mesh_sptr(new Mesh("house.obj", "Test_Mesh"));
		if (mp_testMesh->hasOBJ()) {
			mp_testMesh->attachShaderProgram(testProg);
			mp_testMesh->finalize();
		}
	}
}

void Scene::initTests2() {
	m_light = { Vec4(.0f, .5f, 0.1f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f };
	mp_mesh = Mesh_sptr(new Mesh("Test_Mesh2"));

	// Default unused attributes
	Vec4 col = Vec4(.0f, .8f, .2f, 1.0f);
	Vec2 uv = Vec2(1.0f, 1.0f);

	// Cube Vertices
	Vertex tlf = { Vec4(-.25f, .25f, .0f, 1.0f), Vec4(), Vec4(), col, uv };
	Vertex trf = { Vec4(.25f, .25f, .0f, 1.0f), Vec4(), Vec4(), col, uv };
	Vertex brf = { Vec4(.25f, -.25f, .0f, 1.0f), Vec4(), Vec4(), col, uv };
	Vertex blf = { Vec4(-.25f, -.25f, .0f, 1.0f), Vec4(), Vec4(), col, uv };
	Vertex tlb = { Vec4(-.25f, .25f, -.5f, 1.0f), Vec4(), Vec4(), col, uv };
	Vertex trb = { Vec4(.25f, .25f, -.5f, 1.0f), Vec4(), Vec4(), col, uv };
	Vertex brb = { Vec4(.25f, -.25f, -.5f, 1.0f), Vec4(), Vec4(), col, uv };
	Vertex blb = { Vec4(-.25f, -.25f, -.5f, 1.0f), Vec4(), Vec4(), col, uv };

	Vec4 v1 = tlf.position - blf.position;
	Vec4 v2 = brf.position - blf.position;
	Vec3 v1_3 = Vec3(v1.x, v1.y, v1.z);
	Vec3 v2_3 = Vec3(v2.x, v2.y, v2.z);
	Vec3 nf0 = glm::normalize(glm::cross(v1_3, v2_3));

	/* Add vertices in triangular fashion (some may be added twice) */

	// Front
	mp_mesh->addVertex(blf);
	mp_mesh->addVertex(brf);
	mp_mesh->addVertex(tlf);
	mp_mesh->addVertex(tlf);
	mp_mesh->addVertex(brf);
	mp_mesh->addVertex(trf);

	// Top
	mp_mesh->addVertex(trf);
	mp_mesh->addVertex(trb);
	mp_mesh->addVertex(tlb);
	mp_mesh->addVertex(tlb);
	mp_mesh->addVertex(tlf);
	mp_mesh->addVertex(trf);

	// Right
	mp_mesh->addVertex(trf);
	mp_mesh->addVertex(brf);
	mp_mesh->addVertex(trb);
	mp_mesh->addVertex(trb);
	mp_mesh->addVertex(brf);
	mp_mesh->addVertex(brb);

	// Back
	mp_mesh->addVertex(brb);
	mp_mesh->addVertex(blb);
	mp_mesh->addVertex(trb);
	mp_mesh->addVertex(trb);
	mp_mesh->addVertex(blb);
	mp_mesh->addVertex(tlb);

	// Left
	mp_mesh->addVertex(tlb);
	mp_mesh->addVertex(tlf);
	mp_mesh->addVertex(blb);
	mp_mesh->addVertex(blb);
	mp_mesh->addVertex(tlf);
	mp_mesh->addVertex(blf);

	// Bottom
	mp_mesh->addVertex(blf);
	mp_mesh->addVertex(brf);
	mp_mesh->addVertex(blb);
	mp_mesh->addVertex(blb);
	mp_mesh->addVertex(brf);
	mp_mesh->addVertex(brb);

	// Create shaders
	Shader_sptr vsh = Shader::createShaderFromSource("default.vert", SHADER_TYPE::VERT, "Default_vertex_Shader");
	Shader_sptr fsh = Shader::createShaderFromSource("diffuse.frag", SHADER_TYPE::FRAG, "Diffuse_Frag_Shader");

	// Create shader program and attach above shaders
	ShaderProgram_sptr prog = ShaderProgram_sptr(new ShaderProgram("Cube_Shader"));
	prog->attachShader(vsh);
	prog->attachShader(fsh);

	// Link program and send light uniforms
	if (prog->link() && prog->activate()) {
		prog->sendUniform(prog->getUniformLocation("light.position"), 1, m_light.position);
		prog->sendUniform(prog->getUniformLocation("light.color"), 1, m_light.color);
		prog->sendUniform(prog->getUniformLocation("light.intensity"), m_light.intensity);

		// Attach shader program to mesh
		mp_mesh->attachShaderProgram(prog);

		// Finalize the mesh
		mp_mesh->finalize();
	}
}

void Scene::initializeGrid() {
	NoobVertex* verts = new NoobVertex[200];
	float max = getComponent<Camera>("Default_Camera")->getMaxDepth();
	float min = -max;
	min += (max * .25f);
	max -= (max * .25f);
	float f = min, inc = 3.06125f;

	for (unsigned i = 0; i < 200; i += 4) {
		verts[i] = { Vec3(min, .0f, f), GRID_COLOR };
		verts[i + 1] = { Vec3(max, .0f, f), GRID_COLOR };
		verts[i + 2] = { Vec3(f, .0f, min), GRID_COLOR };
		verts[i + 3] = { Vec3(f, .0f, max), GRID_COLOR };
		f += inc;
	}

	// Set up shaders for the grid
	Shader_sptr vsh = Shader::createShaderFromSource(
		"simple_color.vert", SHADER_TYPE::VERT, "Grid_Vertex_Shader");
	Shader_sptr fsh = Shader::createShaderFromSource(
		"simple_color.frag", SHADER_TYPE::FRAG, "Grid_Fragment_Shader");

	// Set up program and attach shaders
	ShaderProgram_sptr prog = ShaderProgram_sptr(new ShaderProgram("Grid_Shader"));
	prog->attachShader(vsh);
	prog->attachShader(fsh);
	
	// If program linkage & activation passes, start sending neccesary data
	if (prog->link() && prog->activate()) {
		// Generate & bind vertex array object & vertex buffer objects
		glGenVertexArrays(1, &m_grid_vao);
		glBindVertexArray(m_grid_vao);
		glGenBuffers(1, &m_grid_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_grid_vbo);

		glBufferData(GL_ARRAY_BUFFER, 200 * sizeof(NoobVertex), verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(NoobVertex), 
			reinterpret_cast<void*>(offsetof(NoobVertex, position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(NoobVertex),
			reinterpret_cast<void*>(offsetof(NoobVertex, color)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		addComponent(prog);

		getComponent<Camera>("Default_Camera")->getTransform()->setPosition(
			getComponent<Camera>("Default_Camera")->getTransform()->getPosition() + Vec3(.0f, 2.0f, .0f));
		getComponent<Camera>("Default_Camera")->updateViewMatrix();
	}

	delete[] verts;
}

void Scene::update() { ; }

void Scene::render() {
	if (mb_showGrid)
		renderGrid();

	if (mp_testMesh)
		mp_testMesh->render(getComponent<Camera>("Default_Camera"));

	/*if (mp_mesh)
		mp_mesh->render(getComponent<Camera>("Default_Camera"));*/
}

void Scene::renderGrid() {
	getComponent<ShaderProgram>("Grid_Shader")->activate();
	
	Matrix4 model = Matrix4(1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(model));
	model = glm::translate(model, Vec3(.0f, .0f, -.5f));
	Matrix4 mvp = getComponent<Camera>("Default_Camera")->getProjectionMatrix() *
		getComponent<Camera>("Default_Camera")->getViewMatrix() * model;
	getComponent<ShaderProgram>("Grid_Shader")->sendUniform(
		getComponent<ShaderProgram>("Grid_Shader")->getUniformLocation("mvp_matrix"), 1, false, mvp);

	glBindVertexArray(m_grid_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_grid_vbo);
	glDrawArrays(GL_LINES, 0, 200);
	glBindVertexArray(0);

	getComponent<ShaderProgram>("Grid_Shader")->deactivate();
}

#pragma endregion

// END OF FILE