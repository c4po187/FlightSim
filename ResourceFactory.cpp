/**
 * ResourceFactory.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "ResourceFactory.h"

using namespace EUMD_FlightSimulator::Resources;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

ResourceFactory::ResourceFactory() : m_idIterator(0) { ; }

ResourceFactory::~ResourceFactory() { ; }

/* Functions */

void ResourceFactory::setupInitialResources() { ; }

void ResourceFactory::setResourceId(Resource_sptr pResource) {
	pResource->setID(m_idIterator);
	++m_idIterator;
}

void ResourceFactory::addResource(Resource_sptr presource) {
	setResourceId(presource);
	mv_pResources.push_back(presource);
}

void ResourceFactory::removeResourceAt(const int& index) {
	mv_pResources.erase(mv_pResources.begin() + index);
}

Resource_sptr ResourceFactory::findResource(const int& id) {
	Resource_sptr pr;

	for (auto pRes : mv_pResources) {
		if (pRes->getID() == id) {
			pr = pRes;
			break;
		}
	}

	return (pr) ? pr : nullptr;
}

Resource_sptr ResourceFactory::findResource(const std::string& tag) {
	Resource_sptr pr;

	for (auto pRes : mv_pResources) {
		if (pRes->getTag() == tag) {
			pr = pRes;
			break;
		}
	}

	return (pr) ? pr : nullptr;
}

#pragma endregion

// END OF FILE