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
#include "EUMD_Exceptions.h"
#include "Defines.h"

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	/* Macros */

	#define DEFAULT_TYPE_INFO			0
	#define EXTENDED_TYPE_INFO			1
	#define DST							"Destroying: "
	#define DST_NOTIFY					std::cout << DST << getType() << std::endl

	typedef bool TypeInfo;

	/* Application Object Interface */

	class IApplicationObject {

		public:

			/* Pure Virtual Functions */

			virtual const std::string	getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) = 0;
			virtual void				clean() = 0;
	};
}

#pragma endregion

#endif /* !__IAPPLICATION_OBJECT_H__ */

// END OF FILE