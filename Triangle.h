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

#include "Vertex.h"

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Core {

		namespace Graphics {

			/* Structures */

			typedef struct tagTRIANGLE {
				Vertex p0;
				Vertex p1;
				Vertex p2;
			} Triangle, *PTriangle;
		}
	}
}

#pragma endregion

#endif /* !__TRIANGLE_H__ */

// END OF FILE