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

ResourceFactory::ResourceFactory() : m_idIterator(0) { setupInitialResources(); }

ResourceFactory::~ResourceFactory() { ; }

/* Functions */

// Load up all game resources here
void ResourceFactory::setupInitialResources() {
	m_currentXMLTree = XMLTree();

	///// XML PARSE TEST /////

	m_xmlTester = XMLTester();
	XMLParser::readXMLFile("test.xml", m_currentXMLTree);

	if (!m_currentXMLTree.empty()) {
		BOOST_FOREACH(XMLNode const& node, m_currentXMLTree.get_child("Resources.Test")) {
			std::string label = node.first;

			if (label == "Number")
				m_xmlTester.num = node.second.get("", 0);
			else if (label == "Textual")
				m_xmlTester.str = node.second.data();
			else {
				BOOST_FOREACH(XMLNode const& snode, node.second.get_child("")) {
					std::string slabel = snode.first;

					if (slabel == "Textual")
						m_xmlTester.vstr.push_back(snode.second.data());
				}
			}
		}
	}

	////////////////////////// > SUCCESS!
}

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