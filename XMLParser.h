/**
 * XMLParser.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __XML_PARSER_H__
#define __XML_PARSER_H__

#pragma once

#pragma region Prerequisites

#include <string>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>

using namespace boost::property_tree;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	typedef ptree XMLTree;
	typedef XMLTree::value_type XMLNode;

	namespace Utilities {

		class XMLParser {

			public:

				/* Functions */

				inline static bool readXMLFile(const std::string& filename, XMLTree& xmltree) {
					// Clear the tree prior to reading to it
					if (xmltree.empty()) xmltree.clear();

					// Read xml file to tree
					read_xml(filename, xmltree);

					/**
					 * If the xml tree is NOT empty,
					 * we can assume the read completed successfully
					 * and return true - false otherwise.
					 */
					return !xmltree.empty() ? true : false;
				}
		};
	}
}

#pragma endregion

#endif /*!__XML_PARSER_H__ */

// END OF FILE