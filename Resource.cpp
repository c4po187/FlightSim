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

void Resource::addResource(Resource_sptr presource) {
	mv_pChildResources.push_back(presource);
}

void Resource::addComponent(Component_sptr pcomponent) {
	mv_pComponents.push_back(pcomponent);
}

template <class _TyComponent>
std::tr1::shared_ptr<_TyComponent> Resource::getComponent() {
	bool validType = false;
	
	// First check if the type of component is valid
	for (unsigned i = 0; i < SZ_SUBCOMPONENTS; ++i) {
		if (Config::SubComponents[i].c_str() == typeid(_TyComponent).name()) {
			validType = true;
			break;
		}
	}
	
	if (!validType)
		throw std::exception("ERROR: Invalid Component type.");

	Component_sptr component = NULL;

	// Now check if the component exists in the vector
	for (auto c : mv_pComponents) {
		if (typeid(_TyComponent).name() == c->getType().c_str()) {
			component = c;
			break;
		}
	}

	// Return if found
	return (component) ? dynamic_cast<std::tr1::shared_ptr<_TyComponent>>(component) : nullptr;
}

void Resource::clean() {
	if (!mv_pChildResources.empty())
		mv_pChildResources.clear();

	if (!mv_pComponents.empty())
		mv_pComponents.clear();
}

#pragma endregion

// END OF FILE