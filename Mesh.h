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

				inline const PTriangles& getTriangles() const { return mv_pTriangles; }
				inline const bool& hasOBJ() const { return mb_hasOBJ; }

				/* Modifiers */

				inline void setTriangles(const PTriangles& triangles) { mv_pTriangles = triangles; }

				/* Implementations */

				inline const std::string getType(TypeInfo typeInfo_ex = DEFAULT_TYPE_INFO) override {
					return (typeInfo_ex) ? (Component::getType() + ".Mesh") : "Mesh"; }
				void clean() override;

				/* Functions */

				bool loadOBJtoMesh(const std::string& obj_filename, bool calculateNormals);
				void attachShaderProgram(ShaderProgram_sptr pshaderProgram);
				void attachTransform(Transform_sptr ptransform);
				void addTriangle(Triangle_sptr ptriangle);
				bool removeTriangleAt(const int& index);
				void finalize();
				void render();

			private:

				/* Members */

				PTriangles mv_pTriangles;
				bool mb_hasOBJ, mb_hasShader;
				unsigned int m_vao, m_vbo;
		};
	}
}

#pragma endregion

#endif /* !__MESH_H__ */

// END OF FILE