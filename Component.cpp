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

#pragma endregion

// END OF FILE