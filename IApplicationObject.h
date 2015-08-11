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

#pragma region Macros

	#define DEFAULT_TYPE_INFO	0
	#define EXTENDED_TYPE_INFO	1

	typedef bool TypeInfo;

	/* Application Object Interface */

	class IApplicationObject {

		public:

			/* Pure Virtual Functions */

			virtual const std::string	getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) = 0;
			virtual void				clean() = 0;
	};

	#define DST					"\n###############################\nDestroying: "
	#define DST_NOTIFY			std::cout << DST << getType() << \
								"\n###############################\n" << std::endl
}

#pragma endregion

#endif /* !__IAPPLICATION_OBJECT_H__ */

// END OF FILE