/**
 * ResourceFactory.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __RESOURCE_FACTORY_H__
#define __RESOURCE_FACTORY_H__

#pragma once

#pragma region Prerequisites

#include "Resource.h"
#include <algorithm>
#include <vector>
#include "XMLParser.h"
#include <boost\foreach.hpp>

using namespace EUMD_FlightSimulator::Utilities;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	///// Tests /////

	typedef struct tagXMLTester {
		unsigned int num;
		std::string str;
		std::vector<std::string> vstr;
	} XMLTester, *PXMLTester;

	/////////////////

	namespace Resources {

		class ResourceFactory;

		typedef std::tr1::shared_ptr<ResourceFactory> ResourceFactory_sptr;

		class ResourceFactory : public IApplicationObject {

			public:

				/* Ctor, Dtor */

				ResourceFactory();
				~ResourceFactory();

				/* Accessors */

				inline PResources			getResources() { return mv_pResources; }

				///// Tests /////

				inline PXMLTester			getXMLTester() { return &m_xmlTester; }

				/////////////////

				/* Functions */

				void						addResource(Resource_sptr presource);
				bool						removeResourceAt(const int& index);
				Resource_sptr				findResource(const int& id);
				Resource_sptr				findResource(const std::string& tag);
				void						clean();

				/* Implementations */

				inline const std::string	getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { 
					return "ResourceFactory"; 
				}

			private:

				/* Members */

				PResources					mv_pResources;
				unsigned int				m_idIterator;
				XMLTree						m_currentXMLTree;

				///// Tests /////

				XMLTester					m_xmlTester;

				/////////////////

				/* Functions */

				void						setupInitialResources();
				void						setResourceId(Resource_sptr presource);
		};
	}
}

#pragma endregion

#endif /* !__RESOURCE_FACTORY_H__ */

// END OF FILE