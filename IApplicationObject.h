/**
 * IApplicationObject.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __IAPPLICATION_OBJECT_H__
#define __IAPPLICATION_OBJECT_H__

#pragma once

#pragma region Prerequisites

#include <iostream>
#include <string>

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	class IApplicationObject {

		public:

			/* Functions */

			virtual const std::string getType() = 0;
	};
}

#pragma endregion

#endif /* !__IAPPLICATION_OBJECT_H__ */

// END OF FILE