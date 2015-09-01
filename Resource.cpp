/**
 * Resource.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Resource.h"

using namespace EUMD_FlightSimulator;
using namespace EUMD_FlightSimulator::Resources;

#pragma endregion

#pragma region Definitions

/* Dtor */

Resource::~Resource() { 
	clean();
#if _DEBUG
	DST_NOTIFY;
#endif
}

/* Operator Overloads */

bool Resource::operator == (const Resource& resource) {
	return (this->getID() == resource.getID());
}

/* Functions */

bool Resource::checkValidity(const char* type_id) {
	bool validity = false;
	std::string tname_ex(type_id);
	size_t dc_pos = tname_ex.find_last_of(':');
	std::string tname = tname_ex.substr(dc_pos + 1);

	// First check if the type of component is valid
	for (unsigned i = 0; i < SZ_SUBCOMPONENTS; ++i) {
		if (Config::SubComponents[i] == tname) {
			validity = true;
			break;
		}
	}

	return validity;
}

void Resource::addResource(Resource_sptr presource) {
	mv_pChildResources.push_back(presource);
}

void Resource::addComponent(Component_sptr pcomponent) {
	mv_pComponents.push_back(pcomponent);
}

void Resource::clean() {
	if (!mv_pChildResources.empty())
		mv_pChildResources.clear();

	if (!mv_pComponents.empty())
		mv_pComponents.clear();
}

#pragma endregion

// END OF FILE