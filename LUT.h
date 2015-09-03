/**
 * LUT.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __LUT_H__
#define __LUT_H__

#pragma once

#pragma region Prerequisites

#include <string>

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Config {

		#pragma region Macros

		/**
		 * ! IMPORTANT !
		 *
		 * Ensure these macros are updated
		 * to reflect the array sizes defined below.
		 */

		#define SZ_SUBRESOURCES 2
		#define SZ_SUBCOMPONENTS 6

		#pragma endregion
		
		/* Look up Tables */

		static std::string SubResources[] = {
			"Scene",
			"Entity"
		};

		static std::string SubComponents[] = {
			"Camera",
			"Shader",
			"ShaderProgram",
			"Transform",
			"ModelTransform",
			"Mesh"
		};
	}
}

#pragma endregion

#endif /* !__LUT_H__ */

// END OF FILE