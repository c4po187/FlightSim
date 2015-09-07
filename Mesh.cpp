/**
 * Mesh.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Mesh.h"

using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

Mesh::Mesh(const std::string& obj_filename, const std::string& tag, bool calculateNormals) : mb_hasShader(false) {
	m_tag = tag;
	mb_hasOBJ = OBJLoader::loadOBJtoMesh(obj_filename, mv_vertices, calculateNormals);
	addComponent(ModelTransform_sptr(new ModelTransform(Vec3(.0f), "Default_Transform")));
}

Mesh::Mesh(const std::string& tag) : mb_hasOBJ(false), mb_hasShader(false) { m_tag = tag; }

Mesh::Mesh() : mb_hasOBJ(false), mb_hasShader(false) { ; }

Mesh::~Mesh() {
	this->clean();
}

/* Functions */

void Mesh::addVertex(const Vertex& vertex) {
	mv_vertices.push_back(vertex);
}

bool Mesh::removeVertexAt(const int& index) {
	if (index < 0 || index >= mv_vertices.size() || mv_vertices.empty())
		return false;

	size_t pre = mv_vertices.size();
	mv_vertices.erase(mv_vertices.begin() + index);

	return (pre < mv_vertices.size());
}

bool Mesh::clearVertices() {
	if (!mv_vertices.empty())
		mv_vertices.clear();

	return mv_vertices.empty();
}

bool Mesh::loadOBJtoMesh(const std::string& obj_filename, bool calculateNormals) {
	// Clear the vertices first if full
	clearVertices();

	mb_hasOBJ = OBJLoader::loadOBJtoMesh(obj_filename, mv_vertices, calculateNormals);
	
	return mb_hasOBJ;
}

void Mesh::attachShaderProgram(ShaderProgram_sptr pshaderProgram) {
	addComponent(pshaderProgram);
	mb_hasShader = true;
}

/**
 * If this mesh is a component (rather than a solitary
 * object), the best approach is to attach the parent's
 * (usually an Entity) Transform.
 */
void Mesh::attachTransform(Transform_sptr ptransform) {
	addComponent(ptransform);
}

/**
 * This function must be called before you can render!
 * Prior to calling this function you should have 
 * attached a shader program, linked & activated it.
 */
void Mesh::finalize() {
	if (!mv_vertices.empty()) {
		// Generate & bind vertex array object
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		
		// Generate, bind & load the mesh data to the vertex buffer object
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, mv_vertices.size() * sizeof(Vertex), &mv_vertices[0], GL_STATIC_DRAW);

		/* Set up all references to the vertex attributes */
		
		// Vertex positions
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, position)));
		glEnableVertexAttribArray(0);

		// Vertex normals
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, normal)));
		glEnableVertexAttribArray(1);

		// Vertex tangent
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, tangent)));
		glEnableVertexAttribArray(2);

		// Vertex colour
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, color)));
		glEnableVertexAttribArray(3);

		// Vertex texture co-ordinates
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, uv)));
		glEnableVertexAttribArray(4);

		// Unbind
		glBindVertexArray(0);

		rotz = .0f;
	}
}

void Mesh::render(Camera_sptr pcamera) {
	if (mb_hasShader) {
		rotz += .005f;

		getComponent<ShaderProgram>()->activate();

		Matrix4 model = Matrix4(1.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(getComponent<ModelTransform>()->getModelMatrix()));

		Matrix4 modelview = pcamera->getViewMatrix() * getComponent<ModelTransform>()->getModelMatrix();
		Matrix4 mvp = 
			pcamera->getProjectionMatrix() * 
			pcamera->getViewMatrix() * getComponent<ModelTransform>()->getModelMatrix();

		ShaderProgram_sptr pshp = getComponent<ShaderProgram>();
		pshp->sendUniform(
			pshp->getUniformLocation("model_matrix"), 1, false, getComponent<ModelTransform>()->getModelMatrix());
		pshp->sendUniform(pshp->getUniformLocation("view_matrix"), 1, false, pcamera->getViewMatrix());
		pshp->sendUniform(pshp->getUniformLocation("projection_matrix"), 1, false, pcamera->getProjectionMatrix());
		pshp->sendUniform(pshp->getUniformLocation("modelview_matrix"), 1, false, modelview);
		pshp->sendUniform(pshp->getUniformLocation("mvp_matrix"), 1, false, mvp);

		// Perform the render
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glDrawArrays(GL_TRIANGLES, 0, mv_vertices.size());
		glBindVertexArray(0);

		getComponent<ShaderProgram>()->deactivate();
	}
}

void Mesh::clean() {
	clearVertices();
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	Component::clean();
}

#pragma endregion

// END OF FILE