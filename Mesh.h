/**
 * Mesh.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __MESH_H__
#define __MESH_H__

#pragma once

#pragma region Prerequisites

#include "Component.h"
#include "OBJLoader.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"

using namespace EUMD_FlightSimulator::Utilities;
using namespace EUMD_FlightSimulator::Core::Graphics;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Components {

		class Mesh;

		typedef std::tr1::shared_ptr<Mesh> Mesh_sptr;
		
		class Mesh : public Component {

			public:

				/* Ctor, Dtor*/

				Mesh(const std::string& obj_filename, const std::string& tag, bool calculateNormals = false);
				Mesh(const std::string& tag);
				Mesh();
				~Mesh();

				/* Accessors */

				inline const Vertices& getVertices() const { return mv_vertices; }
				inline const bool& hasOBJ() const { return mb_hasOBJ; }
				inline const bool& hasShader() const { return mb_hasShader; }

				/* Modifiers */

				inline void setVertices(const Vertices& vertices) { mv_vertices = vertices; }

				/* Implementations */

				inline const std::string getType(TypeInfo typeInfo_ex = DEFAULT_TYPE_INFO) override {
					return (typeInfo_ex) ? (Component::getType() + ".Mesh") : "Mesh"; }
				void clean() override;

				/* Functions */

				bool loadOBJtoMesh(const std::string& obj_filename, bool calculateNormals);
				void attachShaderProgram(ShaderProgram_sptr pshaderProgram);
				void attachTransform(Transform_sptr ptransform);
				void addVertex(const Vertex& vertex);
				bool removeVertexAt(const int& index);
				bool clearVertices();
				void finalize();
				void render(Camera_sptr pcamera);

			private:

				/* Members */

				bool mb_hasOBJ, mb_hasShader;
				unsigned int m_vao, m_vbo;
				Vertices mv_vertices;
				float rotz;
		};
	}
}

#pragma endregion

#endif /* !__MESH_H__ */

// END OF FILE