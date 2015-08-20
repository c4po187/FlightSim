/**
 * Vertex.h
 *
 * Rici Underwood � 2015
 * c4po198@gmail.com
 */

#ifndef __VERTEX_H__
#define __VERTEX_H__

#pragma once

#pragma region Prerequisites

#include "Defines.h"
#include <memory>

using namespace EUMD_FlightSimulator;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Core {

		namespace Graphics {

			/* Structures */

			typedef struct tagVERTEX {
				Vec4 position;
				Vec4 normal;
				Vec4 tangent;
				Vec4 color;
				Vec2 uv;
			} Vertex, *PVertex;

			typedef struct tagNOOB_VERTEX {
				Vec3 position;
				Vec3 color;
			} NoobVertex, *PNoobVertex;

			/* Shared Pointer definitions */

			typedef std::tr1::shared_ptr<Vertex> Vertex_sptr;
			typedef std::tr1::shared_ptr<NoobVertex> NoobVertex_sptr;
		}
	}
}

#pragma endregion

#endif /* !__VERTEX_H__ */

// END OF FILE