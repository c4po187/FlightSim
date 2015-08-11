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

/* Functions */

void Resource::addResource(Resource_sptr presource) {
	mv_pChildResources.push_back(presource);
}

void Resource::addComponent(Component_sptr pcomponent) {
	mv_pComponents.push_back(pcomponent);
}

template <class _TyComponent>
std::tr1::shared_ptr<_TyComponent> getComponent() {
	// @TODO
	return nullptr;
}

void Resource::clean() {
	if (!mv_pChildResources.empty())
		mv_pChildResources.clear();

	if (!mv_pComponents.empty())
		mv_pComponents.clear();
}

#pragma endregion

// END OF FILE