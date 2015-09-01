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

void Scene::initializeGrid() {
	NoobVertex* verts = new NoobVertex[200];
	float max = getComponent<Camera>("Default_Camera")->getMaxDepth();
	float min = -max;
	min += (max * .25f);
	max -= (max * .25f);
	float f = min, inc = 3.0f;

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
	glDrawArrays(GL_LINES, 0, 400);
	glBindVertexArray(0);
}

#pragma endregion

// END OF FILE