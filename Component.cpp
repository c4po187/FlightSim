/**
 * Component.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Component.h"

using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Definitions

/* Dtor */

Component::~Component() {
	clean();
#if _DEBUG
	DST_NOTIFY;
#endif
}

/* Functions */

void Component::addComponent(Component_sptr pComponent) {
	mv_pChildComponents.push_back(pComponent);
}

bool Component::removeComponentAt(const int& index) {
	if (index < 0 || index >= mv_pChildComponents.size())
		return false;

	size_t pre = mv_pChildComponents.size();
	mv_pChildComponents.erase(mv_pChildComponents.begin() + index);

	return (mv_pChildComponents.size() < pre);
}

void Component::clean() {
	if (!mv_pChildComponents.empty())
		mv_pChildComponents.clear();
}

bool Component::checkValidity(const char* type_id) {
	bool validity = false;
	std::string tname = getClassNameFromTypeID(type_id);

	for (unsigned i = 0; i < SZ_SUBCOMPONENTS; ++i) {
		if (Config::SubComponents[i] == tname) {
			validity = true;
			break;
		}
	}

	return validity;
}

std::string Component::getClassNameFromTypeID(const char* type_id) {
	std::string tname_ex(type_id);
	size_t dc_pos = tname_ex.find_last_of(':');
	std::string tname = tname_ex.substr(dc_pos + 1);

	return tname;
}

#pragma endregion

// END OF FILE