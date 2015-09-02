/**
 * Triangle.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H_

#pragma once

#pragma region Prerequisites

#include <vector>
#include "Vertex.h"

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Core {

		namespace Graphics {

			/* Structures */

			typedef struct tagTRIANGLE {
				Vertex points[3];
				const Vertex& operator [] (const int& i) { return points[i]; }
			} Triangle, *PTriangle;

			/* Shared Pointer definitions */

			typedef std::tr1::shared_ptr<Triangle> Triangle_sptr;
			typedef std::vector<Triangle_sptr> PTriangles;
		}
	}
}

#pragma endregion

#endif /* !__TRIANGLE_H__ */

// END OF FILE