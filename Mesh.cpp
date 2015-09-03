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
	mb_hasOBJ = OBJLoader::loadOBJtoMesh(obj_filename, mv_pTriangles, calculateNormals);
}

Mesh::Mesh(const std::string& tag) : mb_hasOBJ(false), mb_hasShader(false) { m_tag = tag; }

Mesh::Mesh() : mb_hasOBJ(false), mb_hasShader(false) { ; }

Mesh::~Mesh() {
	this->clean();
}

/* Functions */

bool Mesh::loadOBJtoMesh(const std::string& obj_filename, bool calculateNormals) {
	mb_hasOBJ = OBJLoader::loadOBJtoMesh(obj_filename, mv_pTriangles, calculateNormals);
	
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

void Mesh::addTriangle(Triangle_sptr ptriangle) {
	if (ptriangle)
		mv_pTriangles.push_back(ptriangle);
}

bool Mesh::removeTriangleAt(const int& index) {
	if (index < 0 || index >= mv_pTriangles.size() || mv_pTriangles.empty())
		return false;
	
	size_t pre = mv_pTriangles.size();
	mv_pTriangles.erase(mv_pTriangles.begin() + index);

	return (mv_pTriangles.size() < pre);
}

/**
 * This function must be called before you can render!
 * Prior to calling this function you should have 
 * attached a shader program, linked & activated it.
 */
void Mesh::finalize() {
	if (!mv_pTriangles.empty()) {
		// Generate & bind vertex array object
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		
		// Generate, bind & load the mesh data to the vertex buffer object
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, 3 * mv_pTriangles.size() * sizeof(Vertex), 
			&(mv_pTriangles[0]->points[0]), GL_STATIC_DRAW);

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
	}
}

void Mesh::render() {
	if (mb_hasShader) {
		getComponent<ShaderProgram>()->activate();

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(getComponent<ModelTransform>()->getModelMatrix()));

		/**
		 * @TODO: 
		 *		MVP - Figure out how we will include the camera into this class.
		 *		Send uniforms (such as MVP) to shader.
		 */
		Matrix4 mvp;

		// Perform the render
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glDrawArrays(GL_TRIANGLES, 0, 3 * mv_pTriangles.size());
		glBindVertexArray(0);
	}
}

void Mesh::clean() {
	if (!mv_pTriangles.empty()) {
		for (auto t : mv_pTriangles)
			t = nullptr;
		mv_pTriangles.clear();
	}

	Component::clean();
}

#pragma endregion

// END OF FILE