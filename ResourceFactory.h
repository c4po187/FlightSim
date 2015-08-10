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

using namespace EUMD_FlightSimulator::Utilities;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

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

				/* Functions */

				void						addResource(Resource_sptr presource);
				void						removeResourceAt(const int& index);
				Resource_sptr				findResource(const int& id);
				Resource_sptr				findResource(const std::string& tag);

				/* Implementations */

				inline const std::string	getType() { return "ResourceFactory"; }

			private:

				/* Members */

				PResources					mv_pResources;
				unsigned int				m_idIterator;

				/* Functions */

				void						setupInitialResources();
				void						setResourceId(Resource_sptr presource);
		};
	}
}

#pragma endregion

#endif /* !__RESOURCE_FACTORY_H__ */

// END OF FILE