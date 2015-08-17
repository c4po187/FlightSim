/**
 * EUMD_Exceptions.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __EUMD_EXCEPTIONS_H__
#define __EUMD_EXCEPTIONS_H__

#pragma once

#pragma region Prerequisites

#include <stdexcept>
#include <ios>
#include <system_error>

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Config {

		#define EX_GENERAL			std::exception("ERROR: Something wicked happened!")
		#define EX_INV_COMP_TYPE	std::exception("ERROR: Invalid Component type.")
		#define EX_INV_RES_TYPE		std::exception("ERROR: Invalid Resource type.")
		#define EX_INV_ENT_TYPE		std::exception("ERROR: Invalid Entity type.") 
		#define EX_INV_TAG			std::runtime_error("ERROR: Tag does not exist.")
		#define EX_IOR				std::out_of_range("ERROR: Index out of range.")
		#define EX_XML_READ			std::ios_base::failure("ERROR: Failed to read XML file.")
		#define EX_XML_PARSE		std::runtime_error("ERROR: Failed to parse XML data.")
		#define EX_WINBUM			std::system_error("ERROR: Seems we have been bummed by Windows, again...")
	}
}

#pragma endregion

#endif /* !__EUMD_EXCEPTIONS_H__ */

// END OF FILE