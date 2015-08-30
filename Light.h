/**
 * Light.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __LIGHT_H__
#define __LIGHT_H__

#pragma once

#pragma region Prerequisites

#include "Component.h"

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Components {

		/**
		 * This basic light structure holds the three, key
		 * attributes of any light.
		 * The shaders contain a matching structure - 
		 * Bear this in mind!
		 */

		typedef struct tagBASIC_LIGHT {
			Vec4 position;
			Vec4 color;
			float intensity;
		} BasicLight, *PBasicLight;

		// @TODO: Create complex lighting classes here
	}
}

#pragma endregion

#endif /* !__LIGHT_H__ */

// END OF FILE